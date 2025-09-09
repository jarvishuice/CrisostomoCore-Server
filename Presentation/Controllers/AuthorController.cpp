#include "AuthorController.hpp"
#include <crow.h>
#include <iostream>
#include <vector>

AuthorController::AuthorController(GetAuthorsUseCase& authorsUseCase,
                                 GetAuthorUseCase& authorUseCase,
                                 RegisterAuthorUseCase& registerUseCase,
                                 SearchAuthorUseCase& searchUseCase)
    : getAuthorsUseCase(authorsUseCase),
      getAuthorUseCase(authorUseCase),
      registerAuthorUseCase(registerUseCase),
      searchAuthorUseCase(searchUseCase)
{
    std::cout << "AuthorController inicializado\n";
}

void AuthorController::setupRoutes(crow::SimpleApp& app)
{
    // GET /authors → devuelve todos los autores
    CROW_ROUTE(app, "/authors")
    ([this]() -> crow::response {
        std::cout << "Petición GET /authors recibida\n";
        try {
            std::vector<Domain::Entities::AuthorEntity> authors = getAuthorsUseCase.execute();

            crow::json::wvalue body;
            auto& arr = body["authors"] = crow::json::wvalue::list();
            for (size_t i = 0; i < authors.size(); ++i) {
                std::string authorJson = authors[i].to_json().dump(4);
                arr[i] = crow::json::load(authorJson);
            }

            crow::response resp{body};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al obtener autores: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });

    // GET /authors/{cod} → devuelve un autor específico
    CROW_ROUTE(app, "/authors/<string>")
    ([this](const crow::request& /*req*/, std::string cod) -> crow::response {
        std::cout << "Petición GET /authors/" << cod << "\n";
        try {
            auto authors = getAuthorUseCase.execute(cod);

            // Verificar si se encontraron autores
            if (authors.empty()) {
                return crow::response{
                    crow::status::NOT_FOUND,
                    "{\"error\": \"Autor no encontrado\"}"
                };
            }

            // Devolver el primer autor encontrado (ya que getByCod retorna vector)
            auto authorJson = authors[0].to_json().dump();
            crow::json::wvalue body = crow::json::load(authorJson);

            crow::response resp{body};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al obtener autor: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });

    // POST /authors → crea un nuevo autor
    CROW_ROUTE(app, "/authors").methods("POST"_method)
    ([this](const crow::request& req) -> crow::response {
        std::cout << "Petición POST /authors recibida\n";
        try {
            // Parsear JSON del cuerpo de la petición
            auto body = crow::json::load(req.body);
            if (body.error()) {
                return crow::response{
                    crow::status::BAD_REQUEST,
                    "{\"error\": \"JSON inválido\"}"
                };
            }

            // Validar campos requeridos
            if (!body.has("name") || body["name"].s().size() == 0) {
                return crow::response{
                    crow::status::BAD_REQUEST,
                    "{\"error\": \"El campo 'name' es requerido\"}"
                };
            }

            // Crear entidad autor
            Domain::Entities::AuthorEntity author;
            author.name = body["name"].s();
            
            if (body.has("cod") && body["cod"].s().size() > 0) {
                author.cod = body["cod"].s();
            }
            
            if (body.has("description") && body["description"].s().size() > 0) {
                author.description = body["description"].s();
            }

            if (body.has("codUserCreated") && body["codUserCreated"].s().size() > 0) {
                author.codUserCreated = body["codUserCreated"].s();
            }

            // Registrar autor
            std::string resultCod = registerAuthorUseCase.execute(author);
            
            if (resultCod.empty()) {
                return crow::response{
                    crow::status::INTERNAL_SERVER_ERROR,
                    "{\"error\": \"Error al registrar el autor\"}"
                };
            }

            // Devolver el autor creado
            crow::json::wvalue responseBody;
            responseBody["message"] = "Autor registrado exitosamente";
            responseBody["cod"] = resultCod;
            responseBody["author"] = crow::json::load(author.to_json().dump());

            crow::response resp{responseBody};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al registrar autor: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });

    // GET /authors/search?param=valor → busca autores
    CROW_ROUTE(app, "/authors/search/<string>")
    ([this](const crow::request& /*req*/, std::string cod) -> crow::response {
        std::cout << "Petición GET /authors/search recibida\n";
        try {
            // Obtener parámetro de búsqueda
           
            
            
            std::vector<Domain::Entities::AuthorEntity> authors = searchAuthorUseCase.execute(cod);

            crow::json::wvalue body;
            auto& arr = body["authors"] = crow::json::wvalue::list();
            for (size_t i = 0; i < authors.size(); ++i) {
                std::string authorJson = authors[i].to_json().dump(4);
                arr[i] = crow::json::load(authorJson);
            }

            body["searchParam"] = cod;
            body["count"] = static_cast<int>(authors.size());

            crow::response resp{body};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al buscar autores: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });
}

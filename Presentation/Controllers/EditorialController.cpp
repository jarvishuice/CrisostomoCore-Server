#include "EditorialController.hpp"
#include <crow.h>
#include <iostream>
#include <vector>

EditorialController::EditorialController(GetEditorialsUseCase& editorialsUseCase,
                                       GetEditorialUseCase& editorialUseCase,
                                       RegisterEditorialUseCase& registerUseCase)
    : getEditorialsUseCase(editorialsUseCase),
      getEditorialUseCase(editorialUseCase),
      registerEditorialUseCase(registerUseCase)
{
    std::cout << "EditorialController inicializado\n";
}

void EditorialController::setupRoutes(crow::SimpleApp& app)
{
    // GET /editorials → devuelve todas las editoriales
    CROW_ROUTE(app, "/editorials")
    ([this]() -> crow::response {
        std::cout << "Petición GET /editorials recibida\n";
        try {
            std::vector<Domain::Entities::EditorialEntity> editorials = getEditorialsUseCase.execute();

            crow::json::wvalue body;
            auto& arr = body["editorials"] = crow::json::wvalue::list();
            for (size_t i = 0; i < editorials.size(); ++i) {
                std::string editorialJson = editorials[i].to_json().dump(4);
                arr[i] = crow::json::load(editorialJson);
            }

            crow::response resp{body};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al obtener editoriales: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });

    // GET /editorials/{cod} → devuelve una editorial específica
    CROW_ROUTE(app, "/editorials/<string>")
    ([this](const crow::request& /*req*/, std::string cod) -> crow::response {
        std::cout << "Petición GET /editorials/" << cod << "\n";
        try {
            auto editorial = getEditorialUseCase.execute(cod);

            // Verificar si se encontró la editorial
            if (editorial.cod.empty()) {
                return crow::response{
                    crow::status::NOT_FOUND,
                    "{\"error\": \"Editorial no encontrada\"}"
                };
            }

            auto editorialJson = editorial.to_json().dump();
            crow::json::wvalue body = crow::json::load(editorialJson);

            crow::response resp{body};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al obtener editorial: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });

    // POST /editorials → crea una nueva editorial
    CROW_ROUTE(app, "/editorials").methods("POST"_method)
    ([this](const crow::request& req) -> crow::response {
        std::cout << "Petición POST /editorials recibida\n";
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

            // Crear entidad editorial
            Domain::Entities::EditorialEntity editorial;
            editorial.name = body["name"].s();
            
            if (body.has("cod") && body["cod"].s().size() > 0) {
                editorial.cod = body["cod"].s();
            }
            
            if (body.has("userCod") && body["userCod"].s().size() > 0) {
                editorial.userCod = body["userCod"].s();
            }

            // Registrar editorial
            std::string resultCod = registerEditorialUseCase.execute(editorial);
            
            if (resultCod.empty()) {
                return crow::response{
                    crow::status::INTERNAL_SERVER_ERROR,
                    "{\"error\": \"Error al registrar la editorial\"}"
                };
            }

            // Devolver la editorial creada
            crow::json::wvalue responseBody;
            responseBody["message"] = "Editorial registrada exitosamente";
            responseBody["cod"] = resultCod;
            responseBody["editorial"] = crow::json::load(editorial.to_json().dump());

            crow::response resp{responseBody};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al registrar editorial: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });
}

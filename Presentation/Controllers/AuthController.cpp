#include "AuthController.hpp"
#include <crow.h>
#include <iostream>

AuthController::AuthController(SingUpUseCase& useCase)
    : singUpUseCase(useCase)
{
    std::cout << "AuthController inicializado\n";
}

void AuthController::setupRoutes(crow::SimpleApp& app)
{
    // POST /auth/signup → registra un nuevo usuario
    CROW_ROUTE(app, "/auth/signup")
        .methods("POST"_method)
        ([this](const crow::request& req) -> crow::response {
            std::cout << "Petición POST /auth/signup recibida\n";
            try {
                // Parsear el JSON del body de la petición
                auto body = crow::json::load(req.body);
                if (!body) {
                    return crow::response{
                        crow::status::BAD_REQUEST,
                        "Invalid JSON format"
                    };
                }

                // Crear la entidad de usuario desde el JSON
                Domain::Entities::UserEntity user;
                user.from_json(body);

                // Ejecutar el caso de uso de registro
                std::string userCode = singUpUseCase.execute(user);

                if (userCode.empty()) {
                    return crow::response{
                        crow::status::INTERNAL_SERVER_ERROR,
                        "Failed to create user"
                    };
                }

                // Retornar respuesta exitosa con el código del usuario
                crow::json::wvalue responseBody;
                responseBody["message"] = "User created successfully";
              

                crow::response resp{crow::status::CREATED,responseBody};
                resp.set_header("Content-Type", "application/json");
                
              
                return resp;
            }
            catch (const std::exception& e) {
                std::cerr << "Error al registrar usuario: " << e.what() << "\n";
                return crow::response{
                    crow::status::INTERNAL_SERVER_ERROR,
                    std::string("Internal error: ") + e.what()
                };
            }
        });

    // POST /auth/login → autenticación de usuario (para futuras implementaciones)
    CROW_ROUTE(app, "/auth/login")
        .methods("POST"_method)
        ([this](const crow::request& req) -> crow::response {
            std::cout << "Petición POST /auth/login recibida\n";
            try {
                // Parsear el JSON del body de la petición
                auto body = crow::json::load(req.body);
                if (!body) {
                    return crow::response{
                        crow::status::BAD_REQUEST,
                        "Invalid JSON format"
                    };
                }

                // TODO: Implementar lógica de login
                // Por ahora retornamos un mensaje de "en desarrollo"
                
                crow::json::wvalue responseBody;
                responseBody["message"] = "Login functionality coming soon";
                responseBody["status"] = "not_implemented";

                crow::response resp{responseBody};
                resp.set_header("Content-Type", "application/json");
                return resp;
            }
            catch (const std::exception& e) {
                std::cerr << "Error en login: " << e.what() << "\n";
                return crow::response{
                    crow::status::INTERNAL_SERVER_ERROR,
                    std::string("Internal error: ") + e.what()
                };
            }
        });

    // GET /auth/health → verificación de estado del servicio de autenticación
    CROW_ROUTE(app, "/auth/health")
    ([this]() -> crow::response {
        std::cout << "Petición GET /auth/health recibida\n";
        
        crow::json::wvalue responseBody;
        responseBody["status"] = "healthy";
        responseBody["service"] = "authentication";
        responseBody["timestamp"] = std::time(nullptr);

        crow::response resp{responseBody};
        resp.set_header("Content-Type", "application/json");
        return resp;
    });
}

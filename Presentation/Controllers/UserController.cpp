#include "UserController.hpp"
#include <crow.h>
#include <iostream>
#include <vector>
#include <UserDAO.hpp>

UserController::UserController(GetUsersUseCase& useCase,
                               GetUserUseCase& useCase2)
    : getUsersUseCase(useCase),
      getUserUseCase(useCase2)
{
    std::cout << "UserController inicializado\n";
}

void UserController::setupRoutes(crow::SimpleApp& app)
{
    // GET /users → devuelve { "users": [ {...}, {...} ] }
    CROW_ROUTE(app, "/users")
    ([this]() -> crow::response {
        std::cout << "Petición GET /users recibida\n";
        try {
            
            std::vector<Domain::Entities::UserEntity> users = getUsersUseCase.execute();

            crow::json::wvalue body;
            auto& arr = body["users"] = crow::json::wvalue::list();
            for (size_t i = 0; i < users.size(); ++i) {
                std::cout <<  std::endl << users[1].firstname << "salida ddel dao al leer ";
                 std::string userJson = users[i].to_json().dump(4);
                 arr[i] = crow::json::load(userJson);
            }

            crow::response resp{body};
        
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al obtener usuarios: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });

    // GET /users/{cod} → devuelve un solo usuario
    CROW_ROUTE(app, "/users/<string>")
    ([this](const crow::request& /*req*/, std::string cod) -> crow::response {
        std::cout << "Petición GET /users/" << cod << "\n";
        try {
            auto user = getUserUseCase.execute(cod);

            auto userJson = user.to_json().dump();
            crow::json::wvalue body = crow::json::load(userJson);

            crow::response resp{body};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al obtener usuario: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });
}

#include "CategoryController.hpp"
#include <crow.h>
#include <iostream>
#include <vector>

CategoryController::CategoryController(GetAreasDeweyUseCase& areasUseCase,
                                     GetCategoriesByParentCodeUseCase& categoriesUseCase)
    : getAreasDeweyUseCase(areasUseCase),
      getCategoriesByParentCodeUseCase(categoriesUseCase)
{
    std::cout << "CategoryController inicializado\n";
}

void CategoryController::setupRoutes(crow::SimpleApp& app)
{
    // GET /categories/areas → devuelve todas las áreas principales (parentcod = '-1')
    CROW_ROUTE(app, "/categories/areas")
    ([this]() -> crow::response {
        std::cout << "Petición GET /categories/areas recibida\n";
        try {
            std::vector<Domain::Entities::CategoryEntity> areas = getAreasDeweyUseCase.execute();

            crow::json::wvalue body;
            auto& arr = body["areas"] = crow::json::wvalue::list();
            for (size_t i = 0; i < areas.size(); ++i) {
                std::string areaJson = areas[i].to_json().dump(4);
                arr[i] = crow::json::load(areaJson);
            }

            crow::response resp{body};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al obtener áreas: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });

    // GET /categories/by-parent/{parentCode} → devuelve categorías por código padre
    CROW_ROUTE(app, "/categories/by-parent/<string>")
    ([this](const crow::request& /*req*/, std::string parentCode) -> crow::response {
        std::cout << "Petición GET /categories/by-parent/" << parentCode << "\n";
        try {
            std::vector<Domain::Entities::CategoryEntity> categories = getCategoriesByParentCodeUseCase.execute(parentCode);

            crow::json::wvalue body;
            auto& arr = body["categories"] = crow::json::wvalue::list();
            for (size_t i = 0; i < categories.size(); ++i) {
                std::string categoryJson = categories[i].to_json().dump(4);
                arr[i] = crow::json::load(categoryJson);
            }

            crow::response resp{body};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al obtener categorías por código padre: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });

    // GET /categories → devuelve todas las categorías (alias para /categories/areas)
    CROW_ROUTE(app, "/categories")
    ([this]() -> crow::response {
        std::cout << "Petición GET /categories recibida (redirigiendo a /categories/areas)\n";
        try {
            std::vector<Domain::Entities::CategoryEntity> areas = getAreasDeweyUseCase.execute();

            crow::json::wvalue body;
            auto& arr = body["categories"] = crow::json::wvalue::list();
            for (size_t i = 0; i < areas.size(); ++i) {
                std::string areaJson = areas[i].to_json().dump(4);
                arr[i] = crow::json::load(areaJson);
            }

            crow::response resp{body};
            resp.set_header("Content-Type", "application/json");
            return resp;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al obtener categorías: " << e.what() << "\n";
            return crow::response{
                crow::status::INTERNAL_SERVER_ERROR,
                std::string("Internal error: ") + e.what()
            };
        }
    });
}

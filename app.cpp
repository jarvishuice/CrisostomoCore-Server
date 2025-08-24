// <summary>
// Main application entry point
// </summary>
#include "Domain/Kernel/ConfigValues.hpp"
#include "Infrastructure/Providers/Logs.hpp"
#include "Infrastructure/Providers/StaticConnPsql.hpp"
#include "Infrastructure/Providers/CrowLoggerAdapter.hpp"
#include "Application/UseCases/GetUsersUseCase.hpp"
#include "Presentation/Controllers/UserController.hpp"
#include <crow.h>
int main()
{
    // Inicializar la configuración
    Domain::Kernel::ConfigValues::start();
    Logger::instance().init(Domain::Kernel::ConfigValues::LOG_PATH, LogLevel::DEBUG, true);
    static CrowLoggerAdapter logAdapter;
    Logger::instance().info("Crisostomo start up ....  ");
    Logger::instance().info("Configuración cargada correctamente");
    Logger::instance().info("Configuración Logs correctamente");
    auto &log = Logger::instance();
    log.info("Iniciando el pool de conexiones a la base de datos...");
    StaticConnPoolPsql::initialize(
        "host=" + Domain::Kernel::ConfigValues::DB_HOST + " port=" + Domain::Kernel::ConfigValues::DB_PORT +
            " user=" + Domain::Kernel::ConfigValues::DB_USER +
            " password=" + Domain::Kernel::ConfigValues::DB_PASSWORD +
            " dbname=" + Domain::Kernel::ConfigValues::DB_NAME,
        10 // Tamaño del pool de conexiones

    );

    log.info("Pool de conexiones iniciado correctamente");
    log.info("Iniciando el servidor web en el puerto " + Domain::Kernel::ConfigValues::SERVER_PORT + "...");
    crow::SimpleApp app;
    crow::logger::setHandler(&logAdapter);
    GetUsersUseCase getUsersUseCase;
    GetUserUseCase getUserUseCase;
    UserController userController = UserController(getUsersUseCase,getUserUseCase);
    userController.setupRoutes(app);
    app.port(std::stoi(Domain::Kernel::ConfigValues::SERVER_PORT)).multithreaded().concurrency(32);

    std::thread server_thread([&app]
                              { app.run(); });

    server_thread.join();
    StaticConnPoolPsql::shutdown();
    log.info("Servidor web detenido correctamente");

    return 0;
}
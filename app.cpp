// <summary>
// Main application entry point
// </summary>
#include "Domain/Kernel/ConfigValues.hpp"
#include "Infrastructure/Providers/Logs.hpp"
#include "Infrastructure/Providers/StaticConnPsql.hpp"
#include "Infrastructure/Providers/CrowLoggerAdapter.hpp"
#include <crow.h>
int main()
{
    // Inicializar la configuración
    Domain::Kernel::ConfigValues::start();
    Logger::instance().init(Domain::Kernel::ConfigValues::LOG_PATH, LogLevel::DEBUG, true);
    static CrowLoggerAdapter logAdapter;
    Logger::instance().info("Configuración cargada correctamente");
    auto &log = Logger::instance();
    StaticConnPoolPsql::initialize(
        "host=" + Domain::Kernel::ConfigValues::DB_HOST + " port=" + Domain::Kernel::ConfigValues::DB_PORT +
            " user=" + Domain::Kernel::ConfigValues::DB_USER +
            " password=" + Domain::Kernel::ConfigValues::DB_PASSWORD +
            " dbname=" + Domain::Kernel::ConfigValues::DB_NAME,
        10 // Tamaño del pool de conexiones

    );

    
    crow::SimpleApp app;

    // Acceder a los valores de configuración

    crow::logger::setHandler(&logAdapter);
    app.port(Domain::Kernel::ConfigValues::SERVER_PORT).multithreaded().concurrency(32);

    std::thread server_thread([&app]
                              { app.run(); });

    server_thread.join();
    StaticConnPoolPsql::shutdown();
    return 0;
  
}
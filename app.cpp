// <summary>
// Main application entry point
// </summary>
#include "Domain/Kernel/ConfigValues.hpp"
#include "Infrastructure/Providers/Logs.hpp"
#include "Infrastructure/Providers/StaticConnPsql.hpp"
#include "Infrastructure/Providers/CrowLoggerAdapter.hpp"
#include "Application/UseCases/GetUsersUseCase.hpp"
#include "Presentation/Controllers/UserController.hpp"
#include "Application/Helpers/Sha256Helper.hpp"
#include "Application/Helpers/JwtHelper.hpp"
#include "Application/UseCases/LoginUseCase.hpp"
#include "Application/UseCases/SingUpUseCase.hpp"
#include "Application/UseCases/GetCategoriesByParentCodeUseCase.hpp"
#include "Application/UseCases/GetAreasDeweyUseCase.hpp"
#include "Application/UseCases/GetEditorialsUseCase.hpp"
#include "Application/UseCases/GetEditorialUseCase.hpp"
#include  "Application/UseCases/RegisterEditorialUseCase.hpp"
#include "Presentation/Controllers/SwaggerController.hpp"
#include "Presentation/Controllers/AuthController.hpp"
#include "Presentation/Controllers/CategoryController.hpp"
#include "Presentation/Controllers/EditorialController.hpp"

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
    JwtHelper helper = JwtHelper("123456");
    Application::Helpers::Sha256Helper sha256Helper = Application::Helpers::Sha256Helper();
    std::string password = "123456";
    std::string hash = sha256Helper.hash(password);
    std::string token = helper.generateToken("jarvis");
    log.debug("jwt: " + token);
    log.info("Token: " + hash);

    log.info("Pool de conexiones iniciado correctamente");
    log.info("Iniciando el servidor web en el puerto " + Domain::Kernel::ConfigValues::SERVER_PORT + "...");
    StaticConnPoolPsql::initialize(
        "host=" + Domain::Kernel::ConfigValues::DB_HOST + " port=" + Domain::Kernel::ConfigValues::DB_PORT +
            " user=" + Domain::Kernel::ConfigValues::DB_USER +
            " password=" + Domain::Kernel::ConfigValues::DB_PASSWORD +
            " dbname=" + Domain::Kernel::ConfigValues::DB_NAME,
        10 // Tamaño del pool de conexiones

    );
    
    crow::SimpleApp app;
    crow::logger::setHandler(&logAdapter);
    GetUsersUseCase getUsersUseCase;
    GetUserUseCase getUserUseCase;
    SingUpUseCase singUpUseCase;
    LoginUseCase loginUseCase;
    GetCategoriesByParentCodeUseCase getCategories;
    GetAreasDeweyUseCase   getAreas;
    UserController userController = UserController(getUsersUseCase,getUserUseCase);
    userController.setupRoutes(app);
    SwaggerController swaggerController;
    CategoryController categoryController =  CategoryController(getAreas,getCategories) ;
    AuthController  authController = AuthController(singUpUseCase,loginUseCase);
    swaggerController.setupRoutes(app);
    authController.setupRoutes(app);
    categoryController.setupRoutes(app);
    // Ejemplo de uso en app.cpp
GetEditorialsUseCase editorialsUseCase;
GetEditorialUseCase editorialUseCase;
RegisterEditorialUseCase registerUseCase;
EditorialController editorialController(editorialsUseCase, editorialUseCase, registerUseCase);
editorialController.setupRoutes(app);

    app.port(std::stoi(Domain::Kernel::ConfigValues::SERVER_PORT)).multithreaded().concurrency(32);

    std::thread server_thread([&app]
                              { app.run(); });

    server_thread.join();
    StaticConnPoolPsql::shutdown();
    log.info("Servidor web detenido correctamente");

    return 0;
}
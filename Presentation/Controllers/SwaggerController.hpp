#ifndef SWAGGER_CONTROLLER_HPP
#define SWAGGER_CONTROLLER_HPP

#include "crow.h"

class SwaggerController {
public:
    SwaggerController() = default;
    ~SwaggerController() = default;
    
    void setupRoutes(crow::SimpleApp& app);
    
private:
    std::string generateOpenAPISpec();
    std::string generateAuthEndpoints();
    std::string generateUserEndpoints();
};

#endif // SWAGGER_CONTROLLER_HPP

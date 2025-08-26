#ifndef AUTH_CONTROLLER_HPP
#define AUTH_CONTROLLER_HPP

#include "crow.h"
#include "../../Application/UseCases/SingUpUseCase.hpp"


class AuthController {
private:
    SingUpUseCase& singUpUseCase;
   
    
public:
AuthController(SingUpUseCase& singUpUseCase);
    void setupRoutes(crow::SimpleApp& app);
};

#endif // USER_CONTROLLER_HPP
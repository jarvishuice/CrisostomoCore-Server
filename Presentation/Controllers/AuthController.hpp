#ifndef AUTH_CONTROLLER_HPP
#define AUTH_CONTROLLER_HPP

#include "crow.h"
#include "../../Application/UseCases/SingUpUseCase.hpp"
#include "../../Application/UseCases/LoginUseCase.hpp"


class AuthController {
private:
    SingUpUseCase& singUpUseCase;
    LoginUseCase& loginUsecase;
   
    
public:
AuthController(SingUpUseCase& singUpUseCase,LoginUseCase& loginUsecase);
    void setupRoutes(crow::SimpleApp& app);
};

#endif // USER_CONTROLLER_HPP
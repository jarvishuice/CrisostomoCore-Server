#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include "crow.h"
#include "../../Application/UseCases/GetUsersUseCase.hpp"
#include "../../Application/UseCases/GetUserUseCase.hpp"

class UserController {
private:
    GetUsersUseCase& getUsersUseCase;
    GetUserUseCase& getUserUseCase;
    
public:
    UserController(GetUsersUseCase& useCase,GetUserUseCase& useCase2);
    void setupRoutes(crow::SimpleApp& app);
};

#endif // USER_CONTROLLER_HPP
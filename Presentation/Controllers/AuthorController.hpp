#ifndef AUTHOR_CONTROLLER_HPP
#define AUTHOR_CONTROLLER_HPP

#include <crow.h>
#include "../../Application/UseCases/GetAuthorsUseCase.hpp"
#include "../../Application/UseCases/GetAuthorUseCase.hpp"
#include "../../Application/UseCases/RegisterAuthorUseCase.hpp"
#include "../../Application/UseCases/SearchAuthorUseCase.hpp"

class AuthorController {
private:
    GetAuthorsUseCase& getAuthorsUseCase;
    GetAuthorUseCase& getAuthorUseCase;
    RegisterAuthorUseCase& registerAuthorUseCase;
    SearchAuthorUseCase& searchAuthorUseCase;
    
public:
    AuthorController(GetAuthorsUseCase& authorsUseCase, 
                    GetAuthorUseCase& authorUseCase,
                    RegisterAuthorUseCase& registerUseCase,
                    SearchAuthorUseCase& searchUseCase);
    void setupRoutes(crow::SimpleApp& app);
};

#endif // AUTHOR_CONTROLLER_HPP

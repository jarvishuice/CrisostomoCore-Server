#ifndef EDITORIAL_CONTROLLER_HPP
#define EDITORIAL_CONTROLLER_HPP

#include <crow.h>
#include "../../Application/UseCases/GetEditorialsUseCase.hpp"
#include "../../Application/UseCases/GetEditorialUseCase.hpp"
#include "../../Application/UseCases/RegisterEditorialUseCase.hpp"

class EditorialController {
private:
    GetEditorialsUseCase& getEditorialsUseCase;
    GetEditorialUseCase& getEditorialUseCase;
    RegisterEditorialUseCase& registerEditorialUseCase;
    
public:
    EditorialController(GetEditorialsUseCase& editorialsUseCase, 
                       GetEditorialUseCase& editorialUseCase,
                       RegisterEditorialUseCase& registerUseCase);
    void setupRoutes(crow::SimpleApp& app);
};

#endif // EDITORIAL_CONTROLLER_HPP
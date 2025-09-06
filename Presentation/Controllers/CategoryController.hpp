#ifndef CATEGORY_CONTROLLER_HPP
#define CATEGORY_CONTROLLER_HPP

#include <crow.h>
#include "../../Application/UseCases/GetAreasDeweyUseCase.hpp"
#include "../../Application/UseCases/GetCategoriesByParentCodeUseCase.hpp"

class CategoryController {
private:
    GetAreasDeweyUseCase& getAreasDeweyUseCase;
    GetCategoriesByParentCodeUseCase& getCategoriesByParentCodeUseCase;
    
public:
    CategoryController(GetAreasDeweyUseCase& areasUseCase, GetCategoriesByParentCodeUseCase& categoriesUseCase);
    void setupRoutes(crow::SimpleApp& app);
};

#endif // CATEGORY_CONTROLLER_HPP
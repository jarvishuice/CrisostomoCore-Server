#pragma once
#include "../Entities/CategoryEntity.hpp"

namespace Domain::IDAO
{
    class ICategoryDAO
    {
    public:
        virtual ~ICategoryDAO() = default;
        virtual std::vector<Domain::Entities::CategoryEntity> allAreas() = 0;
        virtual std::vector<Domain::Entities::CategoryEntity> getByParentID(const std::string &cod) = 0;
    };
}
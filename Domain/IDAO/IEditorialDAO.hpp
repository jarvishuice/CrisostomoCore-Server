#pragma once
#include "../Entities/EditorialEntity.hpp"

namespace Domain::IDAO
{
    class IEditorialDAO
    {
    public:
        virtual ~IEditorialDAO() = default;
        virtual std::vector<Domain::Entities::EditorialEntity> all() = 0;
        virtual Domain::Entities::EditorialEntity findByCode(const std::string &cod) = 0;
        virtual std::string save(const Domain::Entities::EditorialEntity &entity) = 0;
    };
}
#pragma once
#include "../Entities/AuthorEntity.hpp"

namespace Domain::IDAO
{
    class IAuthorDAO
    {
    public:
        virtual ~IAuthorDAO() = default;
        virtual std::vector<Domain::Entities::AuthorEntity> all() = 0;
        virtual std::string save(const Domain::Entities::AuthorEntity &entity) = 0;
        virtual std::vector<Domain::Entities::AuthorEntity> getByCod(const std::string &cod) = 0;
        virtual std::vector<Domain::Entities::AuthorEntity> search(const std::string &param) = 0;
    };
}
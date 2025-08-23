#pragma once
#include "../Entities/UserEntity.hpp"

namespace Domain::IDAO
{
    class IUserDAO
    {
    public:
        virtual ~IUserDAO() = default;
        virtual std::string add(const Domain::Entities::UserEntity& user) = 0;
        virtual Domain::Entities::UserEntity findByID(const std::string& id) const = 0;
        virtual std::string update(const Domain::Entities::UserEntity& user) = 0;
        virtual std::vector<Domain::Entities::UserEntity> all() const = 0;
    };
}
#pragma once
#include "../Entities/UserEntity.hpp"

namespace Domain::IDAO
{
    class IUserDAO
    {
    public:
        virtual ~IUserDAO() = default;
        virtual std::string add(const Domain::Entities::UserEntity& user) = 0;
        virtual Domain::Entities::UserEntity getUserByLogin(std::string param) = 0;
        virtual std::vector<Domain::Entities::UserEntity> all()  = 0;
        virtual Domain::Entities::UserEntity findByCode(const std::string &cod) = 0;
    };
}
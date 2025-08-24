#pragma once
#include "../../Infrastructure/DAO/UserDAO.hpp"
#include "../../Domain/Entities/UserEntity.hpp"
using Domain::Entities::UserEntity;
using Infrastructure::DAO::UserDAO;

class GetUserUseCase
{

public:
    UserDAO dao;
    GetUserUseCase() {
            this->dao = UserDAO();
    };
    ~GetUserUseCase() = default;
   UserEntity execute(const std::string &cod)
    {

        return this->dao.findByCode(cod);
    };
};
#pragma once
#include "../../Infrastructure/DAO/UserDAO.hpp"
#include "../../Domain/Entities/UserEntity.hpp"
using Domain::Entities::UserEntity;
using Infrastructure::DAO::UserDAO;
class GetUsersUseCase
{

public:
    UserDAO dao ;
    GetUsersUseCase() {
            this->dao = UserDAO();
    };
    ~GetUsersUseCase() = default;
    std::vector<UserEntity> execute()
    {

        return this->dao.all();
    };
};
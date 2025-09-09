#pragma once 
#include "../../Infrastructure/DAO/AuthorDAO.hpp"
#include "../../Domain/Entities/AuthorEntity.hpp"

using Domain::Entities::AuthorEntity;
using Infrastructure::DAO::AuthorDAO;

class GetAuthorsUseCase{

public:
    AuthorDAO dao;
    GetAuthorsUseCase(){
    this->dao =  AuthorDAO();

    }
    ~GetAuthorsUseCase() =  default;
    std::vector<AuthorEntity> execute(){
    
        return this->dao.all();
       }
};

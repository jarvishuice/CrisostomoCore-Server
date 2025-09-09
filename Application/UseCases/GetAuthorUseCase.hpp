#pragma once 
#include "../../Infrastructure/DAO/AuthorDAO.hpp"
#include "../../Domain/Entities/AuthorEntity.hpp"

using Domain::Entities::AuthorEntity;
using Infrastructure::DAO::AuthorDAO;

class GetAuthorUseCase{

public:
    AuthorDAO dao;
    GetAuthorUseCase(){
    this->dao =  AuthorDAO();

    }
    ~GetAuthorUseCase() =  default;
    std::vector<AuthorEntity> execute(std::string &cod){
    
        return this->dao.getByCod(cod);
       }
};

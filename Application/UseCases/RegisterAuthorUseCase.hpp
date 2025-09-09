#pragma once 
#include <ctime>
#include <string>
#include <iostream>
#include <cctype>
#include "../Helpers/UUIDHelper.hpp"
#include "../../Infrastructure/DAO/AuthorDAO.hpp"
#include "../../Domain/Entities/AuthorEntity.hpp"
using Domain::Entities::AuthorEntity;
using Infrastructure::DAO::AuthorDAO;


class RegisterAuthorUseCase{

public:
    AuthorDAO dao;
    
    RegisterAuthorUseCase(){
    this->dao =  AuthorDAO();

    };
    ~RegisterAuthorUseCase() =  default;
    std::string execute(AuthorEntity &entity){
        
       
     //   entity.cod =std::to_string(static_cast<long long>(std::time(nullptr)));
        entity.cod  =  generateUuidV4() ;
        return  this->dao.save(entity);
  
       };
};

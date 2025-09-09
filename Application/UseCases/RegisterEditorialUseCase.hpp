#pragma once 
#pragma once 
#include <ctime>
#include <string>
#include <iostream>
#include <cctype>

#include "../../Infrastructure/DAO/EditorialDAO.hpp"
#include "../../Domain/Entities/EditorialEntity.hpp"
#include "GetEditorialUseCase.hpp"
using Domain::Entities::EditorialEntity;
using Infrastructure::DAO::EditorialDAO;


class RegisterEditorialUseCase{

public:
    EditorialDAO dao;
    
    RegisterEditorialUseCase(){
    this->dao =  EditorialDAO();
 
    };
    ~RegisterEditorialUseCase() =  default;
    std::string execute(EditorialEntity &entity){
        
       
        entity.cod =std::to_string(static_cast<long long>(std::time(nullptr)));
        
        return  this->dao.save(entity);
  
       };
};


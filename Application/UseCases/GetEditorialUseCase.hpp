#pragma once 
#include "../../Infrastructure/DAO/EditorialDAO.hpp"
#include "../../Domain/Entities/EditorialEntity.hpp"

using Domain::Entities::EditorialEntity;
using Infrastructure::DAO::EditorialDAO;

class GetEditorialUseCase{

public:
    EditorialDAO dao;
    GetEditorialUseCase(){
    this->dao =  EditorialDAO();

    }
    ~GetEditorialUseCase() =  default;
    EditorialEntity execute(std::string &cod){
    
        return this->dao.findByCode(cod);
       }
};


#pragma once 
#include "../../Infrastructure/DAO/EditorialDAO.hpp"
#include "../../Domain/Entities/EditorialEntity.hpp"

using Domain::Entities::EditorialEntity;
using Infrastructure::DAO::EditorialDAO;

class GetEditorialsUseCase{

public:
    EditorialDAO dao;
    GetEditorialsUseCase(){
    this->dao =  EditorialDAO();

    }
    ~GetEditorialsUseCase() =  default;
    std::vector<EditorialEntity> execute(){
    
        return this->dao.all();
       }
};


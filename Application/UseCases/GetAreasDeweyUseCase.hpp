#pragma once 
#include "../../Infrastructure/DAO/CategoryDAO.hpp"
#include "../../Domain/Entities/CategoryEntity.hpp"
using Domain::Entities::CategoryEntity;
using Infrastructure::DAO::CategoryDAO;

class GetAreasDeweyUseCase{
public:
    CategoryDAO dao;
    GetAreasDeweyUseCase(){
    this->dao =  CategoryDAO();

    };
    ~GetAreasDeweyUseCase() = default;

    std::vector<CategoryEntity> execute(){
    
     return this->dao.allAreas();
    }
};
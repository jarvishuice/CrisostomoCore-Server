
#pragma once 
#include "../../Infrastructure/DAO/CategoryDAO.hpp"
#include "../../Domain/Entities/CategoryEntity.hpp"
using Domain::Entities::CategoryEntity;
using Infrastructure::DAO::CategoryDAO;

class GetCategoriesByParentCodeUseCase{
public:
    CategoryDAO dao;
    GetCategoriesByParentCodeUseCase(){
    this->dao =  CategoryDAO();

    };
    ~GetCategoriesByParentCodeUseCase() = default;

    std::vector<CategoryEntity> execute(std::string &codArea){
    
     return this->dao.getByParentID(codArea);
    }
};
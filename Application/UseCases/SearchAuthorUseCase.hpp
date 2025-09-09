#pragma once 
#include "../../Infrastructure/DAO/AuthorDAO.hpp"
#include "../../Domain/Entities/AuthorEntity.hpp"
#include <algorithm>
#include <cctype>

using Domain::Entities::AuthorEntity;
using Infrastructure::DAO::AuthorDAO;

class SearchAuthorUseCase{

public:
    AuthorDAO dao;
    SearchAuthorUseCase(){
    this->dao =  AuthorDAO();

    }
    ~SearchAuthorUseCase() =  default;
    std::vector<AuthorEntity> execute(std::string param){
       
        std::transform(param.begin(), param.end(), param.begin(), ::toupper);
        
        return this->dao.search(param);
       }
};
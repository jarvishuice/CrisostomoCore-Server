#pragma once
#include <uuid/uuid.h>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "../../Infrastructure/DAO/UserDAO.hpp"
#include "../../Domain/Entities/UserEntity.hpp"
#include "../Helpers/Sha256Helper.hpp"
#include "../../Infrastructure/Providers/Logs.hpp"

using Domain::Entities::UserEntity;
using Infrastructure::DAO::UserDAO;
using Application::Helpers::Sha256Helper;

class SingUpUseCase
{
public:
    UserDAO dao;
    Sha256Helper shaHelper;
    
    SingUpUseCase() {
        this->dao = UserDAO();
        this->shaHelper = Sha256Helper();
    };
    
    ~SingUpUseCase() = default;
  
    std::string execute(UserEntity &entity)
    {    
        auto &log = Logger::instance();
        try {
            std::time_t tiempoActual = std::time(nullptr);
            entity.cod.emplace(std::to_string(tiempoActual));
            
            // Convert firstname to uppercase
            std::transform(entity.firstname.begin(), entity.firstname.end(), 
                         entity.firstname.begin(), ::toupper);
            
            // Convert lastName to uppercase
            std::transform(entity.lastName.begin(), entity.lastName.end(), 
                         entity.lastName.begin(), ::toupper);
            
            // Hash the password
            entity.password = this->shaHelper.hash(entity.password);
            
            // Convert email to uppercase
            std::transform(entity.email.begin(), entity.email.end(), 
                         entity.email.begin(), ::toupper);
            
            // Convert middleName to uppercase if it exists
            if(entity.middleName.has_value()) {
                std::string middleNameUpper = entity.middleName.value();
                std::transform(middleNameUpper.begin(), middleNameUpper.end(), 
                             middleNameUpper.begin(), ::toupper);
                entity.middleName.emplace(middleNameUpper);
            }

            entity.validate();
            
            // Add the user and return the generated code
         
            return this->dao.add(entity);
        }
        catch (const std::exception& e) {
            log.error("error in execute: " + std::string(e.what()));
            std::cerr << "Error en execute: " << e.what() << std::endl;
            return "";
        }
    };
};
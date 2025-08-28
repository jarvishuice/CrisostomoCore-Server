#pragma once
#include <uuid/uuid.h>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "../../Infrastructure/DAO/UserDAO.hpp"
#include "../../Domain/Entities/UserEntity.hpp"
#include "../Helpers/Sha256Helper.hpp"
#include "../Helpers/JwtHelper.hpp"
#include "../../Infrastructure/Providers/Logs.hpp"

using Domain::Entities::UserEntity;
using Infrastructure::DAO::UserDAO;
using Application::Helpers::Sha256Helper;


class LoginUseCase
{
public:
    UserDAO dao;
    Sha256Helper shaHelper;
    JwtHelper jwt;    
    // LoginUseCase(){
    //     this->dao = UserDAO();
    //     this->shaHelper = Sha256Helper();
    //     this->jwt =JwtHelper("2fc78e5d45474badcabe0679a27f56c5ee058554212230a6ae88d428bd6409ff");
    // };
    LoginUseCase() 
    : dao(), shaHelper(), jwt("2fc78e5d45474badcabe0679a27f56c5ee058554212230a6ae88d428bd6409ff") 
{}
    ~LoginUseCase() = default;
  
    std::string execute(std::string param, std::string password)
{    
    auto& log = Logger::instance();
    try {
        JwtHelper helper = JwtHelper("2fc78e5d45474badcabe0679a27f56c5ee058554212230a6ae88d428bd6409ff");
        
        // Convertir el usuario a mayúsculas
        std::transform(param.begin(), param.end(), param.begin(), [](unsigned char c) {
            return std::toupper(c);
        });

        // Buscar usuario en la base de datos
        UserEntity user;
        try {
            user = this->dao.getUserByLogin(param);
        } catch (const std::exception& e) {
            throw std::runtime_error("El usuario no existe: " + param);
        }

        // Generar hash de la contraseña ingresada
        std::string hashedInput = this->shaHelper.hash(password);

        // Comparar con el hash almacenado
        if (hashedInput != user.password) {
            log.warn("Contraseña incorrecta para usuario: " + param);
            throw std::runtime_error("Clave invelidad"); // Autenticación fallida
        }

        // Generar JWT
        if (!user.cod.has_value()) {
            log.error("Usuario sin código válido: " + param);
            throw std::runtime_error("Usuario sin código válido");
        }
        
        std::string token = this->jwt.generateToken(user.cod.value());

        log.info("Login exitoso para usuario: " + param);
        return token;
    }
    catch (const std::exception& e) {
        log.error("Error en execute: " + std::string(e.what()));
        std::cerr << "Error en execute: " << e.what() << std::endl;
        return "";
    }
}

};
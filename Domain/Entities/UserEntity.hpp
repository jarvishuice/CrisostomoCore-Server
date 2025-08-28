#pragma once
#include "EntityBase.hpp"
#include <optional>
#include "../Validators/ValidatorsT.hpp"
#include <nlohmann/json.hpp>
namespace Domain::Entities
{

    class UserEntity : public EntityBase
    {
    public:
        std::optional<std::string> cod; // inicia como vacío
        std::string firstname;
        std::string lastName;
        std::optional<std::string> middleName;
        std::string username;
        std::string password;
        std::string email;
        std::string phone;
        std::string birthdate;
        std::string dateRegister;
        std::string dateUpdate;

        // Deserialización desde JSON
        void from_json(const nlohmann::json& j) override {
            if (j.contains("cod") && !j.at("cod").is_null())
                cod = j.at("cod").get<std::string>();
        
            if (j.contains("firstname") && j.at("firstname").is_string())
                firstname = j.at("firstname").get<std::string>();
        
            if (j.contains("lastName") && j.at("lastName").is_string())
                lastName = j.at("lastName").get<std::string>();
        
            if (j.contains("middleName") && j.at("middleName").is_string())
                middleName = j.at("middleName").get<std::string>();
        
            if (j.contains("username") && j.at("username").is_string())
                username = j.at("username").get<std::string>();
        
            if (j.contains("password") && j.at("password").is_string())
                password = j.at("password").get<std::string>();
        
            if (j.contains("email") && j.at("email").is_string())
                email = j.at("email").get<std::string>();
        
            if (j.contains("phone") && j.at("phone").is_string())
                phone = j.at("phone").get<std::string>();
        
            if (j.contains("birthDate") && j.at("birthDate").is_string())
                birthdate = j.at("birthDate").get<std::string>();
        
            if (j.contains("dateRegister") && j.at("dateRegister").is_string())
                dateRegister = j.at("dateRegister").get<std::string>();
        
            if (j.contains("dateUpdate") && j.at("dateUpdate").is_string())
                dateUpdate = j.at("dateUpdate").get<std::string>();
        
            validate();
        }
        
        // Serialización a JSON
        nlohmann::json to_json() const override
        {
            validate();
            nlohmann::json j;
            if (cod.has_value())
                j["cod"] = cod.value();
            j["firstname"] = firstname;
            j["lastName"] = lastName;
            j["middleName"] = middleName.has_value() ? middleName.value() : nullptr;
            j["username"] = username;
            j["password"] = password;
            j["email"] = email;
            j["phone"] = phone;
            j["birthdate"] = birthdate;
            j["dateRegister"] = dateRegister;
            j["dateUpdate"] = dateUpdate;
            
            return j;
        }

        // Validación de campos
        void validate() const override
        {
            Validators::Validator::validate_email(email);
            Validators::Validator::validate_phone(phone);
        }
    };
}
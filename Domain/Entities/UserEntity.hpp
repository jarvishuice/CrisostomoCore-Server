#pragma once
#include "EntityBase.hpp"
#include <optional>
#include "../Validators/ValidatorsT.hpp"
#include <nlohmann/json.hpp>
namespace Domain::Entities {

class UserEntity : public EntityBase {
public:
    std::optional<std::string> id;           // inicia como vacío
    std::string name;
    std::string lastName;
    std::optional<std::string> secondName;
    std::string email;
    std::string phone;
    std::string dni;
    std::string birthDate;
    std::string username;
    std::string password;
    std::string dateCreate;

    // Deserialización desde JSON
    void from_json(const nlohmann::json& j) override {
        if (j.contains("id") && !j.at("id").is_null())
            id = j.at("id").get<std::string>();

        name = j.at("name").get<std::string>();
        lastName = j.at("lastName").get<std::string>();

        if (j.contains("secondName") && !j.at("secondName").is_null())
            secondName = j.at("secondName").get<std::string>();

        email = j.at("email").get<std::string>();
        phone = j.at("phone").get<std::string>();
        dni = j.at("dni").get<std::string>();
        birthDate = j.at("birthDate").get<std::string>();
        username = j.at("username").get<std::string>();
        password = j.at("password").get<std::string>();
        dateCreate = j.at("dateCreate").get<std::string>();

        validate();
    }

    // Serialización a JSON
    nlohmann::json to_json() const override {
        nlohmann::json j;
        if (id.has_value()) j["id"] = id.value();
        j["name"] = name;
        j["lastName"] = lastName;
        j["secondName"] = secondName.has_value() ? secondName.value() : nullptr;
        j["email"] = email;
        j["phone"] = phone;
        j["dni"] = dni;
        j["birthDate"] = birthDate;
        j["username"] = username;
        j["password"] = password;
        j["dateCreate"] = dateCreate;
        return j;
    }

    // Validación de campos
    void validate() const override {
        Validators::Validator::validate_email(email);
        Validators::Validator::validate_phone(phone);
       
    }
};
}
#pragma once

#include "EntityBase.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <optional>

namespace Domain::Entities
{
    class AuthorEntity : public EntityBase
    {
    public:
        AuthorEntity(const std::string& jsonStr)
        {
            parseFromString(jsonStr);
        }

        AuthorEntity() = default;
        ~AuthorEntity() = default;

        std::string cod;
        std::string name;
        std::string dateCreated;
        std::string codUserCreated;
        std::string description;

        void parseFromString(const std::string& jsonStr)
        {
            try
            {
                auto j = nlohmann::json::parse(jsonStr);
                from_json(j);
            }
            catch (const nlohmann::json::parse_error& e)
            {
                throw std::invalid_argument(
                    std::string("Error al parsear JSON a AuthorEntity: ") + e.what());
            }
        }

        // Deserialización desde JSON
        void from_json(const nlohmann::json& j) override
        {
            if (j.contains("cod") && j.at("cod").is_string())
                cod = j.at("cod").get<std::string>();

            if (j.contains("name") && j.at("name").is_string())
                name = j.at("name").get<std::string>();

            if (j.contains("dateCreated") && j.at("dateCreated").is_string())
                dateCreated = j.at("dateCreated").get<std::string>();

            if (j.contains("codUserCreated") && j.at("codUserCreated").is_string())
            codUserCreated = j.at("codUserCreated").get<std::string>();

            if (j.contains("description") && j.at("description").is_string())
            description = j.at("description").get<std::string>();
        }

        // Serialización a JSON
        nlohmann::json to_json() const override
        {
            nlohmann::json j;
            j["cod"]            = cod;
            j["name"]           = name;
            j["dateCreated"]     = dateCreated;
            j["codUserCreated"]  = codUserCreated;
            j["description"]     = description;
            return j;
        }

        void validate() const override
        {
            // Aquí puedes añadir reglas de validación, por ejemplo:
            // if (cod.empty()) throw std::invalid_argument("cod no puede estar vacío");
        }
    };
}

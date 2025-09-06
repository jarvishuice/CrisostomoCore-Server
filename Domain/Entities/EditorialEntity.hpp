#pragma once
#include "EntityBase.hpp"
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
namespace Domain::Entities
{
    class EditorialEntity : public EntityBase
    {
    public:
        EditorialEntity(const std::string &jsonStr)
        {
            parseFromString(jsonStr);
        }
        EditorialEntity() = default;
        ~EditorialEntity() = default;
        std::string cod;
        std::string name;
        std::string dateCreated;
        std::string userCod;

        void parseFromString(const std::string &jsonStr)
        {
            try
            {
                auto j = nlohmann::json::parse(jsonStr);
                from_json(j);
            }
            catch (const nlohmann::json::parse_error &e)
            {
                throw std::invalid_argument(
                    std::string("Error al parsear JSON a EditorialEntity: ") + e.what());
            }
        }
        // Deserialización desde JSON
        void from_json(const nlohmann::json &j) override
        {
            if (j.contains("cod") && j.at("cod").is_string())
                cod = j.at("cod").get<std::string>();

            if (j.contains("name") && j.at("name").is_string())
                name = j.at("name").get<std::string>();

            if (j.contains("dateCreated") && j.at("dateCreated").is_string())
                dateCreated = j.at("dateCreated").get<std::string>();

            if (j.contains("userCod") && j.at("userCod").is_string())
                userCod = j.at("userCod").get<std::string>();
        }

        // Serialización a JSON
        nlohmann::json to_json() const override
        {

            nlohmann::json j;

            j["cod"] = cod;
            j["name"] = name;
            j["dateCreated"] = dateCreated;
            j["userCod"] = userCod;

            return j;
        }
        void validate() const override
        {
        }
    };
}
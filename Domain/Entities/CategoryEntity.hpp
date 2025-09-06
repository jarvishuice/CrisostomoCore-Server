#pragma once
#include "EntityBase.hpp"
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
namespace Domain::Entities
{
    class CategoryEntity : public EntityBase
    {
    public:
        CategoryEntity(const std::string &jsonStr)
        {
            parseFromString(jsonStr);
        }
        CategoryEntity() = default;
        ~CategoryEntity() = default;
        std::string cod;
        std::string name;
        std::string parentCod;
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
                    std::string("Error al parsear JSON a CategoryEntity: ") + e.what());
            }
        }
         // Deserialización desde JSON
         void from_json(const nlohmann::json &j) override
         {
             if (j.contains("cod") && j.at("cod").is_string())
                 cod = j.at("cod").get<std::string>();

             if (j.contains("name") && j.at("name").is_string())
                name = j.at("name").get<std::string>();

             if (j.contains("parentCod") && j.at("parentCod").is_string())
                parentCod = j.at("parentCod").get<std::string>();
         }


        // Serialización a JSON
        nlohmann::json to_json() const override
        {
           
            nlohmann::json j;
           
            j["cod"] = cod;
            j["name"] = name;
            j["parentCod"] = parentCod;
            
            

            return j;
        }
        void validate() const override
        {
            
        }
    };
}
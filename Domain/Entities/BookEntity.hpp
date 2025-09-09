#pragma once

#include "EntityBase.hpp"
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace Domain::Entities
{
    class BookEntity : public EntityBase
    {
    public:
        BookEntity(const std::string& jsonStr)
        {
            parseFromString(jsonStr);
        }

        BookEntity() = default;
        ~BookEntity() = default;

        std::string cod;
        std::string name;
        std::string description;
        std::string codUserUpload;
        std::string codEditorial;
        std::string codAuthor;
        std::string codArea;
        std::string codSubArea;
        std::string codCategory;
        std::string dateUpload;

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
                    std::string("Error al parsear JSON a BookEntity: ") + e.what());
            }
        }

        // Deserialización desde JSON
        void from_json(const nlohmann::json& j) override
        {
            if (j.contains("cod") && j.at("cod").is_string())
                cod = j.at("cod").get<std::string>();

            if (j.contains("name") && j.at("name").is_string())
                name = j.at("name").get<std::string>();

            if (j.contains("description") && j.at("description").is_string())
                description = j.at("description").get<std::string>();

            if (j.contains("codUserUpload") && j.at("codUserUpload").is_string())
                codUserUpload = j.at("codUserUpload").get<std::string>();

            if (j.contains("codEditorial") && j.at("codEditorial").is_string())
                codEditorial = j.at("codEditorial").get<std::string>();

            if (j.contains("codAuthor") && j.at("codAuthor").is_string())
                codAuthor = j.at("codAuthor").get<std::string>();

            if (j.contains("codArea") && j.at("codArea").is_string())
                codArea = j.at("codArea").get<std::string>();

            if (j.contains("codSubArea") && j.at("codSubArea").is_string())
                codSubArea = j.at("codSubArea").get<std::string>();

            if (j.contains("codCategory") && j.at("codCategory").is_string())
                codCategory = j.at("codCategory").get<std::string>();

            if (j.contains("dateUpload") && j.at("dateUpload").is_string())
                dateUpload = j.at("dateUpload").get<std::string>();
        }

        // Serialización a JSON
        nlohmann::json to_json() const override
        {
            nlohmann::json j;
            j["cod"]             = cod;
            j["name"]            = name;
            j["description"]     = description;
            j["codUserUpload"]   = codUserUpload;
            j["codEditorial"]    = codEditorial;
            j["codAuthor"]       = codAuthor;
            j["codArea"]         = codArea;
            j["codSubArea"]      = codSubArea;
            j["codCategory"]     = codCategory;
            j["dateUpload"]      = dateUpload;
            return j;
        }

        void validate() const override
        {
            // Añade aquí reglas de validación si es necesario
        }
    };
}

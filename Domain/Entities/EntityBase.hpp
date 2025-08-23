// BaseModel.hpp
#pragma once
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
namespace Domain::Entities
{
    class EntityBase
    {
    public:
        virtual ~EntityBase() = default;

        // Serializa el objeto a JSON
        virtual nlohmann::json to_json() const = 0;

        // Deserializa desde JSON
        virtual void from_json(const nlohmann::json &j) = 0;

        // Valida el modelo (puedes sobreescribir en tus clases hijas)
        virtual void validate() const
        {
            // Por defecto no hace nada
        }

        // Helper para convertir a string
        std::string to_string() const
        {
            return to_json().dump(4);
        }
    };
};

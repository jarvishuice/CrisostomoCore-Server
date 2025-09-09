
#include "AuthorDAO.hpp"
#include <pqxx/pqxx>
#include <iostream>

using namespace Infrastructure::DAO;

AuthorDAO::AuthorDAO() = default;
AuthorDAO::~AuthorDAO() = default;

std::vector<Domain::Entities::AuthorEntity> AuthorDAO::all()
{
    Logger::instance().info("AuthorDAO::all() called");
    ConnectionRAII conn;
    std::vector<Domain::Entities::AuthorEntity> res;

    try
    {
        pqxx::work txn(*conn);

        // Consulta segura y ordenada para la tabla author
        pqxx::result r = txn.exec(
            "SELECT a.cod, a.name, a.description,a.date_created,a.cod_user_created "
            "FROM public.author a "
            "ORDER BY a.name ASC"
        );

        res.reserve(r.size()); // Optimiza la reserva de memoria

        for (const auto &row : r)
        {
            Domain::Entities::AuthorEntity obj;
            obj.cod = row["cod"].as<std::string>();
            obj.name = row["name"].as<std::string>();
            obj.description =  row["description"].as<std::string>();
            obj.dateCreated = row["date_created"].as<std::string>();
            obj.codUserCreated = row["cod_user_created"].as<std::string>();

            res.emplace_back(std::move(obj));
        }

        Logger::instance().info("AuthorDAO::all() returned " + std::to_string(res.size()) + " records");
    }
    catch (const pqxx::sql_error &e)
    {
        Logger::instance().error("AuthorDAO::all() SQL error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("AuthorDAO::all() error: " + std::string(e.what()));
    }

    return res;
}

std::vector<Domain::Entities::AuthorEntity> AuthorDAO::search(const std::string &param){
    // Validar parámetro de entrada
    if (param.empty()) {
        Logger::instance().warn("AuthorDAO::search() called with empty cod parameter");
        return {};
    }
    auto  cod = "%"+param+"%";

    Logger::instance().info("AuthorDAO::search(" + param + ") called");
    ConnectionRAII conn;
    std::vector<Domain::Entities::AuthorEntity> res;
    
    try
    {
        pqxx::work txn(*conn);

        // Usar consulta con parámetros seguros
        pqxx::result r = txn.exec_params(
            "SELECT a.cod, a.name, a.description,a.date_created,a.cod_user_created "
            "FROM public.author a "
            "WHERE a.name ilike $1 or a.description ilike $2", 
            cod,cod
        );

        res.reserve(r.size());

        for (const auto &row : r)
        {
            Domain::Entities::AuthorEntity obj;
            obj.cod = row["cod"].as<std::string>();
            obj.name = row["name"].as<std::string>();
            obj.description =  row["description"].as<std::string>();
            obj.dateCreated = row["date_created"].as<std::string>();
            obj.codUserCreated = row["cod_user_created"].as<std::string>();

            res.emplace_back(std::move(obj));
        }

        if (res.empty()) {
            Logger::instance().warn("AuthorDAO::search(" + param + ") returned no results");
        } else {
            Logger::instance().info("AuthorDAO::search(" + param + ") returned " + std::to_string(res.size()) + " records");
        }
    }
    catch (const pqxx::sql_error &e)
    {
        Logger::instance().error("AuthorDAO::search(" + param + ") SQL error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("AuthorDAO::search(" + param + ") error: " + std::string(e.what()));
    }

    return res;
}


std::vector<Domain::Entities::AuthorEntity> AuthorDAO::getByCod(const std::string &cod)
{
    // Validar parámetro de entrada
    if (cod.empty()) {
        Logger::instance().warn("AuthorDAO::getByCod() called with empty cod parameter");
        return {};
    }

    Logger::instance().info("AuthorDAO::getByCod(" + cod + ") called");
    ConnectionRAII conn;
    std::vector<Domain::Entities::AuthorEntity> res;

    try
    {
        pqxx::work txn(*conn);

        // Usar consulta con parámetros seguros
        pqxx::result r = txn.exec_params(
            "SELECT a.cod, a.name, a.description,a.date_created,a.cod_user_created "
            "FROM public.author a "
            "WHERE a.cod = $1",
            cod
        );

        res.reserve(r.size());

        for (const auto &row : r)
        {
            Domain::Entities::AuthorEntity obj;
            obj.cod = row["cod"].as<std::string>();
            obj.name = row["name"].as<std::string>();
            obj.description =  row["description"].as<std::string>();
            obj.dateCreated = row["date_created"].as<std::string>();
            obj.codUserCreated = row["cod_user_created"].as<std::string>();

            res.emplace_back(std::move(obj));
        }

        if (res.empty()) {
            Logger::instance().warn("AuthorDAO::getByCod(" + cod + ") returned no results");
        } else {
            Logger::instance().info("AuthorDAO::getByCod(" + cod + ") returned " + std::to_string(res.size()) + " records");
        }
    }
    catch (const pqxx::sql_error &e)
    {
        Logger::instance().error("AuthorDAO::getByCod(" + cod + ") SQL error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("AuthorDAO::getByCod(" + cod + ") error: " + std::string(e.what()));
    }

    return res;
}

std::string AuthorDAO::save(const Domain::Entities::AuthorEntity &entity)
{
    Logger::instance().info("AuthorDAO::save() called for author: " + entity.name);
    ConnectionRAII conn;
    std::string result;

    try
    {
        pqxx::work txn(*conn);

        // Validar que la entidad tenga los campos requeridos
        if (entity.name.empty()) {
            Logger::instance().error("AuthorDAO::save() error: name is required");
            return "";
        }

        if (entity.cod.empty()) {
            Logger::instance().error("AuthorDAO::save() error: cod is required");
            return "";
        }

        // Insertar nuevo autor usando parámetros seguros
        pqxx::result r = txn.exec_params(
            "INSERT INTO public.author (cod, name, description,cod_user_created) "
            "VALUES ($1, $2, $3,$4) RETURNING cod",
            entity.cod,
            entity.name,
            entity.description,
            entity.codUserCreated// Valor por defecto según la estructura de la tabla
        );

        if (!r.empty()) {
            result = r[0]["cod"].as<std::string>();
            txn.commit();
            Logger::instance().info("AuthorDAO::save() successfully saved author with cod: " + result);
        } else {
            Logger::instance().error("AuthorDAO::save() error: no cod returned from insert");
        }
    }
    catch (const pqxx::sql_error &e)
    {
        Logger::instance().error("AuthorDAO::save() SQL error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("AuthorDAO::save() error: " + std::string(e.what()));
    }

    return result;
}

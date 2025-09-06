#include "EditorialDAO.hpp"
#include <pqxx/pqxx>
#include <iostream>

using namespace Infrastructure::DAO;
EditorialDAO::EditorialDAO() = default;
EditorialDAO::~EditorialDAO() = default;

std::vector<Domain::Entities::EditorialEntity> EditorialDAO::all()
{
    Logger::instance().info("EditorialDAO::all() called");
    ConnectionRAII conn;
    std::vector<Domain::Entities::EditorialEntity> res;

    try
    {
        pqxx::work txn(*conn);

        // Consulta segura y ordenada
        pqxx::result r = txn.exec(
            "SELECT ed.cod, ed.name, ed.date_create, ed.cod_user_upload "
            "FROM public.editorials ed "
            "ORDER BY ed.name ASC"
        );

        res.reserve(r.size()); // Optimiza la reserva de memoria

        for (const auto &row : r)
        {
            Domain::Entities::EditorialEntity obj;
            obj.cod = row["cod"].as<std::string>();
            obj.name = row["name"].as<std::string>();
            obj.dateCreated = row["date_create"].as<std::string>();
            obj.userCod = row["cod_user_upload"].as<std::string>();

            res.emplace_back(std::move(obj));
        }

        Logger::instance().info("EditorialDAO::all() returned " + std::to_string(res.size()) + " records");
    }
    catch (const pqxx::sql_error &e)
    {
        Logger::instance().error("EditorialDAO::all() SQL error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("EditorialDAO::all() error: " + std::string(e.what()));
    }

    return res;
}

Domain::Entities::EditorialEntity EditorialDAO::findByCode(const std::string &cod)
{
    // Validar parámetro de entrada
    if (cod.empty()) {
        Logger::instance().warn("EditorialDAO::findByCode() called with empty cod parameter");
        return {};
    }

    Logger::instance().info("EditorialDAO::findByCode(" + cod + ") called");
    ConnectionRAII conn;
    Domain::Entities::EditorialEntity res;

    try
    {
        pqxx::work txn(*conn);

        // Usar consulta con parámetros seguros
        pqxx::result r = txn.exec_params(
            "SELECT ed.cod, ed.name, ed.date_create, ed.cod_user_upload "
            "FROM public.editorials ed "
            "WHERE ed.cod = $1",
            cod
        );

        if (!r.empty()) {
            const auto &row = r.front();
            res.cod = row["cod"].as<std::string>();
            res.name = row["name"].as<std::string>();
            res.dateCreated = row["date_create"].as<std::string>();
            res.userCod = row["cod_user_upload"].as<std::string>();
        } else {
            Logger::instance().warn("EditorialDAO::findByCode(" + cod + ") returned no results");
        }
    }
    catch (const pqxx::sql_error &e)
    {
        Logger::instance().error("EditorialDAO::findByCode(" + cod + ") SQL error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("EditorialDAO::findByCode(" + cod + ") error: " + std::string(e.what()));
    }

    return res;
}


std::string EditorialDAO::save(const Domain::Entities::EditorialEntity &entity)
{
    Logger::instance().info("EditorialDAO::save() called for editorial: " + entity.name);
    ConnectionRAII conn;
    std::string result;

    try
    {
        pqxx::work txn(*conn);

        // Validar que la entidad tenga los campos requeridos
        if (entity.name.empty()) {
            Logger::instance().error("EditorialDAO::save() error: name is required");
            return "";
        }

        // Insertar nueva editorial usando parámetros seguros
        pqxx::result r = txn.exec_params(
            "INSERT INTO public.editorials (cod, name, cod_user_upload) "
            "VALUES ($1, $2, $3) RETURNING cod",
            entity.cod,
            entity.name,
            entity.userCod
        );

        if (!r.empty()) {
            result = r[0]["cod"].as<std::string>();
            txn.commit();
            Logger::instance().info("EditorialDAO::save() successfully saved editorial with cod: " + result);
        } else {
            Logger::instance().error("EditorialDAO::save() error: no cod returned from insert");
        }
    }
    catch (const pqxx::sql_error &e)
    {
        Logger::instance().error("EditorialDAO::save() SQL error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("EditorialDAO::save() error: " + std::string(e.what()));
    }

    return result;
}

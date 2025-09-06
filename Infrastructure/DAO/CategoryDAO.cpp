#include "CategoryDAO.hpp"
#include <pqxx/pqxx>
#include <iostream>
using namespace Infrastructure::DAO;
CategoryDAO::CategoryDAO() = default;
CategoryDAO::~CategoryDAO() = default;

std::vector<Domain::Entities::CategoryEntity> CategoryDAO::allAreas(){
    Logger::instance().info("CategoryDAO::allAreas() called");
    ConnectionRAII conn;
    std::vector<Domain::Entities::CategoryEntity> res;
    try
    {
        pqxx::work txn(*conn);
        // Usar consulta preparada para evitar SQL injection
        auto r = txn.exec("SELECT dc.cod, dc.name, dc.parentcod "
                         "FROM dewey_classification dc "
                         "WHERE dc.parentcod = '-1' "
                         "ORDER BY dc.cod");

        for (auto const &row : r)
        {
            Domain::Entities::CategoryEntity obj = Domain::Entities::CategoryEntity();
            obj.cod = row["cod"].as<std::string>();
            obj.name = row["name"].as<std::string>();
            obj.parentCod = row["parentcod"].as<std::string>();
           
            res.push_back(std::move(obj));
        }

        Logger::instance().info("CategoryDAO::allAreas() returned " + std::to_string(res.size()) + " records");
    }
    catch (const pqxx::sql_error &e)
    {
        Logger::instance().error("CategoryDAO::allAreas() SQL error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("CategoryDAO::allAreas() error: " + std::string(e.what()));
    }
    return res;
}
std::vector<Domain::Entities::CategoryEntity> CategoryDAO::getByParentID(const std::string &cod){
    // Validar parámetro de entrada
    if (cod.empty()) {
        Logger::instance().warn("CategoryDAO::getByParentID() called with empty cod parameter");
        return {};
    }
    
    Logger::instance().info("CategoryDAO::getByParentID("+ cod +") called");
    ConnectionRAII conn;
    std::vector<Domain::Entities::CategoryEntity> res;
    try
    {
        pqxx::work txn(*conn);
        // Usar consulta preparada para evitar SQL injection
        conn->prepare("get_by_parent", 
            "SELECT dc.cod, dc.name, dc.parentcod "
            "FROM dewey_classification dc "
            "WHERE dc.parentcod = $1 "
            "ORDER BY dc.cod");
        
        auto r = txn.prepared("get_by_parent")(cod).exec();


        for (auto const &row : r)
        {
            Domain::Entities::CategoryEntity obj = Domain::Entities::CategoryEntity();
            obj.cod = row["cod"].as<std::string>();
            obj.name = row["name"].as<std::string>();
            obj.parentCod = row["parentcod"].as<std::string>();
           
            res.push_back(std::move(obj));
        }

        Logger::instance().info("CategoryDAO::getByParentID("+ cod +") returned " + std::to_string(res.size()) + " records");
    }
    catch (const pqxx::sql_error &e)
    {
        Logger::instance().error("CategoryDAO::getByParentID("+ cod +") SQL error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("CategoryDAO::getByParentID("+ cod +") error: " + std::string(e.what()));
    }
    return res;
}
#include "UserDAO.hpp"
#include <pqxx/pqxx> // o tu cabecera de PQXX
#include <iostream>  // solo si haces debug con std::cerr

using namespace Infrastructure::DAO;

// Definimos el constructor y el destructor (key function)
UserDAO::UserDAO() = default;
UserDAO::~UserDAO() = default;

std::vector<Domain::Entities::UserEntity> UserDAO::all()
{
    Logger::instance().info("UserDAO::all() called");

    ConnectionRAII conn;
    std::vector<Domain::Entities::UserEntity> res;
    try
    {
        pqxx::work txn(*conn);
        auto r = txn.exec("SELECT * FROM app_user");

        for (auto const &row : r)
        {
            Domain::Entities::UserEntity u = Domain::Entities::UserEntity();
            u.cod = row["cod"].as<std::string>();
            u.firstname = row["firstname"].as<std::string>();
            u.lastName = row["last_name"].as<std::string>();
            if(!row["middle_name"].is_null()){
                u.middleName = row["middle_name"].as<std::string>();
            }
          
            u.username = row["username"].as<std::string>();
            u.password = row["password"].as<std::string>();
            u.email = row["email"].as<std::string>();
            u.phone = row["phone"].as<std::string>();
            u.birthdate = row["birthdate"].as<std::string>();
            u.dateRegister = row["date_register"].as<std::string>();
            u.dateUpdate = row["date_update"].as<std::string>();
            res.push_back(std::move(u));
        }

        Logger::instance().info("UserDAO::all() returned " + std::to_string(res.size()) + " records");
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("UserDAO::all() error: " + std::string(e.what()));
    }
    return res;
}

Domain::Entities::UserEntity UserDAO::findByCode(const std::string &cod)
{
    Logger::instance().info("UserDAO::findByCode(" + cod + ") called");

    ConnectionRAII conn;
    Domain::Entities::UserEntity res;
    try
    {
        pqxx::work txn(*conn);
        auto query = "SELECT * FROM app_user WHERE cod = " + txn.quote(cod);
        auto r = txn.exec(query);

        if (!r.empty())
        {
            auto const &row = r.front();
            res.cod = row["cod"].as<std::string>();
            res.firstname = row["firstname"].as<std::string>();
            res.lastName = row["last_name"].as<std::string>();
           
            res.username = row["username"].as<std::string>();
            res.password = row["password"].as<std::string>();
            res.email = row["email"].as<std::string>();
            res.phone = row["phone"].as<std::string>();
            res.birthdate = row["birthdate"].as<std::string>();
            res.dateRegister = row["date_register"].as<std::string>();
            res.dateUpdate = row["date_update"].as<std::string>();
        }
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("UserDAO::findByCode() error: " + std::string(e.what()));
    }
    return res;
}
Domain::Entities::UserEntity UserDAO::getUserByLogin(std::string param)
{
    Logger::instance().info("UserDAO::findByCode(" + param + ") called");

    ConnectionRAII conn;
    Domain::Entities::UserEntity res;
    try
    {
        pqxx::work txn(*conn);
        auto query = "SELECT * FROM app_user WHERE username = " + txn.quote(param) + " or email= " + txn.quote(param) +" or phone= " + txn.quote(param);
        auto r = txn.exec(query);

        if (!r.empty())
        {
            auto const &row = r.front();
            res.cod = row["cod"].as<std::string>();
            res.firstname = row["firstname"].as<std::string>();
            res.lastName = row["last_name"].as<std::string>();
            if (!row["middle_name"].is_null())
                res.middleName = row["middle_name"].as<std::string>();
            res.username = row["username"].as<std::string>();
            res.password = row["password"].as<std::string>();
            res.email = row["email"].as<std::string>();
            res.phone = row["phone"].as<std::string>();
            res.birthdate = row["birthdate"].as<std::string>();
            res.dateRegister = row["date_register"].as<std::string>();
            res.dateUpdate = row["date_update"].as<std::string>();
        }
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("UserDAO::findByCode() error: " + std::string(e.what()));
    }
    return res;
}       

std::string UserDAO::add(const Domain::Entities::UserEntity& user)
{
    Logger::instance().info("UserDAO::add() called for user: " + user.username);
    std::cout << "UserDAO::add() called for user: " << user.username <<"esto es lo que llega al daO" << std::endl;
   
    ConnectionRAII conn;
    std::string result = "error";
    try
    {
        pqxx::work txn(*conn);
        
        // Prepare the INSERT query
        auto query = "INSERT INTO app_user (cod, firstname, last_name, middle_name, username, password, email, phone, birthdate, date_register, date_update) "
                     "VALUES (" + txn.quote(user.cod) + ", " +
                     txn.quote(user.firstname) + ", " +
                     txn.quote(user.lastName) + ", " +
                     (user.middleName.has_value() ? txn.quote(user.middleName.value()) : "NULL") + ", " +
                     txn.quote(user.username) + ", " +
                     txn.quote(user.password) + ", " +
                     txn.quote(user.email) + ", " +
                     txn.quote(user.phone) + ", " +
                     "now()"+ ", " +
                     "now()" + ", " +
                     "now()" + ")";
        
        // Execute the query
        txn.exec(query);
        
        // Commit the transaction
        txn.commit();
        
        result = "success";
        Logger::instance().info("UserDAO::add() successful for user: " + user.username);
    }
    catch (const std::exception &e)
    {
        Logger::instance().error("UserDAO::add() error: " + std::string(e.what()));
        result = "error: " + std::string(e.what());
    }
    
    return result;
}
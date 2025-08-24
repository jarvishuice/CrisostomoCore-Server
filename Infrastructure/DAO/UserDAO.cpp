#include "UserDAO.hpp"
#include <pqxx/pqxx>    // o tu cabecera de PQXX
#include <iostream>     // solo si haces debug con std::cerr

using namespace Infrastructure::DAO;

// Definimos el constructor y el destructor (key function)
UserDAO::UserDAO() = default;
UserDAO::~UserDAO() = default;

std::vector<Domain::Entities::UserEntity> UserDAO::all() {
    Logger::instance().info("UserDAO::all() called");

    ConnectionRAII conn;
    std::vector<Domain::Entities::UserEntity> res;
    try {
        pqxx::work txn(*conn);
        auto r = txn.exec("SELECT * FROM app_user");

        for (auto const& row : r) {
            Domain::Entities::UserEntity u;
            u.cod         = row["cod"].as<std::string>();
            u.firstname   = row["firstname"].as<std::string>();
            u.lastName    = row["last_name"].as<std::string>();
            if (!row["middle_name"].is_null())
                u.middleName = row["middle_name"].as<std::string>();
            u.username    = row["username"].as<std::string>();
            u.password    = row["password"].as<std::string>();
            u.email       = row["email"].as<std::string>();
            u.phone       = row["phone"].as<std::string>();
            u.birthdate   = row["birthdate"].as<std::string>();
            u.dateRegister= row["date_register"].as<std::string>();
            u.dateUpdate  = row["date_update"].as<std::string>();
            res.push_back(std::move(u));
        }

        Logger::instance().info("UserDAO::all() returned " + std::to_string(res.size()) + " records");
    }
    catch (const std::exception& e) {
        Logger::instance().error("UserDAO::all() error: " + std::string(e.what()));
    }
    return res;
}

Domain::Entities::UserEntity UserDAO::findByCode(const std::string& cod) {
    Logger::instance().info("UserDAO::findByCode(" + cod + ") called");

    ConnectionRAII conn;
    Domain::Entities::UserEntity res;
    try {
        pqxx::work txn(*conn);
        auto query = "SELECT * FROM app_user WHERE cod = " + txn.quote(cod);
        auto r     = txn.exec(query);

        if (!r.empty()) {
            auto const& row = r.front();
            res.cod         = row["cod"].as<std::string>();
            res.firstname   = row["firstname"].as<std::string>();
            res.lastName    = row["last_name"].as<std::string>();
            if (!row["middle_name"].is_null())
                res.middleName = row["middle_name"].as<std::string>();
            res.username    = row["username"].as<std::string>();
            res.password    = row["password"].as<std::string>();
            res.email       = row["email"].as<std::string>();
            res.phone       = row["phone"].as<std::string>();
            res.birthdate   = row["birthdate"].as<std::string>();
            res.dateRegister= row["date_register"].as<std::string>();
            res.dateUpdate  = row["date_update"].as<std::string>();
        }
    }
    catch (const std::exception& e) {
        Logger::instance().error("UserDAO::findByCode() error: " + std::string(e.what()));
    }
    return res;
}

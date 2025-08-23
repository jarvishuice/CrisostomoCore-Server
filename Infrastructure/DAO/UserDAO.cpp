#include "../../Domain/IDAO/IUserDAO.hpp"
#include "../Providers/Logs.hpp"
#include "../Providers/ConnectionRAII.hpp"
#include <pqxx/pqxx>
class UserDAO:public Domain::IDAO::IUserDAO{
    Logger &log = Logger::instance();
    public:
        UserDAO(){};
        ~UserDAO()=default;;

        std::vector<Domain::Entities::UserEntity> all() override {
            log.info("UserDAO::all() called");
              ConnectionRAII conn; // adquiere conexión RAII
        std::vector<Domain::Entities::UserEntity> res;
        try
        {
            pqxx::work txn(*conn);
            pqxx::result r = txn.exec("SELECT * from app_user");

            for (const auto &row : r)
            {
                Domain::Entities::UserEntity p;
                p.cod =row["cod"].as<std::string>();
                p.firstname = row["firstname"].as<std::string>();
                p.lastName = row["lastName"].as<std::string>();
                if (!row["middleName"].is_null())
                    p.middleName = row["middleName"].as<std::string>();
                p.username = row["username"].as<std::string>();
                p.password = row["password"].as<std::string>();
                p.email = row["email"].as<std::string>();
                p.phone = row["phone"].as<std::string>();
                p.birthdate = row["birthdate"].as<std::string>();
                p.dateRegister = row["dateRegister"].as<std::string>();
                p.dateUpdate = row["dateUpdate"].as<std::string>();
                
                res.push_back(p);
            }
            log.info("TOP TEND RES " + std::to_string(res.size()));
            return res;
        }
        catch (const std::exception &e)
        {
            log.error("Error en getTypeUser: " + std::string(e.what()));
            return {};
        }
            };

};
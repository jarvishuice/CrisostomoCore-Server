#pragma once

#include "../../Domain/IDAO/IUserDAO.hpp"
#include "../Providers/Logs.hpp"
#include "../Providers/ConnectionRAII.hpp"

namespace Infrastructure::DAO {

class UserDAO : public Domain::IDAO::IUserDAO {
public:
    UserDAO();
    ~UserDAO() override;

    std::vector<Domain::Entities::UserEntity> all() override;
    Domain::Entities::UserEntity            findByCode(const std::string& cod) override;
    Domain::Entities::UserEntity getUserByLogin(std::string param) override;
    std::string add(const Domain::Entities::UserEntity& user) override;

};

} // namespace Infrastructure::DAO

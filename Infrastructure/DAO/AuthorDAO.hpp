#pragma once
#include "../../Domain/IDAO/IAuthorDAO.hpp"
#include "../Providers/Logs.hpp"
#include "../Providers/ConnectionRAII.hpp"

namespace Infrastructure::DAO
{

    class AuthorDAO : public Domain::IDAO::IAuthorDAO
    {
    public:
        AuthorDAO();
        ~AuthorDAO() override;

        std::vector<Domain::Entities::AuthorEntity> all() override;
        std::string save(const Domain::Entities::AuthorEntity &entity) override;
        std::vector<Domain::Entities::AuthorEntity> getByCod(const std::string &cod) override;
        std::vector<Domain::Entities::AuthorEntity> search(const std::string &param) override;
    };

} // namespace Infrastructure::DAO
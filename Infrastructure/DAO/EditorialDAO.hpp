#pragma once
#include "../../Domain/IDAO/IEditorialDAO.hpp"
#include "../Providers/Logs.hpp"
#include "../Providers/ConnectionRAII.hpp"
namespace Infrastructure::DAO
{

    class EditorialDAO : public Domain::IDAO::IEditorialDAO
    {
    public:
        EditorialDAO();
        ~EditorialDAO() override;

        std::vector<Domain::Entities::EditorialEntity> all() override;
        Domain::Entities::EditorialEntity findByCode(const std::string &cod) override;
        std::string save(const Domain::Entities::EditorialEntity &entity) override;
    };

} // namespace Infrastructure::DAO

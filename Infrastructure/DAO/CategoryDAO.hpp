#pragma once
#include "../../Domain/IDAO/ICategoryDAO.hpp"
#include "../Providers/Logs.hpp"
#include "../Providers/ConnectionRAII.hpp"
namespace Infrastructure::DAO
{

    class CategoryDAO : public Domain::IDAO::ICategoryDAO
    {
    public:
        CategoryDAO();
        ~CategoryDAO() override;

        std::vector<Domain::Entities::CategoryEntity> allAreas()  override;
        std::vector<Domain::Entities::CategoryEntity> getByParentID(const std::string &cod)  override;
    };

}// namespace Infrastructure::DAO

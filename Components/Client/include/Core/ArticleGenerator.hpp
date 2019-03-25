//!
//! @file ArticleGenerator.hpp
//! @author jbruel
//! @date 25/12/18
//!

#ifndef CASH_MANAGER_CLIENT_CORE_ARTICLEGENERATOR_HPP
# define CASH_MANAGER_CLIENT_CORE_ARTICLEGENERATOR_HPP

#include <QtCore/QString>
#include <Network/WarehouseAPI.hpp>
#include "Network/NetworkInfo.hpp"

//!
//! @namespace cash
//!
namespace cash
{
//!
//! @namespace cash
//!
namespace core
{

    //!
    //! @class ArticleGenerator
    //! @brief Article generator.
    //!
    class   ArticleGenerator
    {
    private:
        //!
        //! @var const std::string ArticleRef
        //! @brief Article reference.
        //!
        const std::string ArticleRef = "                                                                    ";

    private:
        network::WarehouseAPI   mDBAPI; //!< API for DB articles.

    public:
        //!
        //! @brief Constructor.
        //!
        ArticleGenerator() : mDBAPI(WAREHOUSE_URL, WAREHOUSE_PORT) {}
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        ArticleGenerator(const ArticleGenerator &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Bill copy.
        //! @warning Not available.
        //!
        ArticleGenerator &operator=(const ArticleGenerator &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~ArticleGenerator() = default;

    public:
        //!
        //! @brief Generate article string.
        //! @param articlePrice Price.
        //! @return Article description.
        //!
        QString generate(double &articlePrice);

    private:
        //!
        //! @brief Generate a random number.
        //! @param max Max generated number.
        //! @return Random generated number.
        //!
        size_t  generateRandomNumber(size_t max) const;

    private:
        //!
        //! @brief Add spaces to article name;
        //! @param quantity Article quantity.
        //! @param article Article description.
        //! @param price Article price.
        //!
//        void    addSpacesToArticleName(const std::string &quantity, std::string &article, const std::string &price) const;
    };

}
}

#endif //CASH_MANAGER_CLIENT_CORE_ARTICLEGENERATOR_HPP

//
// Created by grosso_a on 06/12/18.
//

#ifndef CASH_MANAGER_CLIENT_WAREHOUSEAPI_HPP
#define CASH_MANAGER_CLIENT_WAREHOUSEAPI_HPP

#include <Network/NetworkAPI.hpp>
#include <Network/Request/ArticleList.hpp>
#include <Network/Request/ArticleScan.hpp>

namespace cash
{
    namespace network
    {
        /**
         * @class WarehouseAPI
         * @brief Class used to interact with the warehouse server
         */
        class WarehouseAPI: public cash::network::NetworkAPI
        {
        Q_OBJECT
        public:
            /**
             * @brief WarehouseAPI constructor
             * @param url The server warehouse url
             * @param port The server warehouse port
             */
            WarehouseAPI(const std::string &url, unsigned int port): cash::network::NetworkAPI(url, port) {}

            /**
             * @brief List all articles available on server
             * @return List of article objects
             */
            cash::network::ArticleList *articles();

            /**
             * @brief Select article by id or by name
             * @return Article object if available else nullptr.
             */
            cash::network::ArticleScan *scan(const std::string &id, const std::string &name);
       };
    }
}

#endif //CASH_MANAGER_CLIENT_WAREHOUSEAPI_HPP

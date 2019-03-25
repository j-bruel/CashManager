//
// Created by grosso_a on 16/12/18.
//

#ifndef CASH_MANAGER_CLIENT_ARTICLESCAN_HPP
#define CASH_MANAGER_CLIENT_ARTICLESCAN_HPP

#include <Network/ARequest.hpp>
#include <QJsonObject>
#include <Network/Request/Article.hpp>

namespace cash
{
    namespace network
    {
        /**
         * @class ArticleScan
         * @brief Request to select one article on server.
         */
        class ArticleScan: public cash::network::ARequest, std::enable_shared_from_this<ArticleScan>
        {
        Q_OBJECT
        signals:
            /**
             * @brief QT signal called when data are ready.
             */
            void deserialized(cash::network::ArticleScan *);

        protected:
            /**
             * @brief Deserialize data from QJsonDocument to internal data
             * @param json Data provided by server and parsed by QTJson
             * @return True if data are valid or False.
             */
            bool deserialize(std::shared_ptr<QJsonDocument> json) final;

        public:
            /**
             * @brief ArticleScan request constructor
             */
            ArticleScan();

            /**
             * @brief Get article result of scan.
             * @return Article object or null if not found
             */
            Article *article();

            /**
             * @brief ArticleScan destructor
             */
            ~ArticleScan() final;

        private:
            Article     *_article;
        };
    }
}

#endif //CASH_MANAGER_CLIENT_ARTICLESCAN_HPP

//
// Created by grosso_a on 16/12/18.
//

#ifndef CASH_MANAGER_CLIENT_ARTICLELIST_HPP
#define CASH_MANAGER_CLIENT_ARTICLELIST_HPP

#include <Network/ARequest.hpp>
#include <QJsonObject>
#include <QJsonArray>
#include <Network/Request/Article.hpp>

namespace cash
{
    namespace network
    {
        /**
         * @class ArticleList
         * @brief List all articles available on server
         */
        class ArticleList: public cash::network::ARequest, std::enable_shared_from_this<ArticleList>
        {
        Q_OBJECT
        signals:
            /**
             * @brief QT signal call when article list is ready
             */
            void deserialized(cash::network::ArticleList *);

        private:
            std::list<Article*>  _articles;

        protected:

            /**
             * @brief Deserialize data from QJsonDocument to internal data
             * @param json Json response of server
             * @return True if data is correct else False.
             */
            bool deserialize(std::shared_ptr<QJsonDocument> json) final;

        public:
            /**
             * @brief ArticleList constructor
             */
            ArticleList();

            /**
             * @brief List articles of server
             * @return List of article objects
             */
            std::list<Article*>  &articles();


            /**
             * @brief ArticleList destructor
             */
            virtual ~ArticleList();
        };
    }
}

#endif //CASH_MANAGER_CLIENT_ARTICLELIST_HPP

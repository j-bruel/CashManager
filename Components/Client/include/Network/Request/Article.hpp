//
// Created by grosso_a on 26/12/18.
//

#ifndef CASH_MANAGER_CLIENT_ARTICLE_HPP
#define CASH_MANAGER_CLIENT_ARTICLE_HPP

#include <string>
#include <QJsonObject>

namespace cash
{
    namespace network
    {
        /**
         * @class Article
         * @brief Article from warehouse
         */
        class Article
        {
        private:
            int             _id;
            std::string     _name;
            double           _price;
            int             _stock_size;

        public:
            /**
             * @brief Article contructor
             * @param object Json object parsed with qjson
             */
            Article(const QJsonObject &object);

            /**
             * @brief Article id getter
             * @return article auto-generated id
             */
            int id();

            /**
             * @brief Article name getter
             * @return article name
             */
            const std::string &name();

            /**
             * @brief Article price getter
             * @return article price
             */
            double price();


            /**
             * @brief Article stock size getter
             * @return article stock_size
             */
            int stock_size();
        };
    }
}

#endif //CASH_MANAGER_CLIENT_ARTICLE_HPP

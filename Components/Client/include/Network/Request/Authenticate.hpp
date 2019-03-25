//
// Created by grosso_a on 16/12/18.
//

#ifndef CASH_MANAGER_CLIENT_AUHTENTICATE_HPP
#define CASH_MANAGER_CLIENT_AUHTENTICATE_HPP

#include <Network/ARequest.hpp>
#include <iostream>
#include <memory>
#include <QJsonObject>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace cash
{
    namespace network
    {
        /**
         * @class Authenticate
         * @brief Get authentication token to validate payment.
         */
        class Authenticate: public cash::network::ARequest, std::enable_shared_from_this<Authenticate>
        {
        Q_OBJECT
        signals:
            /**
             * @brief QT signal called when data are ready.
             */
            void deserialized(cash::network::Authenticate *);

        private:
            std::string     _token;
            std::string     _type;
            std::time_t     _created;
            std::time_t     _expire;

        protected:
            /**
             * @brief Convert string datetime to time_t
             * @param dateTime Datetime on format %Y-%m-%dT%H:%M:%SZ to convert.
             * @return time_t datetime converted
             */
            std::time_t parseTime(const std::string& dateTime);

            /**
             * @brief Deserialize data from QJsonDocument to internal data
             * @param json Data provided by server and parsed by QTJson
             * @return True if data are valid or False.
             */
            bool deserialize(std::shared_ptr<QJsonDocument> json) final;

        public:
            /**
             * @brief Authenticate constructor
             */
            Authenticate();

            /**
             * @brief Token getter
             * @return token
             */
            const std::string &token();

            /**
             * @brief Created time_t getter
             * @return created time_t
             */
            std::time_t created();


            /**
             * @brief Expire time_t getter
             * @return expire time_t
             */
            std::time_t expire();

            /**
             * @brief Type getter
             * @return type
             */
            const std::string &type();

            /**
             * @brief Authenticate destructor
             */
            ~Authenticate() final;
        };
    }
}

#endif //CASH_MANAGER_CLIENT_AUHTENTICATE_HPP

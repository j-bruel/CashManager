//
// Created by grosso_a on 16/12/18.
//

#ifndef CASH_MANAGER_CLIENT_BANKCHECK_HPP
#define CASH_MANAGER_CLIENT_BANKCHECK_HPP

#include <Network/ARequest.hpp>
#include <QJsonObject>

namespace cash
{
    namespace network
    {
        /**
         * @class BankCheck
         * @brief Request to pay on check bank.
         */
        class BankCheck: public cash::network::ARequest, std::enable_shared_from_this<BankCheck>
        {
        Q_OBJECT
        signals:
            /**
             * @brief QT signal called when data are ready.
             */
            void deserialized(cash::network::BankCheck *);

        protected:
            /**
             * @brief Deserialize data from QJsonDocument to internal data
             * @param json Data provided by server and parsed by QTJson
             * @return True if data are valid or False.
             */
            bool deserialize(std::shared_ptr<QJsonDocument> json) final;

        public:
            /**
             * @brief BankCheck request constructor
             */
            BankCheck();

            /**
             * @brief Token getter
             */
            const std::string &token();

            /**
             * @brief Payment type getter
             */
            const std::string &type();

            /**
             * @brief Account number
             */
            const std::string &number();

            /**
             * @brief Transaction id auto generated
             */
            const std::string &transaction_id();

            /**
             * @brief Transaction amount
             */
            int amount();

            /**
             * @brief BankCheck destructor
             */
            ~BankCheck() final;

        private:
            std::string     _token;
            std::string     _type;
            std::string     _check_number;
            std::string     _transaction;
            int             _amount;
        };
    }
}

#endif //CASH_MANAGER_CLIENT_BANKCHECK_HPP

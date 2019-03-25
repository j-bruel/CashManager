//
// Created by grosso_a on 16/12/18.
//

#ifndef CASH_MANAGER_CLIENT_CARDPAYMENTCONTACTLESS_HPP
#define CASH_MANAGER_CLIENT_CARDPAYMENTCONTACTLESS_HPP

#include <Network/ARequest.hpp>
#include <QJsonObject>

namespace cash
{
    namespace network
    {
        /**
         * @class CardPaymentContactless
         * @brief Contactless card payment request
         */
        class CardPaymentContactless: public cash::network::ARequest, std::enable_shared_from_this<CardPaymentContactless>
        {
        Q_OBJECT
        signals:
            /**
             * @brief QT signal called when data are ready.
             */
            void deserialized(cash::network::CardPaymentContactless *);

        protected:
            /**
             * @brief Deserialize data from QJsonDocument to internal data
             * @param json Data provided by server and parsed by QTJson
             * @return True if data are valid or False.
             */
            bool deserialize(std::shared_ptr<QJsonDocument> json) final;

        public:
            /**
             * @brief CardPaymentContactless constructor
             */
            CardPaymentContactless();

            /**
             * @brief Token used to validate payment
             */
            const std::string &token();

            /**
             * @brief Payment type
             */
            const std::string &type();

            /**
             * @brief Card type (VISA, MASTER, ELECTRON)
             */
            const std::string &card_type();

            /**
             * @brief Card payment number
             */
            const std::string &card_number();

            /**
             * @brief Payment id
             */
            const std::string &transaction_id();

            /**
             * @brief Payment amount
             */
            int amount();

            /**
             * @brief CardPaymentContactless destructor
             */
            virtual ~CardPaymentContactless();

        private:
            std::string     _token;
            std::string     _type;
            std::string     _card_type;
            std::string     _card_number;
            std::string     _transaction;
            int             _amount;
        };
    }
}

#endif //CASH_MANAGER_CLIENT_CARDPAYMENTCONTACTLESS_HPP

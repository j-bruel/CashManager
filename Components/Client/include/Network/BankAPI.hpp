//
// Created by grosso_a on 06/12/18.
//

#ifndef CASH_MANAGER_CLIENT_QBANKAPI_HPP
#define CASH_MANAGER_CLIENT_QBANKAPI_HPP

#include <Network/NetworkAPI.hpp>
#include <Network/Request/CardPayment.hpp>
#include <Network/Request/Authenticate.hpp>
#include <Network/Request/CardPaymentContactless.hpp>
#include <Network/Request/BankCheck.hpp>

namespace cash
{
    namespace network
    {
        /**
         * @class BankAPI
         * @brief Class used to interact with the bank server
         */
        class BankAPI: public cash::network::NetworkAPI
        {
        Q_OBJECT
        private:
            std::string             clean_spaces(std::string);

        public:
            /**
             * @brief BankAPI constructor
             * @param url The server bank url
             * @param port The server bank port
             */
            BankAPI(const std::string &url, unsigned int port): cash::network::NetworkAPI(url, port) {}

            /**
             * @brief Authenticate request
             * @param payment_type Payment type token (CARD, CONTACTELESS, CHECK)
             * @param try_count Number of try of this token
             * @param timeout Request timeout
             * @return Authenticate request object
             */
            cash::network::Authenticate *authenticate(
                    const std::string &payment_type,
                    int try_count,
                    unsigned int timeout = 500);

            /**
             * @brief Card payment request
             * @param token Payment validation token
             * @param payment_type Payment type token (CARD, CONTACTELESS, CHECK)
             * @param card_number Card number. (16 digits)
             * @param pin Card private code. (4 digits)
             * @param amount Transaction amount value
             * @param timeout Request timeout
             * @return CardPayment request object
             */
            cash::network::CardPayment *card_payment(
                    const std::string &token,
                    const std::string &card_type,
                    const std::string &card_number,
                    const std::string &pin,
                    float amount,
                    unsigned int timeout = 500);

            /**
             * @brief Card contactless payment request
             * @param token Payment validation token
             * @param card_type Card type (VISA, MASTER, ELECTRON)
             * @param card_number Card number. (16 digits)
             * @param amount Transaction amount value
             * @param timeout Request timeout
             * @return CardPaymentContactless request object
             */
            cash::network::CardPaymentContactless *card_payment_contactless(
                    const std::string &token,
                    const std::string &card_type,
                    const std::string &card_number,
                    float amount,
                    unsigned int timeout = 500);

            /**
             * @brief Check payment request
             * @param token Payment validation token
             * @param check_number Check number. (11 alphanumeric)
             * @param amount Transaction amount value
             * @param timeout Request timeout
             * @return CheckPayment request object
             */
            cash::network::BankCheck *check_payment(
                    const std::string &token,
                    const std::string &check_number,
                    float amount,
                    unsigned int timeout = 500);
       };
    }
}

#endif //CASH_MANAGER_CLIENT_QBANKAPI_HPP

//
// Created by grosso_a on 19/12/18.
//

#ifndef CASH_MANAGER_CLIENT_REQUESTFACTORY_HPP
#define CASH_MANAGER_CLIENT_REQUESTFACTORY_HPP

#include <functional>
#include <Network/Request/Authenticate.hpp>
#include <Network/Request/CardPayment.hpp>
#include <Network/Request/CardPaymentContactless.hpp>
#include <Network/Request/BankCheck.hpp>
#include <Network/Request/ArticleList.hpp>
#include <Network/Request/ArticleScan.hpp>


namespace cash
{
    namespace network
    {
        /**
         * @brief All request type available
         */
        enum RequestID: unsigned int {
            AUTHENTICATE_TERMINAL       = 0,
            CARD_PAYMENT                = 1,
            CARD_PAYMENT_CONTACTLESS    = 2,
            BANK_CHECK_PAYMENT          = 3,
            ARTICLE_LIST                = 4,
            ARTICLE_SCAN                = 5,
        };

        /**
         * @class RequestFactory
         * @brief RequestFactory used to build new request
         */
        class RequestFactory {
        private:
            static std::function<ARequest*()> _requests[];
            static const char                 *_signals[];

            RequestFactory() {}

        public:
            /**
             * @brief Request factory build
             * @param id Request type
             * @return New request object
             */
            static ARequest *build_request(RequestID id) {
                return RequestFactory::_requests[(unsigned int)id]();
            }
        };
    }
}


#endif //CASH_MANAGER_CLIENT_REQUESTFACTORY_HPP

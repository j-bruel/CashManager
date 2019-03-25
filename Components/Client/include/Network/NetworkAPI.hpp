//
// Created by grosso_a on 07/12/18.
//

#ifndef CASH_MANAGER_CLIENT_QNETWORKAPI_HPP
#define CASH_MANAGER_CLIENT_QNETWORKAPI_HPP

#include <Network/ARequest.hpp>
#include <QObject>
#include <QUrlQuery>
#include <QString>
#include <list>
#include "Tools/Log/Idx.hpp"
#include <plog/Log.h>

namespace cash
{
    namespace network
    {
        /**
         * @class NetworkAPI
         * @brief Network base class of APIs
         */
        class NetworkAPI: public QObject
            {
            Q_OBJECT

            private:
                std::string                                                 _url;
                unsigned int                                                _port;
                std::list<std::tuple<ARequest *, QNetworkAccessManager*>>   _requests;

            public:
                /**
                 * @brief NetworkAPI constructor
                 * @param url Server root url
                 * @param port Server root port
                 */
                NetworkAPI(std::string url, unsigned int port);


                /**
                 * @brief NetworkAPI destructor
                 */
                ~NetworkAPI();

                /**
                 * @brief NetworkAPI url
                 * @return the server url
                 */
                const std::string &url();

                /**
                 * @brief NetworkAPI port
                 * @return the server port
                 */
                unsigned int port();


                /**
                 * @brief NetworkAPI http GET
                 * @param req Request to call
                 */
                void get(ARequest* req);
            };
    }
}

#endif //CASH_MANAGER_CLIENT_QNETWORKAPI_HPP

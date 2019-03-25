//
// Created by grosso_a on 07/12/18.
//

#ifndef CASH_MANAGER_CLIENT_IREQUEST_HPP
#define CASH_MANAGER_CLIENT_IREQUEST_HPP

#include <QObject>
#include <string>
#include <map>
#include <memory>
#include <QJsonDocument>
#include <QNetworkReply>
#include <chrono>
#include <QCoreApplication>
#include <Network/RequestErrors.hpp>
#include "Tools/Log/Idx.hpp"
#include <plog/Log.h>

namespace cash
{
    namespace network
    {
        typedef std::map<std::string, std::string>  RequestParameters;

        enum RequestStatus {
            PENDING,
            GOOD,
            ERROR_REQUEST,
            ERROR_DATA
        };


        class ARequest: public QObject
        {
        Q_OBJECT
        protected:
            /**
             * Request response deserialize
             * @return True if deserialization is correct
             */
            virtual bool deserialize(std::shared_ptr<QJsonDocument>) = 0;

        public slots:

            /**
             * @brief Call back called by network on request result
             * @param reply Network reply
             */
            void onResult(QNetworkReply *reply);

        public:
            /**
             * @brief ARequest contructor
             * @param path Request url path
             */
            ARequest(const std::string &path);

            /**
             * @brief Request url path
             */
            const std::string &path();

            /**
             * @brief Request parameters
             */
            RequestParameters   &parameters();


            /**
             * @brief Request status
             */
            RequestStatus   status();

            /**
             * @brief Add parameter to request url
             * @param key Parameter name
             * @param value Parameter value
             */
            void    set_parameter(const std::string &key, const std::string &value);

            /**
             * @brief Update request status
             * @param status New request status
             */
            void set_status(RequestStatus status);


            /**
             * @brief Update request error msg
             * @param status New request error msg
             */
            void set_error(const std::string &errmsg, unsigned int errcode);

            /**
             * @brief Error msg
             * @return empty if no error
             */
            const std::string &error_msg();

            /**
             * @brief Error status code
             */
            RequestAPIErrors error_code();

            /**
             * @brief Wait request response
             */
            void   wait();

            /**
             * @brief Wait request response with timeout
             * @param mili Timeout on miliseconds
             */
            void   wait_until(unsigned int mili);

            /**
             * @brief Reset internal data of request to reuse it
             */
            void reset();

            /**
             * @brief Request destructor
             */
            virtual ~ARequest();

        private:
            unsigned int            _errcode;
            std::string             _error;
            std::string             _path;
            RequestParameters       _parameters;
            RequestStatus           _status = RequestStatus::PENDING;
        };
    }
}
#endif //CASH_MANAGER_CLIENT_IREQUEST_HPP

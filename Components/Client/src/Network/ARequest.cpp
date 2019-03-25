//
// Created by grosso_a on 02/01/19.
//
#include <Network/ARequest.hpp>

namespace cash
{
    namespace network
    {
        void ARequest::onResult(QNetworkReply *reply)
        {
            if (this->status() != RequestStatus::PENDING)
                return;
            if (reply->error() != QNetworkReply::NoError) {
                this->set_error("Request error code "+std::to_string(reply->error()), 2);
                LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::error) << "Network error " << std::to_string(reply->error());
                this->_status = RequestStatus::ERROR_REQUEST;
                return;
            }
            QJsonParseError jerror;
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll(), &jerror);
            if (!doc.isNull()) {
                if (deserialize(std::make_shared<QJsonDocument>(doc)))
                    this->_status = RequestStatus::GOOD;
                else
                    this->_status = RequestStatus::ERROR_DATA;
            } else {
                this->set_error("JSON format error", 1);
                LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::error) << "JSON format error GET:" << this->path() << " " << this;
                this->_status = RequestStatus::ERROR_DATA;
            }
        }

        ARequest::ARequest(const std::string &path) {
            this->_path = path;
            this->_status = PENDING;
            this->_errcode = 0;
        }

        const std::string &ARequest::path() {
            return this->_path;
        }

        RequestParameters   &ARequest::parameters()
        {
            return this->_parameters;
        }

        RequestStatus   ARequest::status()
        {
            return this->_status;
        }

        void    ARequest::set_parameter(const std::string &key, const std::string &value) {
            this->_parameters[key] = value;
        }

        void ARequest::set_status(RequestStatus status) {
            this->_status = status;
        }

        void ARequest::set_error(const std::string &errmsg, unsigned int errcode) {
            this->_error = errmsg;
            this->_errcode = errcode;
        }

        const std::string &ARequest::error_msg() {
            return _error;
        }

        RequestAPIErrors ARequest::error_code() {
            return static_cast<RequestAPIErrors>(_errcode);
        }

        void   ARequest::wait() {
            while (this->status() == RequestStatus::PENDING)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
        }

        void   ARequest::wait_until(unsigned int mili) {
            auto  next = std::chrono::system_clock::now() + std::chrono::milliseconds(mili);

            while (this->status() == RequestStatus::PENDING && std::chrono::system_clock::now() < next)
                QCoreApplication::processEvents(QEventLoop::AllEvents, mili);
        }

        void ARequest::reset() {
            this->_status = RequestStatus::PENDING;
            this->_error = "";
            this->_errcode = 0;
        }

        ARequest::~ARequest() {
            disconnect(this, SLOT(onResult(QNetworkReply *)));
        }
    }
}

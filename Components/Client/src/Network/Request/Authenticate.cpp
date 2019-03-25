//
// Created by grosso_a on 02/01/19.
//
#include <Network/Request/Authenticate.hpp>

namespace cash
{
    namespace network
    {
        std::time_t Authenticate::parseTime(const std::string& dateTime) {
            static const std::string dateTimeFormat{"%Y-%m-%dT%H:%M:%SZ" };
            std::istringstream ss{ dateTime };
            std::tm dt;

            ss >> std::get_time(&dt, dateTimeFormat.c_str());
            return std::mktime(&dt);
        }

        bool Authenticate::deserialize(std::shared_ptr<QJsonDocument> json) {
            QJsonObject obj = json->object();
            if (!obj.value(QString("error")).isUndefined()) {
                this->set_error(obj.value(QString("error")).toString().toStdString(),
                                obj.value(QString("error_code")).toInt(0));
                return false;
            }
            _token = obj.value(QString("token")).toString().toStdString();
            _type = obj.value(QString("type")).toString().toStdString();
            _created = parseTime(obj.value(QString("created")).toString().toStdString());
            _expire = parseTime(obj.value(QString("expire")).toString().toStdString());
            return true;
        }

        Authenticate::Authenticate(): cash::network::ARequest("/token")
        {
        }

        const std::string &Authenticate::token() {
            return _token;
        }

        std::time_t Authenticate::created() {
            return _created;
        }

        std::time_t Authenticate::expire() {
            return _expire;
        }

        const std::string &Authenticate::type() {
            return  _type;
        }

        Authenticate::~Authenticate() {};
    }
}

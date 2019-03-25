//
// Created by grosso_a on 02/01/19.
//
#include <Network/Request/CardPayment.hpp>

namespace cash
{
    namespace network
    {
        bool CardPayment::deserialize(std::shared_ptr<QJsonDocument> json) {
            QJsonObject obj = json->object();
            if (!obj.value(QString("error")).isUndefined()) {
                this->set_error(obj.value(QString("error")).toString().toStdString(),
                                obj.value(QString("error_code")).toInt(0));
                return false;
            }
            _token = obj.value(QString("token")).toString().toStdString();
            _type = obj.value(QString("type")).toString().toStdString();
            _card_type = obj.value(QString("card_type")).toString().toStdString();
            _card_number = obj.value(QString("card_number")).toString().toStdString();
            _transaction = obj.value(QString("transaction")).toString().toStdString();
            _amount = obj.value(QString("amount")).toInt();
            return true;
        }

        CardPayment::CardPayment(): cash::network::ARequest("/payment/card") {}

        const std::string &CardPayment::token() {
            return  _token;
        }

        const std::string &CardPayment::type() {
            return  _type;
        }

        const std::string &CardPayment::card_type() {
            return  _card_type;
        }

        const std::string &CardPayment::card_number() {
            return  _card_number;
        }

        const std::string &CardPayment::transaction_id() {
            return  _transaction;
        }

        int CardPayment::amount() {
            return  _amount;
        }

        CardPayment::~CardPayment() {};
    }
}

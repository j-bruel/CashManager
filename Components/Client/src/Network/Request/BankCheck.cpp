//
// Created by grosso_a on 02/01/19.
//
//
// Created by grosso_a on 16/12/18.
//
#include <Network/Request/BankCheck.hpp>

namespace cash
{
    namespace network
    {
        bool BankCheck::deserialize(std::shared_ptr<QJsonDocument> json) {
            QJsonObject obj = json->object();
            if (!obj.value(QString("error")).isUndefined()) {
                this->set_error(obj.value(QString("error")).toString().toStdString(),
                                obj.value(QString("error_code")).toInt(0));
                return false;
            }
            _token = obj.value(QString("token")).toString().toStdString();
            _type = obj.value(QString("type")).toString().toStdString();
            _check_number = obj.value(QString("check_number")).toString().toStdString();
            _transaction = obj.value(QString("transaction")).toString().toStdString();
            _amount = obj.value(QString("amount")).toInt();
            return true;
        }

        BankCheck::BankCheck(): cash::network::ARequest("/payment/check") {}

        const std::string &BankCheck::token() {
            return _token;
        }

        const std::string &BankCheck::type() {
            return  _type;
        }

        const std::string &BankCheck::number() {
            return  _check_number;
        }

        const std::string &BankCheck::transaction_id() {
            return _transaction;
        }

        int BankCheck::amount() {
            return _amount;
        }

        BankCheck::~BankCheck() {};
    }
}


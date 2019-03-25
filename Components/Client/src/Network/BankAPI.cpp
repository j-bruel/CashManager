//
// Created by grosso_a on 16/12/18.
//
#include <Network/BankAPI.hpp>
#include <iostream>
#include <unistd.h>
#include <Network/Request/RequestFactory.hpp>
#include <thread>
#include <chrono>
#include <algorithm>
#include <string>
#include <iostream>
#include "Tools/Log/Idx.hpp"
#include <plog/Log.h>

namespace cash
{
    namespace network
    {
        std::string BankAPI::clean_spaces(std::string str)
        {
            str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
            return str;
        }

        cash::network::Authenticate *BankAPI::authenticate(
                const std::string &payment_type,
                int try_count,
                unsigned int timeout)
        {
            LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "AUTHENTICATE";
            RequestFactory::build_request(RequestID::AUTHENTICATE_TERMINAL);
            cash::network::ARequest *req = RequestFactory::build_request(RequestID::AUTHENTICATE_TERMINAL);
            RequestFactory::build_request(RequestID::AUTHENTICATE_TERMINAL);
            RequestFactory::build_request(RequestID::AUTHENTICATE_TERMINAL);
            req->set_parameter("type", payment_type);
            req->set_parameter("try_count", std::to_string(try_count));
            this->get(req);
            if (timeout > 0)
                req->wait_until(timeout);
            else
                req->wait();
            return dynamic_cast<cash::network::Authenticate*>(req);
        }

        cash::network::CardPayment *BankAPI::card_payment(
                const std::string &token,
                const std::string &card_type,
                const std::string &card_number,
                const std::string &pin,
                float amount,
                unsigned int timeout)
        {
            LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "CARD_PAYMENT";
            cash::network::ARequest *req = RequestFactory::build_request(RequestID::CARD_PAYMENT);
            std::string             amount_param = std::to_string(amount);

            std::replace(amount_param.begin(), amount_param.end(), ',', '.');
            req->set_parameter("card_number", clean_spaces(card_number));
            req->set_parameter("card_type", card_type);
            req->set_parameter("pin", pin);
            req->set_parameter("token", token);
            req->set_parameter("amount", amount_param);
            this->get(req);
            if (timeout > 0)
                req->wait_until(timeout);
            else
                req->wait();
            return dynamic_cast<cash::network::CardPayment*>(req);
        }

        cash::network::CardPaymentContactless *BankAPI::card_payment_contactless(
                const std::string &token,
                const std::string &card_type,
                const std::string &card_number,
                float amount,
                unsigned int timeout)
        {
            LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "CARD_PAYMENT_CONTACTLESS";
            cash::network::ARequest *req = RequestFactory::build_request(RequestID::CARD_PAYMENT_CONTACTLESS);
            std::string             amount_param = std::to_string(amount);

            std::replace(amount_param.begin(), amount_param.end(), ',', '.');
            req->set_parameter("card_number", clean_spaces(card_number));
            req->set_parameter("card_type", card_type);
            req->set_parameter("token", token);
            req->set_parameter("amount", amount_param);
            this->get(req);
            if (timeout > 0)
                req->wait_until(timeout);
            else
                req->wait();
            return dynamic_cast<cash::network::CardPaymentContactless*>(req);
        }

        cash::network::BankCheck *BankAPI::check_payment(
                const std::string &token,
                const std::string &check_number,
                float amount,
                unsigned int timeout)
        {
            LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "CHECK_PAYMENT";
            cash::network::ARequest *req = RequestFactory::build_request(RequestID::BANK_CHECK_PAYMENT);
            std::string             amount_param = std::to_string(amount);

            std::replace(amount_param.begin(), amount_param.end(), ',', '.');
            req->set_parameter("check_number", clean_spaces(check_number));
            req->set_parameter("token", token);
            req->set_parameter("amount", amount_param);
            this->get(req);
            if (timeout > 0)
                req->wait_until(timeout);
            else
                req->wait();
            return dynamic_cast<cash::network::BankCheck*>(req);
        }
    }
}

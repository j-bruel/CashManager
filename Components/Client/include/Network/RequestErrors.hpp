//
// Created by grosso_a on 30/12/18.
//

#ifndef CASH_MANAGER_CLIENT_REQUESTERRORS_HPP
#define CASH_MANAGER_CLIENT_REQUESTERRORS_HPP

namespace cash
{
    namespace network
    {
        enum RequestAPIErrors : unsigned int
        {
            UNKNOW_ERROR = 0,
            INVALID_JSON = 1,
            NETWORK = 2,

            BANK_CARD_BANNED = 101,
            BANK_CHECK_BANNED = 102,
            BANK_INVALID_PIN = 103,
            BANK_INVALID_CARD_NUMBER = 104,
            BANK_INVALID_CHECK_NUMBER = 105,
            BANK_INVALID_AMOUNT = 106,
            BANK_INVALID_TOKEN = 107,
            BANK_MAX_TRY = 108,
        };
    }
}

#endif //CASH_MANAGER_CLIENT_REQUESTERRORS_HPP

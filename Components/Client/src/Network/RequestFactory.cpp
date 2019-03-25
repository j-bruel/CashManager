//
// Created by grosso_a on 26/12/18.
//
//
// Created by grosso_a on 19/12/18.
//
#include <Network/Request/RequestFactory.hpp>

namespace cash
{
    namespace network
    {
        std::function<cash::network::ARequest*()> cash::network::RequestFactory::_requests[] = {
                []{ return new cash::network::Authenticate();},
                []{ return new cash::network::CardPayment();},
                []{ return new cash::network::CardPaymentContactless();},
                []{ return new cash::network::BankCheck();},
                []{ return new cash::network::ArticleList();},
                []{ return new cash::network::ArticleScan();},
        };

        const char  *cash::network::RequestFactory::_signals[] = {
                SIGNAL(authenticate_terminal_resp(cash::network::AuhtenticateTerminal *))
        };
    }
}


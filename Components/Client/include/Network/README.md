# BankAPI
## Start server
### Install
https://docs.docker.com/compose/install/

### Build
`cd T-ARC-CashManager_2018/Components/Server`
`docker-compose build`

### Run
`cd T-ARC-CashManager_2018/Components/Server`
`docker-compose up`

```
#include <Network/BankAPI.hpp>

cash::network::BankAPI           api("http://0.0.0.0", 5000);
cash::network::Authenticate      *reply;

reply = api.authenticate("LOL", 4);
//Check the request result
reply->status() == cash::network::RequestStatus::GOOD
reply->error() // error message

//Payment types allowed are: CARD, CONTACTLESS, CHECK
api.authenticate("CARD", 4);

/*
** cash::network::CardPayment       *card_payment(const std::string &card_type, const std::string &card_number, const std::string &pin, unsigned int amount);
** card_type: VISA, MASTER, ELECTRON
** card_number: numeric with len > 0 and not banned
** pin: numeric with 4 char
** amount: numeric with limit by card type
    VISA : 500
    MASTER : 1000
    ELECTRON : 300
*/


/*
** cash::network::CardPaymentContactless *card_payment_contactless(const std::string &card_type, const std::string &card_number, unsigned int amount);
** card_type: VISA, MASTER, ELECTRON
** card_number: numeric with len > 0 and not banned
** amount: numeric with limit by card type
    VISA : 30
    MASTER : 30
    ELECTRON : 30
*/


/*
** cash::network::BankCheck *BankAPI::check_payment(const std::string &check_number, unsigned int amount);
** card_check: numeric with len > 0 and not banned
** amount: numeric without limit
*/
```

### Ban card or check
http://0.0.0.0:5000/admin/banned/new/?url=%2Fadmin%2Fbanned%2F

###
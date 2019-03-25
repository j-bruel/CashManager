//
// Created by grosso_a on 16/12/18.
//

#include <gtest/gtest.h>
#include <QApplication>
#include <Network/BankAPI.hpp>
#include <QTimer>
#include <thread>
#include <chrono>
#include <Network/NetworkInfo.hpp>

//!
//! @test Check payment with banned card.
//!
TEST (CardPayment, CARD_BANNED)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", -1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    api.card_payment(reply_auth->token(),"VISA", "0000 0000 0000 0000", "0000", 50.0);
    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"VISA", "0000 0000 0000 0000", "0000", 50.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Card banned");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_CARD_BANNED);
}


//!
//! @test Check payment with invalid card type.
//!
TEST (CardPayment, CARD_TYPE_INVALID)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"VISO", "0000 0000 0000 0000", "1000", 50.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_REQUEST);
}


//!
//! @test Test wrong pin code size.
//!
TEST (CardPayment, CARD_INVALID_PIN_SIZE)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"VISA", "0000 0000 0000 0100", "000", 50.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Invalid pin");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_INVALID_PIN);
}


//!
//! @test Try payment with pin contain letters.
//!
TEST (CardPayment, CARD_INVALID_PIN_ALPHA)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"VISA", "0000 0000 0000 0100", "000A", 50.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Invalid pin");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_INVALID_PIN);
}


//!
//! @test Check Visa card payment limit.
//!
TEST (CardPayment, VISA_INVALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"VISA", "0000 0000 0000 0100", "0100", 2501.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Card max amount 2500.0");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_INVALID_AMOUNT);
}


//!
//! @test Check valid Visa card payment.
//!
TEST (CardPayment, VISA_VALID)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"VISA", "0000 0000 0000 0100", "0100", 500.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::GOOD);
    ASSERT_STREQ(reply_pay->token().c_str(), reply_auth->token().c_str());
    ASSERT_STREQ(reply_pay->card_type().c_str(), "VISA");
    ASSERT_STREQ(reply_pay->card_number().c_str(), "0000000000000100");
    ASSERT_EQ(reply_pay->amount(), 500);
}


//!
//! @test Check Master card payment limit.
//!
TEST (CardPayment, MASTER_INVALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"MASTER", "0000 0000 0000 0100", "0100", 3001.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Card max amount 3000.0");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_INVALID_AMOUNT);
}

//!
//! @test Check valid Master card payment limit.
//!
TEST (CardPayment, MASTER_VALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"MASTER", "0000 0000 0000 0100", "0100", 3000.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::GOOD);
    ASSERT_STREQ(reply_pay->token().c_str(), reply_auth->token().c_str());
    ASSERT_STREQ(reply_pay->card_type().c_str(), "MASTER");
    ASSERT_STREQ(reply_pay->card_number().c_str(), "0000000000000100");
    ASSERT_EQ(reply_pay->amount(), 3000);
}


//!
//! @test Check Electron card payment limit.
//!
TEST (CardPayment, ELECTRON_INVALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"ELECTRON", "0000 0000 0000 0100", "0100", 1701.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Card max amount 1700.0");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_INVALID_AMOUNT);
}

//!
//! @test Check valid Electron payment.
//!
TEST (CardPayment, ELECTRON_VALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CARD", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPayment      *reply_pay = api.card_payment(reply_auth->token(),"ELECTRON", "0000 0000 0000 0100", "1000", 1700.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::GOOD);
    ASSERT_STREQ(reply_pay->token().c_str(), reply_auth->token().c_str());
    ASSERT_STREQ(reply_pay->card_type().c_str(), "ELECTRON");
    ASSERT_STREQ(reply_pay->card_number().c_str(), "0000000000000100");
    ASSERT_EQ(reply_pay->amount(), 1700);
}
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
//! @test Test max try token error.
//!
TEST (CardPaymentContectLess, MAX_TRY)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CONTACTLESS", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    api.card_payment_contactless(reply_auth->token(),"VISA", "0000 0000 0000 0000", 30.0);
    cash::network::CardPaymentContactless     *reply_pay = api.card_payment_contactless(reply_auth->token(),"VISA", "0000 0000 0000 0000", 30.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_MAX_TRY);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Max try");
}

//!
//! @test Test payment with banned card.
//!
TEST (CardPaymentContectLess, CARD_BANNED)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CONTACTLESS", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPaymentContactless     *reply_pay = api.card_payment_contactless(reply_auth->token(),"VISA", "0000 0000 0000 0000", 30.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_CARD_BANNED);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Card banned");
}


//!
//! @test Test payment with wrong card type.
//!
TEST (CardPaymentContectLess, CARD_TYPE_INVALID)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CONTACTLESS", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPaymentContactless     *reply_pay = api.card_payment_contactless(reply_auth->token(),"VISO", "0000 0000 0000 0000", 30.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_REQUEST);
}


//!
//! @test Check Visa contactless payment limit.
//!
TEST (CardPaymentContectLess, VISA_INVALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CONTACTLESS", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPaymentContactless     *reply_pay = api.card_payment_contactless(reply_auth->token(),"VISA", "0000 0000 0000 0100", 31.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Contactless max amount 30.0");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_INVALID_AMOUNT);
}


//!
//! @test Check valid Visa contactless payment.
//!
TEST (CardPaymentContectLess, VISA_VALID)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CONTACTLESS", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPaymentContactless     *reply_pay = api.card_payment_contactless(reply_auth->token(),"VISA", "0000 0000 0000 0100", 30.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::GOOD);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "");
    ASSERT_STREQ(reply_pay->token().c_str(), reply_auth->token().c_str());
    ASSERT_STREQ(reply_pay->card_type().c_str(), "VISA");
    ASSERT_STREQ(reply_pay->card_number().c_str(), "0000000000000100");
    ASSERT_EQ(reply_pay->amount(), 30.0);
}


//!
//! @test Check Master contactless payment limit.
//!
TEST (CardPaymentContectLess, MASTER_INVALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CONTACTLESS", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPaymentContactless     *reply_pay = api.card_payment_contactless(reply_auth->token(),"MASTER", "0000 0000 0000 0100", 31.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Contactless max amount 30.0");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_INVALID_AMOUNT);
}

//!
//! @test Check valid Master contactless payment.
//!
TEST (CardPaymentContectLess, MASTER_VALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CONTACTLESS", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPaymentContactless     *reply_pay = api.card_payment_contactless(reply_auth->token(),"MASTER", "0000 0000 0000 0100", 30.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::GOOD);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "");
    ASSERT_STREQ(reply_pay->token().c_str(), reply_auth->token().c_str());
    ASSERT_STREQ(reply_pay->card_type().c_str(), "MASTER");
    ASSERT_STREQ(reply_pay->card_number().c_str(), "0000000000000100");
    ASSERT_EQ(reply_pay->amount(), 30);
}


//!
//! @test Check Electron contactless payment limit.
//!
TEST (CardPaymentContectLess, ELECTRON_INVALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CONTACTLESS", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPaymentContactless      *reply_pay = api.card_payment_contactless(reply_auth->token(),"ELECTRON", "0000 0000 0000 0100", 31.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Contactless max amount 30.0");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_INVALID_AMOUNT);
}


//!
//! @test Check valid Electron contactless payment.
//!
TEST (CardPaymentContectLess, ELECTRON_VALID_AMOUNT)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CONTACTLESS", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::CardPaymentContactless      *reply_pay = api.card_payment_contactless(reply_auth->token(),"ELECTRON", "0000 0000 0000 0100", 30.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::GOOD);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "");
    ASSERT_STREQ(reply_pay->token().c_str(), reply_auth->token().c_str());
    ASSERT_STREQ(reply_pay->card_type().c_str(), "ELECTRON");
    ASSERT_STREQ(reply_pay->card_number().c_str(), "0000000000000100");
    ASSERT_EQ(reply_pay->amount(), 30);
}
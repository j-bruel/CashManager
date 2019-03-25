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
//! @test Try payment with banned check.
//!
TEST (BankCheckPayment, CHECK_BANNED)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CHECK", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::BankCheck     *reply_pay = api.check_payment(reply_auth->token(), "0000 0000 AAA", 30.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::ERROR_DATA);
    ASSERT_STREQ(reply_pay->error_msg().c_str(), "Check banned");
    ASSERT_EQ(reply_pay->error_code(), cash::network::RequestAPIErrors::BANK_CHECK_BANNED);
}


//!
//! @test Try payment with valid check.
//!
TEST (BankCheckPayment, CHECK_VALID)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CHECK", 1);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    cash::network::BankCheck     *reply_pay = api.check_payment(reply_auth->token(), "0000 0000 AAB", 30.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::GOOD);
    ASSERT_STREQ(reply_pay->token().c_str(), reply_auth->token().c_str());
    ASSERT_STREQ(reply_pay->number().c_str(), "00000000AAB");
    ASSERT_EQ(reply_pay->amount(), 30);
}


//!
//! @test Try two payment with second valid.
//!
TEST (BankCheckPayment, CHECK_VALID_SECOND_TRY)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply_auth = api.authenticate("CHECK", 2);

    ASSERT_EQ(reply_auth->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply_auth->token().size(), (unsigned int)32);

    api.check_payment(reply_auth->token(), "0000 0000 AAA", 30.0);
    cash::network::BankCheck     *reply_pay = api.check_payment(reply_auth->token(), "0000 0000 AAB", 30.0);
    ASSERT_EQ(reply_pay->status(), cash::network::RequestStatus::GOOD);
    ASSERT_STREQ(reply_pay->token().c_str(), reply_auth->token().c_str());
    ASSERT_STREQ(reply_pay->number().c_str(), "00000000AAB");
    ASSERT_EQ(reply_pay->amount(), 30);
}

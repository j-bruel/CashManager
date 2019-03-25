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
//! @test Check wrong payment type error.
//!
TEST (AuthneticateTerminal, WrongType)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply = api.authenticate("TOTO", 4, 500);
    ASSERT_EQ(reply->status(), cash::network::RequestStatus::ERROR_REQUEST);
    ASSERT_STRCASEEQ(reply->error_msg().c_str(), "Request error code 302");
    ASSERT_EQ(reply->error_code(), cash::network::RequestAPIErrors::NETWORK);
}

//!
//! @test Generate token for card payment
//!
TEST (AuthneticateTerminal, CARD)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply = api.authenticate("CARD", 1, 500);
    ASSERT_EQ(reply->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply->error_code(), cash::network::RequestAPIErrors::UNKNOW_ERROR);
    ASSERT_EQ(reply->token().size(), (unsigned int)32);
}

//!
//! @test Generate token for contactless payment
//!
TEST (AuthneticateTerminal, CONTACTLESS)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply = api.authenticate("CONTACTLESS", 1, 500);
    ASSERT_EQ(reply->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply->error_code(), cash::network::RequestAPIErrors::UNKNOW_ERROR);
    ASSERT_EQ(reply->token().size(), (unsigned int)32);
}

//!
//! @test Generate token for check payment
//!
TEST (AuthneticateTerminal, CHECK)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::BankAPI          api(BANK_URL, BANK_PORT);
    cash::network::Authenticate     *reply = api.authenticate("CHECK", 1);
    ASSERT_EQ(reply->status(), cash::network::RequestStatus::GOOD);
    ASSERT_EQ(reply->error_code(), cash::network::RequestAPIErrors::UNKNOW_ERROR);
    ASSERT_EQ(reply->token().size(), (unsigned int)32);
}
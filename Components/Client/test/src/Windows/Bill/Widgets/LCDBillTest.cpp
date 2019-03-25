//!
//! @file LCDBillTest.cpp
//! @author jbruel
//! @date 06/12/18
//!

#include "Windows/Bill/Widgets/LCDBill.hpp"
#include <QtWidgets/QApplication>
#include <gtest/gtest.h>

//!
//! @test Simple bill initialize.
//!
TEST (LCDBill, setBill)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(20.1);
    ASSERT_DOUBLE_EQ(bill.getBill(), 20.1);
}

//!
//! @test bill initialize with 0.
//!
TEST (LCDBill, setBillWithZero)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(0);
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
}

//!
//! @test bill initialize with a big number.
//!
TEST (LCDBill, setBillWithBigNumber)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(567890);
    ASSERT_DOUBLE_EQ(bill.getBill(), 567890);
}

//!
//! @test bill initialize with a negatif number.
//!
TEST (LCDBill, setBillWithNegatif)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(-2);
    ASSERT_DOUBLE_EQ(bill.getBill(), -2);
}

//!
//! @test Set bill multi time on same instance.
//!
TEST (LCDBill, setBillMultiTime)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(20.1);
    ASSERT_DOUBLE_EQ(bill.getBill(), 20.1);
    bill.setBill(0);
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
    bill.setBill(567890);
    ASSERT_DOUBLE_EQ(bill.getBill(), 567890);
    bill.setBill(-2);
    ASSERT_DOUBLE_EQ(bill.getBill(), -2);
    bill.setBill(457689009868);
    ASSERT_DOUBLE_EQ(bill.getBill(), 457689009868);
}

//!
//! @test Set bill multi time (same value) on same instance.
//!
TEST (LCDBill, setBillMultiTimeWithSameValue)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(20.1);
    ASSERT_DOUBLE_EQ(bill.getBill(), 20.1);
    bill.setBill(20.1);
    bill.setBill(20.1);
    bill.setBill(20.1);
    bill.setBill(20.1);
    bill.setBill(20.1);
    bill.setBill(20.1);
    bill.setBill(20.1);
    ASSERT_DOUBLE_EQ(bill.getBill(), 20.1);
}

//!
//! @test Simple unset bill initialize.
//!
TEST (LCDBill, unsetBill)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(20.1);
    bill.unsetBill();
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
    bill.setBill(0);
    bill.unsetBill();
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
    bill.setBill(567890);
    bill.unsetBill();
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
    bill.setBill(-2);
    bill.unsetBill();
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
    bill.setBill(457689009868);
    bill.unsetBill();
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
}

//!
//! @test Multi unset on same instance.
//!
TEST (LCDBill, multiUnsetBill)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(20.1);
    bill.unsetBill();
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
    bill.unsetBill();
    bill.unsetBill();
    bill.unsetBill();
    bill.unsetBill();
    bill.unsetBill();
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
}

//!
//! @test Unset without set.
//!
TEST (LCDBill, unsetWithoutSet)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.unsetBill();
    bill.unsetBill();
    bill.unsetBill();
    bill.unsetBill();
    bill.unsetBill();
    ASSERT_DOUBLE_EQ(bill.getBill(), 0);
}

//!
//! @test Add a price to the bill.
//!
TEST (LCDBill, addPriceToBill)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(20.1);
    ASSERT_DOUBLE_EQ(bill.getBill(), 20.1);
    bill.addPriceToBill(10.2);
    ASSERT_DOUBLE_EQ(bill.getBill(), 30.3);
    bill.addPriceToBill(0.1);
    ASSERT_DOUBLE_EQ(bill.getBill(), 30.4);
    bill.addPriceToBill(0);
    ASSERT_DOUBLE_EQ(bill.getBill(), 30.4);
    bill.addPriceToBill(100);
    ASSERT_DOUBLE_EQ(bill.getBill(), 130.4);
}

//!
//! @test Add a price negative to the bill.
//!
TEST (LCDBill, addNativePriceToBill)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(20.1);
    ASSERT_DOUBLE_EQ(bill.getBill(), 20.1);
    bill.addPriceToBill(-10);
    ASSERT_DOUBLE_EQ(bill.getBill(), 10.1);
}

//!
//! @test Remove a price to the bill.
//!
TEST (LCDBill, removePriceToBill)
{
    char                                *argv[] = { const_cast<char *>("./cash-manager-client-ut"), nullptr };
    int                                 argc = 1;
    QApplication                        app(argc, argv);
    cash::win::bill::widget::LCDBill    bill(nullptr);

    bill.setBill(153.8);
    ASSERT_DOUBLE_EQ(bill.getBill(), 153.8);
    bill.removePriceToBill(10.2);
    ASSERT_DOUBLE_EQ(bill.getBill(), 143.6);
    bill.removePriceToBill(0.1);
    ASSERT_DOUBLE_EQ(bill.getBill(), 143.5);
    bill.removePriceToBill(0);
    ASSERT_DOUBLE_EQ(bill.getBill(), 143.5);
    bill.removePriceToBill(100);
    ASSERT_DOUBLE_EQ(bill.getBill(), 43.5);
}
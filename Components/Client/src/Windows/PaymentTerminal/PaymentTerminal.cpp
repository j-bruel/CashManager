//!
//! @file PaymentTerminal.cpp
//! @author jbruel
//! @date 07/12/18
//!

#include "Windows/PaymentTerminal/PaymentTerminal.hpp"
#include "Tools/Log/Idx.hpp"
#include <plog/Severity.h>
#include <plog/Log.h>
#include <exception.hpp>

namespace cash
{
namespace win
{

    PaymentTerminal::PaymentTerminal(QWidget *parent) : QWidget(parent), mPaymentTerminalWindow(), mTerminal(&mPaymentTerminalWindow)
    {
        initScreen();
    }

    void    PaymentTerminal::initScreen()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "MPT: Initialize windows.";
        mPaymentTerminalWindow.setFixedSize(390, 535);
        mPaymentTerminalWindow.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        mPaymentTerminalWindow.setWindowTitle(QApplication::translate("mPaymentTerminalWindow", "Payment Terminal", Q_NULLPTR));
    }

    bool    PaymentTerminal::update(std::shared_ptr<core::PaymentOrder> &subject)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: Cashier ask for payment process, bill : " << subject->mBill << "€.";
        return (mTerminal.payment(subject->mBill));
    }

}
}
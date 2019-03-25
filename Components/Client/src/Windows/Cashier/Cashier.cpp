//!
//! @file Cashier.cpp
//! @author jbruel
//! @date 07/12/18
//!

#include "Windows/Cashier/Cashier.hpp"
#include "Tools/Log/Idx.hpp"
#include <plog/Severity.h>
#include <plog/Log.h>
#include <exception.hpp>

namespace cash
{
namespace win
{

    Cashier::Cashier(QWidget *parent) : QWidget(parent), mCashierWindow(), mEscape(&mCashierWindow), mCashierScreen(&mCashierWindow)
    {
        initScreen();
        initEscapeHandling();
    }

    void    Cashier::attachSubjets(win::Bill *bill, win::PaymentTerminal *mpt)
    {
        mCashierScreen.tool::Subject<double>::attach(bill);
        mCashierScreen.tool::Subject<core::PaymentOrder>::attach(mpt);
    }

    void    Cashier::quitApplication()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::warning) << "Cashier: Closing the application.";
        QApplication::quit();
    }

    void    Cashier::initScreen()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Initialize windows.";
        mCashierWindow.setFixedSize(350, 670);
        mCashierWindow.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        mCashierWindow.setWindowTitle(QApplication::translate("mCashierWindow", "Cashier", Q_NULLPTR));
    }

    void    Cashier::initEscapeHandling()
    {
        mEscape.setKey(Qt::Key_Escape);
        connect(&mEscape, SIGNAL(activated()), this, SLOT(quitApplication()));
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Escape system initialize.";
    }


}
}
//!
//! @file CashManager.cpp
//! @author jbruel
//! @date 06/12/18
//!

#include "Core/CashManager.hpp"
#include "Tools/Log/Idx.hpp"
#include <plog/Log.h>

namespace cash
{
namespace core
{

    void    CashManager::init()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "CashManager client finish is initialization.";
        mCashier.attachSubjets(&mBill, &mPaymentTerminal);
        mPaymentTerminal.attachCreditCardDialog(&mCashier.getCashierScreenInstance().getCreditCardDialog());
    }

    void    CashManager::run()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "CashManager application as been launch.";
        mBill.show();
        mCashier.show();
        mPaymentTerminal.show();
    }

}
}
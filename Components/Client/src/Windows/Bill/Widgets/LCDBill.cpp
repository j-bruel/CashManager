//!
//! @file LCDBill.cpp
//! @author jbruel
//! @date 05/12/18
//!

#include "Windows/Bill/Widgets/LCDBill.hpp"
#include "Windows/Bill/BillConfiguration.hpp"
#include "Windows/Bill/CurrencyConfiguration.hpp"
#include <QtWidgets/QApplication>
#include "Tools/Log/Idx.hpp"
#include <sstream>
#include <plog/Log.h>

namespace cash
{
namespace win
{
namespace bill
{
namespace widget
{

    LCDBill::LCDBill(QWidget *parent) : QWidget(parent), mBill(3, parent), mCurrency(getBillCurrencySymbol(), parent), mCurrentBillValue(0)
    {
        setFocusPolicy(Qt::StrongFocus);
        initBillLayout();
        initCurrencyLayout();
    }

    void    LCDBill::initBillLayout()
    {
        mBill.setSegmentStyle(QLCDNumber::Filled);
        mBill.setMode(QLCDNumber::Mode::Dec);
        mBill.resize(BillWidthWindow, BillHeightWindow);
        mBill.setDigitCount(BillMaxDigits);
        mBill.setStyleSheet(BillBackgroundColor + BillColor);
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Bill: Number display is ready.";
    }

    void    LCDBill::initCurrencyLayout()
    {
        mCurrency.move(BillWidthWindow, 0);
        mCurrency.resize(100, 120);

        QFont font = mCurrency.font();

        font.setPointSize(BillCurrencyFontSize);
        mCurrency.setFont(font);
        mCurrency.setStyleSheet(getCurrencyBackgroundColor() + getCurrencyColor());
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Bill: Currency is ready.";
    }

    void     LCDBill::setBill(double bill)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Bill: Update received, old bill : " << mCurrentBillValue << "€, new bill : " << bill << "€.";
        mCurrentBillValue = bill;
        updateBill();
    }

    void     LCDBill::unsetBill()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Bill: Update received, reinitialize to zero, old bill : " << mCurrentBillValue << "€.";
        mCurrentBillValue = 0;
        updateBill();
    }

    void     LCDBill::addPriceToBill(double price)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Bill: The price : " << price << "€ will be added to the bill.";
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Bill: Update received, old bill : " << mCurrentBillValue << "€, new bill : " << mCurrentBillValue + price << "€.";
        mCurrentBillValue += price;
        updateBill();
    }

    void     LCDBill::removePriceToBill(double price)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Bill: The price : " << price << "€ will be remove to the bill.";
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Bill: Update received, old bill : " << mCurrentBillValue << "€, new bill : " << mCurrentBillValue - price << "€.";
        mCurrentBillValue -= price;
        updateBill();
    }

    QString LCDBill::priceToQString(double price) const
    {
        std::ostringstream  strs;

        strs << price;
        return (QString(strs.str().c_str()));
    }

}
}
}
}
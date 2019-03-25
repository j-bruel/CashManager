//!
//! @file Bill.cpp
//! @author jbruel
//! @date 05/12/18
//!

#include "Windows/Bill/Bill.hpp"
#include "Windows/Bill/BillConfiguration.hpp"
#include "Tools/Log/Idx.hpp"
#include <plog/Log.h>
#include <QtWidgets/QApplication>

namespace cash
{
namespace win
{

    Bill::Bill(QWidget *parent) : QWidget(parent), mBillWindow(), mBill(&mBillWindow)
    {
        initBillWindow();
        mBill.setBill(0);
    }

    bool    Bill::update(std::shared_ptr<double> &data)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::warning) << "Bill: A update has been received : " << (*data) << "€.";
        mBill.setBill((*data));
        return (true);
    }

    void    Bill::initBillWindow()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Bill: Initialize windows.";
        mBillWindow.setFixedSize(bill::WidthWindow, bill::HeightWindow);
        mBillWindow.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        mBillWindow.setWindowTitle(QApplication::translate("mBillWindow", "Bill", Q_NULLPTR));
    }

}
}
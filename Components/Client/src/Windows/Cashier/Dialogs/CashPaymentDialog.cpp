//!
//! @file CashPaymentDialog.cpp
//! @author jbruel
//! @date 21/12/18
//!

#include <sstream>
#include <plog/Severity.h>
#include <Tools/Log/Idx.hpp>
#include <plog/Log.h>
#include "Windows/Cashier/Dialogs/CashPaymentDialog.hpp"

namespace cash
{
namespace win
{
namespace cashier
{
namespace dialog
{

    CashPaymentDialog::CashPaymentDialog(QWidget *parent) : QDialog(parent), mBill(this), mUserCash(this), mUserRefound(this),
                                                            mMountNumber(this), mCashInPayment(this), mValidatePayment(this),
                                                            mBillValue(0), mBillString(), mPaymentValidate(false)
    {
        initWindow();
        initWidgets();
        QMetaObject::connectSlotsByName(this);
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Cashier: Initialize cash payment dialog.";
    }

    bool    CashPaymentDialog::execCashDialog()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Running cash payment.";
        mBillString.clear();
        mUserCash.display("0");
        mPaymentValidate = false;
        mBill.display(mBillValue);
        mUserRefound.display("0");
        mValidatePayment.setStandardButtons(QDialogButtonBox::Cancel);
        mCashInPayment.setEnabled(true);
        mCashInPayment.setText(QApplication::translate("Dialog", "Cash In", Q_NULLPTR));
        exec();
        return (mPaymentValidate);
    }

    void    CashPaymentDialog::enterPinOne()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '1' for cash payment.";
        mBillString += "1";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterPinTwo()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '2' for cash payment.";
        mBillString += "2";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterPinThree()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '3' for cash payment.";
        mBillString += "3";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterPinFour()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '4' for cash payment.";
        mBillString += "4";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterPinFive()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '5' for cash payment.";
        mBillString += "5";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterPinSix()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '6' for cash payment.";
        mBillString += "6";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterPinSeven()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '7' for cash payment.";
        mBillString += "7";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterPinHeight()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '8' for cash payment.";
        mBillString += "8";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterPinNine()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '9' for cash payment.";
        mBillString += "9";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterPinZero()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter '0' for cash payment.";
        mBillString += "0";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterComma()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter ',' for cash payment.";
        mBillString += ".";
        mUserCash.display(mBillString.c_str());
    }

    void    CashPaymentDialog::enterSupp()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: User enter 'SUPP' for cash payment.";
        mBillString = "0";
        mUserCash.display(mBillString.c_str());
        mBillString.clear();
    }

    void    CashPaymentDialog::validePayment()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Cash payment done.";
        mPaymentValidate = true;
        accept();
    }

    void    CashPaymentDialog::cashIn()
    {
        double  cashOut = 0;

        if (mBillString.empty() || mBillString == "0" || mBillValue <= 0)
            return ;
        std::stringstream(mBillString) >> cashOut;
        if (cashOut < mBillValue)
        {
            enterSupp();
            return ;
        }
        if (cashOut != mBillValue)
            cashOut = cashOut - mBillValue;
        else
            cashOut = 0;
        mUserRefound.display(cashOut);
        mCashInPayment.setText(QApplication::translate("Dialog", "Cash Out", Q_NULLPTR));
        mCashInPayment.setEnabled(false);
        mValidatePayment.setStandardButtons(QDialogButtonBox::Ok);
        repaint();
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: User bill : " << mBillValue;
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: User given cash : " << mBillString;
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: User cash back : " << cashOut;
    }

    void    CashPaymentDialog::initWindow()
    {
        if (objectName().isEmpty())
            setObjectName(QStringLiteral("Dialog"));
        setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        setFixedSize(280, 517);
        setWindowTitle(QApplication::translate("Dialog", "Cash payment", Q_NULLPTR));
        setWindowModality(Qt::WindowModal);
    }

    void    CashPaymentDialog::initWidgets()
    {
        mBill.setObjectName(QStringLiteral("mBill"));
        mBill.setGeometry(QRect(10, 10, 251, 31));
        mBill.setDigitCount(15);
        mUserCash.setObjectName(QStringLiteral("mUserCash"));
        mUserCash.setGeometry(QRect(10, 50, 251, 31));
        mUserCash.setStyleSheet(QStringLiteral("color: rgb(138, 226, 52)"));
        mUserCash.setSmallDecimalPoint(false);
        mUserCash.setDigitCount(15);
        mUserCash.setMode(QLCDNumber::Dec);
        mUserCash.setProperty("intValue", QVariant(0));
        mUserRefound.setObjectName(QStringLiteral("mUserRefound"));
        mUserRefound.setGeometry(QRect(10, 90, 251, 31));
        mUserRefound.setStyleSheet(QStringLiteral("color: rgb(239, 41, 41)"));
        mUserRefound.setDigitCount(15);
        mCashInPayment.setObjectName(QStringLiteral("mCashInPayment"));
        mCashInPayment.setGeometry(QRect(10, 430, 251, 25));
        mCashInPayment.setText(QApplication::translate("Dialog", "Cash In", Q_NULLPTR));
        mValidatePayment.setObjectName(QStringLiteral("mValidatePayment"));
        mValidatePayment.setGeometry(QRect(60, 470, 201, 41));
        mValidatePayment.setOrientation(Qt::Horizontal);
        mValidatePayment.setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
        QObject::connect(&mValidatePayment, SIGNAL(accepted()), this, SLOT(validePayment()));
        QObject::connect(&mValidatePayment, SIGNAL(rejected()), this, SLOT(reject()));
        QObject::connect(&mMountNumber.mZeroButton, SIGNAL(clicked()), this, SLOT(enterPinZero()));
        QObject::connect(&mMountNumber.mOneButton, SIGNAL(clicked()), this, SLOT(enterPinOne()));
        QObject::connect(&mMountNumber.mTwoButton, SIGNAL(clicked()), this, SLOT(enterPinTwo()));
        QObject::connect(&mMountNumber.mThreeButton, SIGNAL(clicked()), this, SLOT(enterPinThree()));
        QObject::connect(&mMountNumber.mFourButton, SIGNAL(clicked()), this, SLOT(enterPinFour()));
        QObject::connect(&mMountNumber.mFiveButton, SIGNAL(clicked()), this, SLOT(enterPinFive()));
        QObject::connect(&mMountNumber.mSixButton, SIGNAL(clicked()), this, SLOT(enterPinSix()));
        QObject::connect(&mMountNumber.mSevenButton, SIGNAL(clicked()), this, SLOT(enterPinSeven()));
        QObject::connect(&mMountNumber.mEightButton, SIGNAL(clicked()), this, SLOT(enterPinHeight()));
        QObject::connect(&mMountNumber.mNineButton, SIGNAL(clicked()), this, SLOT(enterPinNine()));
        QObject::connect(&mMountNumber.mSuppButton, SIGNAL(clicked()), this, SLOT(enterSupp()));
        QObject::connect(&mMountNumber.mCommaButton, SIGNAL(clicked()), this, SLOT(enterComma()));
        QObject::connect(&mCashInPayment, SIGNAL(clicked()), this, SLOT(cashIn()));
    }

    void    CashPaymentDialog::keyPressEvent(QKeyEvent *e)
    {
        if (e->key() != Qt::Key_Escape)
            QDialog::keyPressEvent(e);
    }

}
}
}
}
//!
//! @file CreditCardDialog.cpp
//! @author jbruel
//! @date 18/12/18
//!

#include <iomanip>
#include <plog/Severity.h>
#include <Tools/Log/Idx.hpp>
#include <plog/Log.h>
#include "Windows/Cashier/Dialogs/CreditCardDialog.hpp"
#include <QKeyEvent>

namespace cash
{
namespace win
{
namespace cashier
{
namespace dialog
{

    CreditCardDialog::CreditCardDialog(QWidget *parent) :   QDialog(parent), mValidateDialogButtons(this), mPaymentStatus(this),
                                                            mPaymentProgress(this), mBill(this), mBillValue(0),
                                                            mPaymentProgressPalette(), mLastPaymentStatus(false)
    {
        setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        initWindow();
        initWidgets();
        QObject::connect(&mValidateDialogButtons, SIGNAL(accepted()), this, SLOT(accept()));
        QObject::connect(&mValidateDialogButtons, SIGNAL(rejected()), this, SLOT(reject()));
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Cashier: Initialize credit card dialog.";
        QMetaObject::connectSlotsByName(this);
    }

    bool    CreditCardDialog::execDialog()
    {
        std::stringstream   stream;

        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Launching card payment dialog.";
        stream << std::fixed << std::setprecision(2) << mBillValue;
        mPaymentStatus.setText(QString("Waiting card insertion"));
        mBill.setText(QApplication::translate("Dialog", std::string(stream.str() + " EUR").c_str(), Q_NULLPTR));
        mPaymentProgress.setValue(0);
        mValidateDialogButtons.setDisabled(true);
        mLastPaymentStatus = false;
        exec();
        return (mLastPaymentStatus);
    }

    void    CreditCardDialog::keyPressEvent(QKeyEvent *e)
    {
        if (e->key() != Qt::Key_Escape)
            QDialog::keyPressEvent(e);
    }

    bool    CreditCardDialog::update(std::shared_ptr<core::PaymentUpdate> &up)
    {
        QPalette    p = palette();

        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Received update payment status : " << up->mMsg;
        mPaymentStatus.setText(QString(up->mMsg.c_str()));
        if (mPaymentStateMachine.at(up->mStatus) == 100)
        {
            if (up->mStatus == core::PaymentStatus::PROCESS_PAYMENT_FINISH)
            {
                p.setColor(QPalette::Highlight, Qt::darkGreen);
                mValidateDialogButtons.setDisabled(false);
                mLastPaymentStatus = true;
            }
            else if (up->mStatus == core::PaymentStatus::PAYMENT_TYPE_CONNECTION_FAIL ||
                     up->mStatus == core::PaymentStatus::CREDIT_CARD_RIPPED_OFF ||
                     up->mStatus == core::PaymentStatus::PAYMENT_SERVER_AUTH_FAIL ||
                     up->mStatus == core::PaymentStatus::PAYMENT_REFUSE)
            {
                p.setColor(QPalette::Highlight, Qt::red);
                mValidateDialogButtons.setDisabled(false);
                LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Payment status: " << up->mStatus;
            }
            else if (up->mStatus == core::PaymentStatus::PAYMENT_SERVER_CONNECTION_FAIL ||
                     up->mStatus == core::PaymentStatus::PAYMENT_SERVER_CHECK_CODE_FAIL)
            {
                p.setColor(QPalette::Highlight, Qt::red);
                LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Payment status: " << up->mStatus;
            }
            mPaymentProgress.setPalette(p);
        }
        else
            mPaymentProgress.setPalette(mPaymentProgressPalette);
        mPaymentProgress.setValue(mPaymentStateMachine.at(up->mStatus));
        repaint();
        return (true);
    }

    void    CreditCardDialog::initWindow()
    {
        if (objectName().isEmpty())
            setObjectName(QStringLiteral("Dialog"));
        setFixedSize(267, 233);
        setWindowTitle(QApplication::translate("Dialog", "Credit card payment", Q_NULLPTR));
        setWindowModality(Qt::WindowModal);
    }

    void    CreditCardDialog::initWidgets()
    {
        QPalette    p = palette();

        mValidateDialogButtons.setObjectName(QStringLiteral("mValidateDualogButtons"));
        mValidateDialogButtons.setGeometry(QRect(60, 180, 181, 32));
        mValidateDialogButtons.setOrientation(Qt::Horizontal);
        mValidateDialogButtons.setStandardButtons(QDialogButtonBox::Ok);
        mValidateDialogButtons.setDisabled(true);
        mPaymentStatus.setObjectName(QStringLiteral("mPaymentStatus"));
        mPaymentStatus.setGeometry(QRect(20, 110, 221, 21));
        mPaymentStatus.setAlignment(Qt::AlignCenter);
        mPaymentStatus.setText(QString());
        mPaymentProgress.setObjectName(QStringLiteral("mPaymentProgress"));
        mPaymentProgress.setGeometry(QRect(20, 60, 221, 31));
        mPaymentProgress.setValue(0);
        mPaymentProgressPalette = mPaymentProgress.palette();
        mBill.setObjectName(QStringLiteral("mBill"));
        mBill.setGeometry(QRect(66, 30, 131, 20));
        mBill.setAlignment(Qt::AlignCenter);
        mBill.setText(QApplication::translate("Dialog", "EUR", Q_NULLPTR));
    }

}
}
}
}
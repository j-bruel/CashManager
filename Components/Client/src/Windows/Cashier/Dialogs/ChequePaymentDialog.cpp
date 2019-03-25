//!
//! @file ChequePaymentDialog.cpp
//! @author jbruel
//! @date 24/12/18
//!

#include "Conf/AssetsPath.hpp"
#include "Windows/Cashier/Dialogs/ChequePaymentDialog.hpp"
#include "Tools/Log/Idx.hpp"
#include <plog/Severity.h>
#include <plog/Log.h>
#include <QKeyEvent>
#include <Conf/ConnexionsSettings.hpp>
#include "Network/NetworkInfo.hpp"

namespace cash
{
namespace win
{
namespace cashier
{
namespace dialog
{

    ChequePaymentDialog::ChequePaymentDialog(QWidget *parent) : QDialog(parent), mValidatePayment(this), mChequeImage(this),
                                                                mPaymentProgess(this), mPaymentStatus(this),
                                                                mAmountText(this), mAmonutValue(this), mDateText(this),
                                                                mDateValue(this), mFromText(this), mFromValue(this),
                                                                mToText(this), mToValue(this), mWhereText(this),
                                                                mWhereValue(this), mNumberText(this), mNumberValue(this),
                                                                mPaymentProgressPalette(), mBillValue(0), mPaymentValidate(false),
                                                                mChequeChecked(false), mChequeInfoGenerator(),
                                                                mSettings(conf::ConnexionsSettings::Instance()),
                                                                mBank(BANK_URL, BANK_PORT)
    {
        setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        initWindow();
        initWidgets();
        QObject::connect(&mValidatePayment, SIGNAL(accepted()), this, SLOT(validePayment()));
        QObject::connect(&mValidatePayment, SIGNAL(rejected()), this, SLOT(reject()));
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Cashier: Initialize credit card dialog.";
        QMetaObject::connectSlotsByName(this);
    }

    bool    ChequePaymentDialog::execChequeDialog()
    {
        std::stringstream   stream;

        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Running cheque payment.";
        mPaymentProgess.setPalette(mPaymentProgressPalette);
        mValidatePayment.setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        mValidatePayment.setEnabled(true);
        mPaymentProgess.setValue(10);
        stream << std::fixed << std::setprecision(2) << mBillValue;
        mPaymentStatus.setText(QApplication::translate("Dialog", "Checking cheque scan.", Q_NULLPTR));
        mAmonutValue.setText(QApplication::translate("Dialog", std::string(stream.str() + " EUR").c_str(), Q_NULLPTR));
        mDateValue.setText(QApplication::translate("Dialog", mChequeInfoGenerator.getCurrentTime().c_str(), Q_NULLPTR));
        mFromValue.setText(QApplication::translate("Dialog", mChequeInfoGenerator.generateName().c_str(), Q_NULLPTR));
        mToValue.setText(QApplication::translate("Dialog", "POMMED’EPITECH", Q_NULLPTR));
        mWhereValue.setText(QApplication::translate("Dialog", "Le Kremlin-Bicêtre.", Q_NULLPTR));
        mNumberValue.setText(QApplication::translate("Dialog", mChequeInfoGenerator.generateChequeNumber().c_str(), Q_NULLPTR));
        mPaymentValidate = false;
        mChequeChecked = false;
        exec();
        return (mPaymentValidate);
    }

    void    ChequePaymentDialog::validePayment()
    {
        if (mChequeChecked)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Cheque payment done.";
            mPaymentValidate = true;
            accept();
            return ;
        }

        QPalette    p = palette();
        std::string bankToken;

        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Cheque has been checked.";
        mChequeChecked = true;
        mValidatePayment.setEnabled(false);
        repaint();
        if (!serverConnexion(bankToken))
        {
            p.setColor(QPalette::Highlight, Qt::red);
            mPaymentProgess.setValue(100);
            mPaymentProgess.setPalette(p);
            mPaymentStatus.setText(QApplication::translate("Dialog", "Connexion failed.", Q_NULLPTR));
            mValidatePayment.setEnabled(true);
            mValidatePayment.setStandardButtons(QDialogButtonBox::Cancel);
            repaint();
            return;
        }
        if (!paymentOrder(bankToken))
        {
            p.setColor(QPalette::Highlight, Qt::red);
            mPaymentProgess.setValue(100);
            mPaymentProgess.setPalette(p);
            mPaymentStatus.setText(QApplication::translate("Dialog", "Cheque refused.", Q_NULLPTR));
            mValidatePayment.setEnabled(true);
            mValidatePayment.setStandardButtons(QDialogButtonBox::Cancel);
            repaint();
            return;
        }
        p.setColor(QPalette::Highlight, Qt::darkGreen);
        mPaymentProgess.setValue(100);
        mPaymentProgess.setPalette(p);
        mPaymentStatus.setText(QApplication::translate("Dialog", "Cheque authorized.", Q_NULLPTR));
        mValidatePayment.setEnabled(true);
        mValidatePayment.setStandardButtons(QDialogButtonBox::Ok);
        repaint();
    }

    bool    ChequePaymentDialog::serverConnexion(std::string &bankToken)
    {
        mPaymentProgess.setPalette(mPaymentProgressPalette);
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Connexion to the payment server.";
        mPaymentStatus.setText(QApplication::translate("Dialog", "Connexion in progress.", Q_NULLPTR));
        mPaymentProgess.setValue(30);
        repaint();

        network::Authenticate     *reply = mBank.authenticate("CHECK", mSettings.mAttempts, mSettings.mDelay * 1000);

        if (reply->status() != network::RequestStatus::GOOD)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "Cashier: Bank API: Authenticate impossible : " << reply->error_msg();
            return (false);
        }
        bankToken = reply->token();
        sleep(1);
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Connexion to the payment server establised.";
        mPaymentStatus.setText(QApplication::translate("Dialog", "Connexion established.", Q_NULLPTR));
        mPaymentProgess.setValue(50);
        repaint();
        sleep(2);
        return (true);
    }

    bool    ChequePaymentDialog::paymentOrder(const std::string &bankToken)
    {
        mPaymentProgess.setPalette(mPaymentProgressPalette);
        mPaymentStatus.setText(QApplication::translate("Dialog", "Pending authorization ...", Q_NULLPTR));
        mPaymentProgess.setValue(70);
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Pending bank authorization ...";
        repaint();

        network::BankCheck     *reply = mBank.check_payment(bankToken, mNumberValue.text().toStdString(), mBillValue);

        if (reply->status() != network::RequestStatus::GOOD)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "Cashier: Bank API: Cheque paiment impossible : " << reply->error_msg();
            return (false);
        }
        sleep(1);
        return (true);
    }

    void    ChequePaymentDialog::keyPressEvent(QKeyEvent *e)
    {
        if (e->key() != Qt::Key_Escape)
            QDialog::keyPressEvent(e);
    }

    void    ChequePaymentDialog::initWindow()
    {
        if (objectName().isEmpty())
            setObjectName(QStringLiteral("Dialog"));
        setFixedSize(317, 495);
        setWindowTitle(QApplication::translate("Dialog", "Cheque payment", Q_NULLPTR));
        setWindowModality(Qt::WindowModal);
    }

    void    ChequePaymentDialog::initWidgets()
    {
        mValidatePayment.setObjectName(QStringLiteral("mValidatePayment"));
        mValidatePayment.setGeometry(QRect(120, 450, 181, 32));
        mValidatePayment.setOrientation(Qt::Horizontal);
        mValidatePayment.setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        mChequeImage.setObjectName(QStringLiteral("mChequeImage"));
        mChequeImage.setGeometry(QRect(10, 10, 291, 121));
        mChequeImage.setStyleSheet(QStringLiteral("border-image: url(") + cash::conf::getAssetPath().c_str() + QStringLiteral("cheque-real.png) no-repeat center"));
        mPaymentProgess.setObjectName(QStringLiteral("mPaymentProfess"));
        mPaymentProgess.setGeometry(QRect(37, 150, 241, 31));
        mPaymentProgess.setValue(24);
        mPaymentStatus.setObjectName(QStringLiteral("mPaymentStatus"));
        mPaymentStatus.setGeometry(QRect(66, 200, 181, 31));
        mPaymentStatus.setAlignment(Qt::AlignCenter);
        mAmountText.setObjectName(QStringLiteral("mAmountText"));
        mAmountText.setGeometry(QRect(20, 250, 81, 31));
        mAmountText.setText(QApplication::translate("Dialog", "Amount", Q_NULLPTR));
        mAmonutValue.setObjectName(QStringLiteral("mAmonutValue"));
        mAmonutValue.setGeometry(QRect(130, 250, 171, 31));
        mAmonutValue.setAlignment(Qt::AlignCenter);
        mDateText.setObjectName(QStringLiteral("mDateText"));
        mDateText.setGeometry(QRect(20, 280, 81, 31));
        mDateText.setText(QApplication::translate("Dialog", "Date", Q_NULLPTR));
        mDateValue.setObjectName(QStringLiteral("mDateValue"));
        mDateValue.setGeometry(QRect(130, 280, 171, 31));
        mDateValue.setAlignment(Qt::AlignCenter);
        mFromText.setObjectName(QStringLiteral("mFromText"));
        mFromText.setGeometry(QRect(20, 310, 81, 31));
        mFromText.setText(QApplication::translate("Dialog", "From", Q_NULLPTR));
        mFromValue.setObjectName(QStringLiteral("mFromValue"));
        mFromValue.setGeometry(QRect(130, 310, 171, 31));
        mFromValue.setAlignment(Qt::AlignCenter);
        mToText.setObjectName(QStringLiteral("mToTest"));
        mToText.setGeometry(QRect(20, 340, 81, 31));
        mToText.setText(QApplication::translate("Dialog", "To", Q_NULLPTR));
        mToValue.setObjectName(QStringLiteral("mToValue"));
        mToValue.setGeometry(QRect(130, 340, 171, 31));
        mToValue.setAlignment(Qt::AlignCenter);
        mWhereText.setObjectName(QStringLiteral("mWhereText"));
        mWhereText.setGeometry(QRect(20, 370, 81, 31));
        mWhereText.setText(QApplication::translate("Dialog", "Where", Q_NULLPTR));
        mWhereValue.setObjectName(QStringLiteral("mWhereValue"));
        mWhereValue.setGeometry(QRect(130, 370, 171, 31));
        mNumberText.setObjectName(QStringLiteral("mNumberText"));
        mNumberText.setGeometry(QRect(20, 400, 81, 31));
        mNumberText.setText(QApplication::translate("Dialog", "Number", Q_NULLPTR));
        mWhereValue.setAlignment(Qt::AlignCenter);
        mNumberValue.setObjectName(QStringLiteral("mNumberValue"));
        mNumberValue.setGeometry(QRect(130, 400, 171, 31));
        mNumberValue.setAlignment(Qt::AlignCenter);
        mPaymentProgressPalette = mPaymentProgess.palette();
    }

}
}
}
}

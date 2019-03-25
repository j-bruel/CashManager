//!
//! @file PaymentTerminalScreen.cpp
//! @author jbruel
//! @date 13/12/18
//!

#include <Tools/Log/Idx.hpp>
#include <plog/Severity.h>
#include <plog/Log.h>
#include <Conf/AssetsPath.hpp>
#include "Windows/PaymentTerminal/Widgets/PaymentTerminalScreen.hpp"
#include "Network/NetworkInfo.hpp"
#include "Network/BankAPI.hpp"
#include <random>

namespace cash
{
namespace win
{
namespace term
{
namespace widget
{

    PaymentTerminalScreen::PaymentTerminalScreen(QWidget *parent) : QWidget(parent), mLine(parent), mScreenUserInformation(parent),
                                                                    mPaymentDescription(&mScreenUserInformation), mBill(&mScreenUserInformation),
                                                                    mBillValue(0), mContactLessLogo(&mScreenUserInformation), mInsertCard(parent),
                                                                    mCodes(parent, &mPaymentDescription, this),
                                                                    mPaymentProcessRunning(false), mCardInsert(false),
                                                                    mBankFinishPayment(false), mCardRipped(false),
                                                                    mSettings(conf::ConnexionsSettings::Instance()),
                                                                    mBank(BANK_URL, BANK_PORT), mBankToken(), mLastCardNumber(generateCardNumber())
    {
        initParentWindow(parent);
        initScreenUserInformationPayment();
        QMetaObject::connectSlotsByName(parent);
        connect(&mInsertCard, SIGNAL(clicked()), this, SLOT(insertCreditCard()));
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "MPT: Payment terminal has been loaded.";
    }

    void    PaymentTerminalScreen::validPinCode()
    {
        if (mCodes.getUserPinCode().size() < 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Impossible to validate this current pin code, the code must be 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: The user valid his pin code.";

        network::CardPayment     *reply = mBank.card_payment(mBankToken, "MASTER", mLastCardNumber, mCodes.getUserPinCode(),
                                                             static_cast<float>(mBillValue),
                                                             static_cast<unsigned int>(mSettings.mDelay * 1000));

        if (reply->status() != network::RequestStatus::GOOD)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Bank API: Card payment impossible, msg : " << reply->error_msg();
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Bank API: Card payment impossible, code : " << reply->error_code();
            if (reply->error_code() == network::RequestAPIErrors::BANK_INVALID_PIN)
            {
                mPaymentDescription.setText(QApplication::translate("Form", "Wrong code.", Q_NULLPTR));
                mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_SERVER_CHECK_CODE_FAIL, "Wrong code.");
                LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Wrong pin code.";
                repaint();
                sleep(2);
                LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "MPT: Reset pin to empty.";
                mCodes.correctPin();
                mCodes.correctPin();
                mCodes.correctPin();
                mCodes.correctPin();
                allowUserCodePin();
//                delete reply;
                return ;
            }
            bankRefusePayment();
//            delete reply;
            return ;
        }
//        delete reply;
        sleep(1);
        mPaymentDescription.setText(QApplication::translate("Form", "Correct code.", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_SERVER_CHECK_CODE_DONE, "Correct code.");
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: User enter correct pin.";
        repaint();
        sleep(2);
        mPaymentDescription.setText(QApplication::translate("Form", "Pending authorization ...", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_SERVER_AUTH_PENDING, "Pending authorization ...");
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: Pending bank authorization ...";
        repaint();
        sleep(2);
        mPaymentDescription.setText(QApplication::translate("Form", "Card payment accepted.", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_VALID, "Card payment accepted.");
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: Card payment accepted.";
        mCodes.disconnectPins();
        repaint();
        sleep(2);
        mPaymentDescription.setText(QApplication::translate("Form", "You can take off your card.", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::USER_MUST_REMOVE_CREDIT_CARD, "User can take off your card.");
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: User can take off his card.";
        repaint();
        mBankFinishPayment = true;
    }

    void    PaymentTerminalScreen::cancelPinEnter()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::warning) << "MPT: The user cancel during payment state.";
        mCodes.disconnectPins();
        mPaymentDescription.setText(QApplication::translate("Form", "Operation cancel.", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::MPT_CANCEL_PAYMENT, "User cancel operation.");
        repaint();
        sleep(2);
        if (mCardInsert)
        {
            mPaymentDescription.setText(QApplication::translate("Form", "You can take off your card.", Q_NULLPTR));
            mCodes.notifyCashierUpdate(core::PaymentStatus::USER_MUST_REMOVE_CREDIT_CARD, "User can take off your card.");
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: User can take off his card.";
            repaint();
            mCardRipped = false;
            return;
        }
        mInsertCard.setText(QApplication::translate("Form", "Insert Credit Card", Q_NULLPTR));
        repaint();
        sleep(2);
        mCardInsert = false;
        repaint();
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_REFUSE, "Payment refused.");
        finishPaymentProcess();
    }

    void    PaymentTerminalScreen::bankRefusePayment()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: The bank refuse payment.";
        mCodes.disconnectPins();
        mPaymentDescription.setText(QApplication::translate("Form", "Card payment refused", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_BANK_REFUSE, "Card payment refused");
        repaint();
        sleep(2);
        if (mCardInsert)
        {
            mPaymentDescription.setText(QApplication::translate("Form", "You can take off your card.", Q_NULLPTR));
            mCodes.notifyCashierUpdate(core::PaymentStatus::USER_MUST_REMOVE_CREDIT_CARD, "User can take off your card.");
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: User can take off his card.";
            repaint();
            mCardRipped = false;
            return;
        }
        mInsertCard.setText(QApplication::translate("Form", "Insert Credit Card", Q_NULLPTR));
        repaint();
        sleep(2);
        mCardInsert = false;
        repaint();
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_REFUSE, "Payment refused.");
        finishPaymentProcess();
    }

    void    PaymentTerminalScreen::insertCreditCard()
    {
        if (!mPaymentProcessRunning)
            return ;
        if (!mCardInsert)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: User insert his credit card.";
            mInsertCard.setText(QApplication::translate("Form", "Take Off Credit Card", Q_NULLPTR));
            mCodes.notifyCashierUpdate(core::PaymentStatus::CREDIT_CARD_INSERT, "User insert his credit card.");
            disconnect(mContactLessConnect);
            mLastCardNumber = generateCardNumber();
            mCardInsert = true;
            if (!connectPaymentServer("CARD"))
            {
                serverConnectFail();
                mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_REFUSE, "Payment refused.");
                finishPaymentProcess();
                return ;
            }
            allowUserCodePin();
        }
        else
        {
            mCodes.disconnectPins();
            if (!mBankFinishPayment && mCardRipped)
            {
                mPaymentDescription.setText(QApplication::translate("Form", "Credit card ripped off.", Q_NULLPTR));
                mCodes.notifyCashierUpdate(core::PaymentStatus::CREDIT_CARD_RIPPED_OFF, "Credit card ripped off.");
                repaint();
                sleep(2);
                LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: User ripped off his credit card.";
                mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_REFUSE, "Payment refused.");
            }
            else if (!mBankFinishPayment)
            {
                mPaymentDescription.setText(QApplication::translate("Form", "Credit card take off.", Q_NULLPTR));
                mCodes.notifyCashierUpdate(core::PaymentStatus::CREDIT_CARD_TAKE_OFF, "Credit card take off.");
                repaint();
                sleep(2);
                mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_REFUSE, "Payment refused.");
            }
            else
                mCodes.notifyCashierUpdate(core::PaymentStatus::PROCESS_PAYMENT_FINISH, "Payment complet.");
            mInsertCard.setText(QApplication::translate("Form", "Insert Credit Card", Q_NULLPTR));
            mCardInsert = false;
            repaint();
            finishPaymentProcess();
        }
        mBankFinishPayment = false;
        repaint();
    }

    void    PaymentTerminalScreen::contactLessPayment()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: The user valid a contact less payment.";
        if (!connectPaymentServer("CONTACTLESS"))
        {
            serverConnectFail();
            mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_REFUSE, "Payment refused.");
            finishPaymentProcess();
            return ;
        }
        mPaymentDescription.setText(QApplication::translate("Form", "Pending authorization ...", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_SERVER_AUTH_PENDING, "Pending authorization ...");
        mCodes.disconnectPins();
        repaint();

        network::CardPaymentContactless *reply = mBank.card_payment_contactless(mBankToken, "MASTER", generateCardNumber(),
                                                                               static_cast<float>(mBillValue),
                                                                               static_cast<unsigned int>(mSettings.mDelay * 1000));

        if (reply->status() != network::RequestStatus::GOOD)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Bank API: Card payment impossible, msg : " << reply->error_msg();
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Bank API: Card payment impossible, code : " << reply->error_code();
            bankRefusePayment();
//            delete reply;
            finishPaymentProcess();
            return ;
        }
//        delete reply;
        sleep(1);
        mPaymentDescription.setText(QApplication::translate("Form", "Card payment accepted.", Q_NULLPTR));
        repaint();
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_VALID, "Card payment accepted.");
        sleep(2);
        mBankFinishPayment = true;
        mCardInsert = false;
        repaint();
        mCodes.notifyCashierUpdate(core::PaymentStatus::PROCESS_PAYMENT_FINISH, "Payment complet.");
        finishPaymentProcess();
    }

    bool    PaymentTerminalScreen::payment(double bill)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: Payment terminal received bill order : " << bill;
        if (mPaymentProcessRunning)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Impossible to run a payment process, one proccess already running.";
            return (false);
        }
        if (bill <= 0)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Impossible to order a bill under or equal 0.";
            return (false);
        }
        startPaymentProcess();
        setBillPayment(bill);
        return (true);
    }

    void    PaymentTerminalScreen::allowUserCodePin()
    {
        mPaymentDescription.setText(QApplication::translate("Form", "Enter card PIN code.", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::MPT_WAITING_CODE, "Waiting user pin code.");
        mCodes.connectPins();
    }

    void    PaymentTerminalScreen::startPaymentProcess()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "MPT: Payment process running.";
        mPaymentDescription.setText(QApplication::translate("Form", "Insert your credit card.", Q_NULLPTR));
        mContactLessConnect = connect(&mContactLessLogo, SIGNAL(clicked()), this, SLOT(contactLessPayment()));
        mInsertCard.setEnabled(true);
        repaint();
        mCodes.connectCancel();
        mPaymentProcessRunning = true;
        mCardInsert = false;
        mCardRipped = true;
    }

    void    PaymentTerminalScreen::finishPaymentProcess()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "MPT: Payment process finish.";
        mBill.setText(QApplication::translate("Form", "EUR", Q_NULLPTR));
        mBillValue = 0;
        mPaymentDescription.setText(QApplication::translate("Form", "EpiBank", Q_NULLPTR));
        mInsertCard.setEnabled(false);
        disconnect(mContactLessConnect);
        repaint();
        mPaymentProcessRunning = false;
    }

    void    PaymentTerminalScreen::setBillPayment(double bill)
    {
        std::stringstream   stream;

        stream << std::fixed << std::setprecision(2) << bill;
        mBill.setText(QApplication::translate("Form", std::string(stream.str() + " EUR").c_str(), Q_NULLPTR));
        mBillValue = bill;
        repaint();
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "MPT: Bill has been updated : " << bill << "€.";
    }

    void    PaymentTerminalScreen::initParentWindow(QWidget *parent)
    {
        if (parent->objectName().isEmpty())
            parent->setObjectName(QStringLiteral("Form"));
    }

    void    PaymentTerminalScreen::initScreenUserInformationPayment()
    {
        mLine.setObjectName(QStringLiteral("mLine"));
        mLine.setGeometry(QRect(20, 30, 341, 20));
        mLine.setLineWidth(3);
        mLine.setFrameShape(QFrame::HLine);
        mLine.setFrameShadow(QFrame::Sunken);
        mScreenUserInformation.setObjectName(QStringLiteral("mScreenUserInformations"));
        mScreenUserInformation.setGeometry(QRect(40, 60, 291, 161));
        mScreenUserInformation.setFrameShape(QFrame::StyledPanel);
        mScreenUserInformation.setFrameShadow(QFrame::Raised);
        mPaymentDescription.setObjectName(QStringLiteral("mPaymentDescription"));
        mPaymentDescription.setGeometry(QRect(0, 30, 291, 31));
        mPaymentDescription.setAlignment(Qt::AlignCenter);
        mPaymentDescription.setText(QApplication::translate("Form", "EpiBank", Q_NULLPTR));
        mBill.setObjectName(QStringLiteral("mBill"));
        mBill.setGeometry(QRect(10, 0, 281, 31));
        mBill.setAlignment(Qt::AlignCenter);
        mBill.setText(QApplication::translate("Form", "EUR ", Q_NULLPTR));
        mBillValue = 0;
        mContactLessLogo.setObjectName(QStringLiteral("mContactLessLogo"));
        mContactLessLogo.setGeometry(QRect(80, 80, 131, 51));
        mContactLessLogo.setStyleSheet(QStringLiteral("border-image: url(") + conf::getAssetPath().c_str() + QStringLiteral("contactless.png) no-repeat center"));
        mInsertCard.setObjectName(QStringLiteral("mInsertCard"));
        mInsertCard.setGeometry(QRect(30, 500, 321, 21));
        mInsertCard.setEnabled(false);
        mInsertCard.setText(QApplication::translate("Form", "Insert Credit Card", Q_NULLPTR));
    }

    bool    PaymentTerminalScreen::connectPaymentServer(const std::string &paymentType)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "MPT: Connexion to the payment server.";
        mPaymentDescription.setText(QApplication::translate("Form", "Connexion in progress.", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_SERVER_CONNECTION_WAITING, "Connexion in progress.");
        repaint();

        network::Authenticate     *reply = nullptr;

        for (size_t i = 0; i < mSettings.mAttempts; ++i)
        {
//            if (i > 0)
//                delete reply;
            reply = mBank.authenticate(paymentType, 3, static_cast<unsigned int>(mSettings.mDelay * 1000));
            if (reply->status() == network::RequestStatus::GOOD)
                break ;
            if (i + 1 == mSettings.mAttempts)
            {
                LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Bank API: Authenticate impossible : " << reply->error_msg();
//                delete reply;
                return (false);
            }
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: Connexion to the payment server failed.";
            mPaymentDescription.setText(QApplication::translate("Form", "Connexion refused.", Q_NULLPTR));
            mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_SERVER_CONNECTION_FAIL, "Connexion refused.");
            repaint();
            sleep(2);
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: Retry connexion to the payment server.";
            mPaymentDescription.setText(QApplication::translate("Form", "Connexion retry.", Q_NULLPTR));
            mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_SERVER_CONNECTION_RETRY, "Connexion retry.");
            repaint();
            sleep(2);
        }
        if (reply == nullptr)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Bank API: Authenticate impossible : " << reply->error_msg();
//            delete reply;
            return (false);
        }
        mBankToken = reply->token();
//        delete reply;
        sleep(1);
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "MPT: Connexion to the payment server establised.";
        mPaymentDescription.setText(QApplication::translate("Form", "Connexion established.", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_SERVER_CONNECTION_DONE, "Connexion established.");
        repaint();
        sleep(2);
        return (true);
    }

    void    PaymentTerminalScreen::serverConnectFail()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Payment server refused connexion.";
        mPaymentDescription.setText(QApplication::translate("Form", "Connexion refused.", Q_NULLPTR));
        mCodes.notifyCashierUpdate(core::PaymentStatus::PAYMENT_SERVER_CONNECTION_FAIL, "Connexion refused.");
        repaint();
        sleep(2);
    }

    std::string PaymentTerminalScreen::generateCardNumber() const
    {
        std::string nb;

        for (size_t i = 0; i < 16; ++i)
            nb += std::to_string(generateRandomNumber(9));
        return (nb);
    }

    size_t  PaymentTerminalScreen::generateRandomNumber(size_t max) const
    {
        std::random_device seeder;

        std::mt19937 engine(seeder());
        std::uniform_int_distribution<int> dist(0, max);
        return (dist(engine));
    }

}
}
}
}
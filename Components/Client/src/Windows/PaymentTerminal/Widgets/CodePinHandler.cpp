//!
//! @file CodePinHandler.cpp
//! @author jbruel
//! @date 16/12/18
//!

#include <QtWidgets/QApplication>
#include <Tools/Log/Idx.hpp>
#include <plog/Severity.h>
#include <plog/Log.h>
#include "Windows/PaymentTerminal/Widgets/CodePinHandler.hpp"
#include "Windows/PaymentTerminal/Widgets/PaymentTerminalScreen.hpp"

namespace cash
{
namespace win
{
namespace term
{
namespace widget
{

    CodePinHandler::CodePinHandler(QWidget *parent, QLabel *pinLabel, PaymentTerminalScreen *mpt) :
                                                        QWidget(parent), mPinCode(), mOneButton(parent), mTwoButton(parent),
                                                        mThreeButton(parent), mFourButton(parent), mFiveButton(parent),
                                                        mSixButton(parent), mSevenButton(parent), mEightButton(parent),
                                                        mNineButton(parent), mUnUseButton(parent), mUnUseButton2(parent),
                                                        mZeroButton(parent), mCancelButton(parent),mValidateButton(parent),
                                                        mCorrectButton(parent), mPaymentTerminal(mpt), mPinLabel(pinLabel),
                                                        mPinsAlreadyConnect(false)
    {
        initButtons();
    }

    void    CodePinHandler::connectPins()
    {
        if (mPinsAlreadyConnect)
            return ;
        mOneConnect = connect(&mOneButton, SIGNAL(clicked()), this, SLOT(enterPinOne()));
        mTwoConnect = connect(&mTwoButton, SIGNAL(clicked()), this, SLOT(enterPinTwo()));
        mThreeConnect = connect(&mThreeButton, SIGNAL(clicked()), this, SLOT(enterPinThree()));
        mFourConnect = connect(&mFourButton, SIGNAL(clicked()), this, SLOT(enterPinFour()));
        mFiveConnect = connect(&mFiveButton, SIGNAL(clicked()), this, SLOT(enterPinFive()));
        mSixConnect = connect(&mSixButton, SIGNAL(clicked()), this, SLOT(enterPinSix()));
        mSevenConnect = connect(&mSevenButton, SIGNAL(clicked()), this, SLOT(enterPinSeven()));
        mHeightConnect = connect(&mEightButton, SIGNAL(clicked()), this, SLOT(enterPinHeight()));
        mNineConnect = connect(&mNineButton, SIGNAL(clicked()), this, SLOT(enterPinNine()));
        mZeroConnect = connect(&mZeroButton, SIGNAL(clicked()), this, SLOT(enterPinZero()));
        mCorrectConnect = connect(&mCorrectButton, SIGNAL(clicked()), this, SLOT(correctPin()));
        mValidateConnect = connect(&mValidateButton, SIGNAL(clicked()), mPaymentTerminal, SLOT(validPinCode()));
        mPinsAlreadyConnect = true;
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: All buttons connections has been set.";
    }

    void    CodePinHandler::connectCancel()
    {
        mCancelConnect = connect(&mCancelButton, SIGNAL(clicked()), mPaymentTerminal, SLOT(cancelPinEnter()));
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Cancel buttons connections has been set.";
    }

    void    CodePinHandler::disconnectPins()
    {
        disconnect(mOneConnect);
        disconnect(mTwoConnect);
        disconnect(mThreeConnect);
        disconnect(mFourConnect);
        disconnect(mFiveConnect);
        disconnect(mSixConnect);
        disconnect(mSevenConnect);
        disconnect(mHeightConnect);
        disconnect(mNineConnect);
        disconnect(mZeroConnect);
        disconnect(mCorrectConnect);
        disconnect(mValidateConnect);
        disconnect(mCancelConnect);
        mPinsAlreadyConnect = false;
        mPinCode.clear();
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: All buttons connections has been unset.";
    }

    void    CodePinHandler::enterPinOne()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '1' has been enter by the user.";
        mPinCode += '1';
        setPinLabel();

        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::enterPinTwo()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '2' has been enter by the user.";
        mPinCode += '2';
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::enterPinThree()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '3' has been enter by the user.";
        mPinCode += '3';
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::enterPinFour()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '4' has been enter by the user.";
        mPinCode += '4';
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::enterPinFive()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '5' has been enter by the user.";
        mPinCode += '5';
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::enterPinSix()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '6' has been enter by the user.";
        mPinCode += '6';
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::enterPinSeven()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '7' has been enter by the user.";
        mPinCode += '7';
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::enterPinHeight()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '8' has been enter by the user.";
        mPinCode += '8';
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::enterPinNine()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '9' has been enter by the user.";
        mPinCode += '9';
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::enterPinZero()
    {
        if (mPinCode.size() >= 4)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Pin code max 4 numbers.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Pin '0' has been enter by the user.";
        mPinCode += '0';
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::correctPin()
    {
        if (mPinCode.empty())
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "MPT: Impossible to correct the last pin, the pin is empty.";
            return ;
        }
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: The last pin has been removed.";
        mPinCode = mPinCode.substr(0, mPinCode.size() - 1);
        setPinLabel();
        notifyCashierUpdate(core::PaymentStatus::MPT_ENTER_CODE, "Pin : " + mPinLabel->text().toStdString());
    }

    void    CodePinHandler::notifyCashierUpdate(core::PaymentStatus status, const std::string &msg)
    {
        std::shared_ptr<core::PaymentUpdate>    order = std::make_shared<core::PaymentUpdate>(core::PaymentUpdate(status, msg));

        tool::Subject<core::PaymentUpdate>::notify(order);
    }

    void    CodePinHandler::initButtons()
    {
        mOneButton.setObjectName(QStringLiteral("mOneButton"));
        mOneButton.setGeometry(QRect(70, 250, 71, 31));
        mOneButton.setText(QApplication::translate("Form", "1", Q_NULLPTR));
        mTwoButton.setObjectName(QStringLiteral("mTwoButton"));
        mTwoButton.setGeometry(QRect(150, 250, 71, 31));
        mTwoButton.setText(QApplication::translate("Form", "2", Q_NULLPTR));
        mThreeButton.setObjectName(QStringLiteral("mThreeButton"));
        mThreeButton.setGeometry(QRect(230, 250, 71, 31));
        mThreeButton.setText(QApplication::translate("Form", "3", Q_NULLPTR));
        mFourButton.setObjectName(QStringLiteral("mFourButton"));
        mFourButton.setGeometry(QRect(70, 300, 71, 31));
        mFourButton.setText(QApplication::translate("Form", "4", Q_NULLPTR));
        mFiveButton.setObjectName(QStringLiteral("mFiveButton"));
        mFiveButton.setGeometry(QRect(150, 300, 71, 31));
        mFiveButton.setText(QApplication::translate("Form", "5", Q_NULLPTR));
        mSixButton.setObjectName(QStringLiteral("mSixButton"));
        mSixButton.setGeometry(QRect(230, 300, 71, 31));
        mSixButton.setText(QApplication::translate("Form", "6", Q_NULLPTR));
        mSevenButton.setObjectName(QStringLiteral("mSevenButton"));
        mSevenButton.setGeometry(QRect(70, 350, 71, 31));
        mSevenButton.setText(QApplication::translate("Form", "7", Q_NULLPTR));
        mEightButton.setObjectName(QStringLiteral("mEightButton"));
        mEightButton.setGeometry(QRect(150, 350, 71, 31));
        mEightButton.setText(QApplication::translate("Form", "8", Q_NULLPTR));
        mNineButton.setObjectName(QStringLiteral("mNineButton"));
        mNineButton.setGeometry(QRect(230, 350, 71, 31));
        mNineButton.setText(QApplication::translate("Form", "9", Q_NULLPTR));
        mUnUseButton.setObjectName(QStringLiteral("mUnUseButton"));
        mUnUseButton.setGeometry(QRect(230, 400, 71, 31));
        mUnUseButton.setText(QString());
        mUnUseButton2.setObjectName(QStringLiteral("mUnUseButton2"));
        mUnUseButton2.setGeometry(QRect(70, 400, 71, 31));
        mUnUseButton2.setText(QString());
        mZeroButton.setObjectName(QStringLiteral("mZeroButton"));
        mZeroButton.setGeometry(QRect(150, 400, 71, 31));
        mZeroButton.setText(QApplication::translate("Form", "0", Q_NULLPTR));
        mCancelButton.setObjectName(QStringLiteral("mCancelButton"));
        mCancelButton.setGeometry(QRect(70, 450, 71, 31));
        mCancelButton.setStyleSheet(QStringLiteral("background-color: red"));
        mCancelButton.setText(QString());
        mValidateButton.setObjectName(QStringLiteral("mValidateButton"));
        mValidateButton.setGeometry(QRect(230, 450, 71, 31));
        mValidateButton.setStyleSheet(QStringLiteral("background-color: green"));
        mValidateButton.setText(QString());
        mCorrectButton.setObjectName(QStringLiteral("mCorrectButton"));
        mCorrectButton.setGeometry(QRect(150, 450, 71, 31));
        mCorrectButton.setStyleSheet(QStringLiteral("background-color: yellow"));
        mCorrectButton.setText(QString());
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "MPT: Buttons layout has been initialize.";
    }

    void    CodePinHandler::setPinLabel()
    {
        std::string pins;

        if (mPinLabel == nullptr)
            return ;
        if (mPinCode.empty())
        {
            mPinLabel->setText(QApplication::translate("Form", "Enter card PIN code.", Q_NULLPTR));
            return ;
        }
        for (size_t i = 0; i < mPinCode.size(); ++i)
            pins += '*';
        mPinLabel->setText(QApplication::translate("Form", pins.c_str(), Q_NULLPTR));
    }

}
}
}
}
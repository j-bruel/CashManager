//!
//! @file CashierScreen.cpp
//! @author jbruel
//! @date 17/12/18
//!

#include <plog/Severity.h>
#include <Tools/Log/Idx.hpp>
#include <plog/Log.h>
#include <Conf/AssetsPath.hpp>
#include <Conf/ConnexionsSettings.hpp>
#include "Windows/Cashier/Widgets/CashierScreen.hpp"

namespace cash
{
namespace win
{
namespace cashier
{
namespace widget
{

    CashierScreen::CashierScreen(QWidget *parent) : mOptionsSeparator(parent), mScan(parent), mCancel(parent),
                                                    mBasketSeperator(parent), mBasketImage(parent), mBill(parent),
                                                    mSetting(parent), mArticlesSeparator(parent), mSum(parent),
                                                    mBillIcon(parent), mBillSeparator(parent), mCash(parent),
                                                    mCheque(parent), mCard(parent), mArticles(parent), mBillValue(0),
                                                    mCreditCardPaymentDialog(parent), mSettingDialog(parent), mCashPaymentDialog(parent),
                                                    mChequePaymentDialog(parent), mArticleGenerator()
    {
        initWindow(parent);
        initWidgets();
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Cashier: All widgets initialize.";
        QMetaObject::connectSlotsByName(parent);
    }

    void    CashierScreen::scanArticle()
    {
        std::stringstream   stream;
        double  articlePrice = 0;

        mArticles.addItem(mArticleGenerator.generate(articlePrice));
        mBillValue += articlePrice;
        stream << std::fixed << std::setprecision(2) << mBillValue;
        mBill.setText(QApplication::translate("Form", std::string(stream.str() + " EUR").c_str(), Q_NULLPTR));
        repaint();
        updateBillScreen();
    }

    void    CashierScreen::updateBillScreen()
    {
        std::shared_ptr<double>    order = std::make_shared<double>(mBillValue);
        std::stringstream   stream;

        stream << std::fixed << std::setprecision(2) << mBillValue;
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Cashier: Bill screen order update launch, new bill : " << mBillValue;
        mBill.setText(QApplication::translate("Form", std::string(stream.str() + " EUR").c_str(), Q_NULLPTR));
        tool::Subject<double>::notify(order);
    }

    void    CashierScreen::runPayment()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Create a payment order for the mobile payment terminal.";
        mCreditCardPaymentDialog.setBill(mBillValue);
        if (mBillValue <= 0)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "Cashier: Impossible to run payment, bill must be upper than 0.";
            return ;
        }

        std::shared_ptr<core::PaymentOrder>    order = std::make_shared<core::PaymentOrder>(mBillValue, core::PaymentType::CARD);

        tool::Subject<core::PaymentOrder>::notify(order);
    }

    void    CashierScreen::rundialogPayment()
    {
        if (mBillValue <= 0)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "Cashier: Impossible to run payment, bill must be upper than 0.";
            return ;
        }
        if (mCreditCardPaymentDialog.execDialog())
        {
            mBillValue = 0;
            updateBillScreen();
            mArticles.clear();
            repaint();
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Clear bilL.";
        }
    }

    void    CashierScreen::execCashDialog()
    {
        if (mBillValue <= 0)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "Cashier: Impossible to run cash payment, bill must be upper than 0.";
            return ;
        }
        mCashPaymentDialog.setBill(mBillValue);
        if (mCashPaymentDialog.execCashDialog())
        {
            mBillValue = 0;
            updateBillScreen();
            mArticles.clear();
            repaint();
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Clear bilL.";
        }
    }

    void    CashierScreen::execChequeDialog()
    {
        if (mBillValue <= 0)
        {
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "Cashier: Impossible to run cheque payment, bill must be upper than 0.";
            return ;
        }
        mChequePaymentDialog.setBill(mBillValue);
        if (mChequePaymentDialog.execChequeDialog())
        {
            mBillValue = 0;
            updateBillScreen();
            mArticles.clear();
            repaint();
            LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Clear bilL.";
        }
    }

    void    CashierScreen::cancelPayment()
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Canceling order.";
        mBillValue = 0;
        updateBillScreen();
        mArticles.clear();
        repaint();
    }

    void    CashierScreen::articleItemClicked(QListWidgetItem *item)
    {
        std::string val = item->text().toStdString();

        if (val.empty() || val.size() < 5)
            return ;

        size_t      euroIdx = val.find_first_of("€");
        std::string price = val.substr(5, euroIdx - 5);

        mBillValue -= std::stod(price);
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::warning) << "Cashier: Remove a article, article price : " << std::stod(price);
        delete item;
        if (mArticles.count() == 0)
            mBillValue = 0;
        updateBillScreen();
    }

    void    CashierScreen::initWindow(QWidget *parent)
    {
        if (parent->objectName().isEmpty())
            parent->setObjectName(QStringLiteral("Form"));
        parent->resize(352, 659);
    }

    void    CashierScreen::initWidgets()
    {
        mOptionsSeparator.setObjectName(QStringLiteral("mOptionsSeparator"));
        mOptionsSeparator.setGeometry(QRect(0, 50, 351, 16));
        mOptionsSeparator.setFrameShape(QFrame::HLine);
        mOptionsSeparator.setFrameShadow(QFrame::Sunken);
        initScanButton();
        initCancelButton();
        initSettingButton();
        mBasketSeperator.setObjectName(QStringLiteral("mBasketSeperator"));
        mBasketSeperator.setGeometry(QRect(0, 110, 351, 16));
        mBasketSeperator.setFrameShape(QFrame::HLine);
        mBasketSeperator.setFrameShadow(QFrame::Sunken);
        mBasketImage.setObjectName(QStringLiteral("mBasketImage"));
        mBasketImage.setGeometry(QRect(30, 70, 41, 31));
        mBasketImage.setStyleSheet(QStringLiteral("border-image: url(") + conf::getAssetPath().c_str() + QStringLiteral("shopping-basket.png) no-repeat center"));
        mBasketImage.setText(QString());
        mBill.setObjectName(QStringLiteral("mBill"));
        mBill.setGeometry(QRect(176, 560, 141, 20));
        mBill.setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        mBill.setText(QApplication::translate("Form", "0 EUR", Q_NULLPTR));
        mArticlesSeparator.setObjectName(QStringLiteral("mArticlesSeparator"));
        mArticlesSeparator.setGeometry(QRect(0, 540, 351, 20));
        mArticlesSeparator.setFrameShape(QFrame::HLine);
        mArticlesSeparator.setFrameShadow(QFrame::Sunken);
        mSum.setObjectName(QStringLiteral("mSum"));
        mSum.setGeometry(QRect(0, 560, 67, 17));
        mSum.setAlignment(Qt::AlignCenter);
        mSum.setText(QApplication::translate("Form", "Sum", Q_NULLPTR));
        mBillIcon.setObjectName(QStringLiteral("mBillIcon"));
        mBillIcon.setGeometry(QRect(280, 70, 31, 31));
        mBillIcon.setStyleSheet(QStringLiteral("border-image: url(") + conf::getAssetPath().c_str() + QStringLiteral("bourse.png) no-repeat center"));
        mBillIcon.setText(QString());
        mBillSeparator.setObjectName(QStringLiteral("mBillSeparator"));
        mBillSeparator.setGeometry(QRect(0, 580, 351, 20));
        mBillSeparator.setFrameShape(QFrame::HLine);
        mBillSeparator.setFrameShadow(QFrame::Sunken);
        initCashButton();
        initChequeButton();
        initCardButton();
        mArticles.setObjectName(QStringLiteral("listWidget"));
        mArticles.setGeometry(QRect(20, 130, 311, 401));
        connect(&mArticles, SIGNAL(itemPressed(QListWidgetItem *)), this, SLOT(articleItemClicked(QListWidgetItem *)));
        conf::ConnexionsSettings::Instance().setConnexionsSettings(2, 30);
    }

    void    CashierScreen::initScanButton()
    {
        QPixmap pixmap(std::string(conf::getAssetPath() + "codebarre.png").c_str());
        QIcon   icon(pixmap);

        mScan.setObjectName(QStringLiteral("mScan"));
        mScan.setIcon(icon);
        mScan.setIconSize(QRect(10, 10, 171, 41).size());
        mScan.move(10, 5);
        connect(&mScan, SIGNAL(clicked()), this, SLOT(scanArticle()));
    }

    void    CashierScreen::initCancelButton()
    {
        QPixmap pixmap(std::string(conf::getAssetPath() + "poubelle.png").c_str());
        QIcon   icon(pixmap);

        mCancel.setObjectName(QStringLiteral("mCancel"));
        mCancel.setIcon(icon);
        mCancel.setIconSize(QRect(200, 10, 51, 41).size());
        mCancel.move(200, 5);
        connect(&mCancel, SIGNAL(clicked()), this, SLOT(cancelPayment()));
    }

    void    CashierScreen::initSettingButton()
    {
        QPixmap pixmap(std::string(conf::getAssetPath() + "settings.png").c_str());
        QIcon   icon(pixmap);

        mSetting.setObjectName(QStringLiteral("mSetting"));
        mSetting.setIcon(icon);
        mSetting.setIconSize(QRect(270, 10, 51, 41).size());
        mSetting.move(270, 5);
        connect(&mSetting, SIGNAL(clicked()), &mSettingDialog, SLOT(execSettingDialog()));
    }

    void    CashierScreen::initCashButton()
    {
        QPixmap pixmap(std::string(conf::getAssetPath() + "cash.png").c_str());
        QIcon   icon(pixmap);

        mCash.setObjectName(QStringLiteral("mCash"));
        mCash.setIcon(icon);
        mCash.setIconSize(QRect(10, 600, 91, 51).size());
        mCash.move(13, 600);
        connect(&mCash, SIGNAL(clicked()), this, SLOT(execCashDialog()));
    }

    void    CashierScreen::initChequeButton()
    {
        QPixmap pixmap(std::string(conf::getAssetPath() + "cheque.png").c_str());
        QIcon   icon(pixmap);

        mCheque.setObjectName(QStringLiteral("mCheque"));
        mCheque.setIcon(icon);
        mCheque.setIconSize(QRect(130, 600, 91, 51).size());
        mCheque.move(123, 600);
        connect(&mCheque, SIGNAL(clicked()), this, SLOT(execChequeDialog()));
    }

    void    CashierScreen::initCardButton()
    {
        QPixmap pixmap(std::string(conf::getAssetPath() + "card.png").c_str());
        QIcon   icon(pixmap);

        mCard.setObjectName(QStringLiteral("mCard"));
        mCard.setIcon(icon);
        mCard.setIconSize(QRect(250, 600, 91, 51).size());
        mCard.move(233, 600);
        connect(&mCard, SIGNAL(clicked()), this, SLOT(runPayment()));
        connect(&mCard, SIGNAL(clicked()), this, SLOT(rundialogPayment()));
    }

}
}
}
}
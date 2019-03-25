//!
//! @file SettingDialog.cpp
//! @author jbruel
//! @date 20/12/18
//!

#include <Tools/Log/Idx.hpp>
#include <plog/Severity.h>
#include <plog/Log.h>
#include <Conf/ConnexionsSettings.hpp>
#include "Windows/Cashier/Dialogs/SettingDialog.hpp"

namespace cash
{
namespace win
{
namespace cashier
{
namespace dialog
{

    SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent), mValidateButtons(this), mPaymentConnexionDelayText(this),
                                                    mMaximunConnexionAttempsText(this), mPaymentConnexionDelaySpinBox(this),
                                                    mMaximunConnexionAttempsSpinBox(this),
                                                    mDefaultMoneyDeviseText(this), mDefaultMoneyDevise(this)

    {
        setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        initWindow();
        initWidgets();
        QObject::connect(&mValidateButtons, SIGNAL(accepted()), this, SLOT(saveSettings()));
        QObject::connect(&mValidateButtons, SIGNAL(rejected()), this, SLOT(reject()));
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Cashier: Initialize settings dialog.";
        QMetaObject::connectSlotsByName(this);
    }

    void    SettingDialog::execSettingDialog()
    {
        conf::ConnexionsSettings    &connexionsSettings = conf::ConnexionsSettings::Instance();

        mMaximunConnexionAttempsSpinBox.setDisabled(false);
        mMaximunConnexionAttempsSpinBox.setValue(static_cast<int>(connexionsSettings.mAttempts));
        mPaymentConnexionDelaySpinBox.setValue(static_cast<int>(connexionsSettings.mDelay));
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Cashier: Launching settings dialog.";
        exec();
    }

    void    SettingDialog::saveSettings()
    {
        conf::ConnexionsSettings    &connexionsSettings = conf::ConnexionsSettings::Instance();

        connexionsSettings.mAttempts = static_cast<size_t>(mMaximunConnexionAttempsSpinBox.value());
        connexionsSettings.mDelay = static_cast<size_t>(mPaymentConnexionDelaySpinBox.value());
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Cashier: Save settings.";
        accept();
    }

    void    SettingDialog::initWindow()
    {
        if (objectName().isEmpty())
            setObjectName(QStringLiteral("Dialog"));
        setFixedSize(335, 184);
        setWindowTitle(QApplication::translate("Dialog", "Setting", Q_NULLPTR));
        setWindowModality(Qt::WindowModal);
    }

    void    SettingDialog::initWidgets()
    {
        mValidateButtons.setObjectName(QStringLiteral("mValidateButtons"));
        mValidateButtons.setGeometry(QRect(50, 140, 211, 32));
        mValidateButtons.setOrientation(Qt::Horizontal);
        mValidateButtons.setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        mPaymentConnexionDelayText.setObjectName(QStringLiteral("mPaymentConnexionDelayText"));
        mPaymentConnexionDelayText.setGeometry(QRect(10, 20, 181, 21));
        mPaymentConnexionDelayText.setText(QApplication::translate("Dialog", "Payment connexion delay", Q_NULLPTR));
        mMaximunConnexionAttempsText.setObjectName(QStringLiteral("mMaximunConnexionAttempsText"));
        mMaximunConnexionAttempsText.setGeometry(QRect(10, 60, 211, 21));
        mMaximunConnexionAttempsText.setText(QApplication::translate("Dialog", "Maximun connexion attempts", Q_NULLPTR));
        mPaymentConnexionDelaySpinBox.setObjectName(QStringLiteral("mPaymentConnexionDelaySpinBox"));
        mPaymentConnexionDelaySpinBox.setGeometry(QRect(277, 20, 51, 26));
        mPaymentConnexionDelaySpinBox.setMinimum(2);
        mPaymentConnexionDelaySpinBox.setMaximum(180);
        mMaximunConnexionAttempsSpinBox.setObjectName(QStringLiteral("mMaximunConnexionAttempsSpinBox"));
        mMaximunConnexionAttempsSpinBox.setGeometry(QRect(277, 60, 51, 26));
        mMaximunConnexionAttempsSpinBox.setMinimum(1);
        mMaximunConnexionAttempsSpinBox.setMaximum(99);
        mDefaultMoneyDeviseText.setObjectName(QStringLiteral("mDefaultMoneyDeviseText"));
        mDefaultMoneyDeviseText.setGeometry(QRect(10, 100, 201, 21));
        mDefaultMoneyDeviseText.setText(QApplication::translate("Dialog", "Default money devise", Q_NULLPTR));
        mDefaultMoneyDevise.setObjectName(QStringLiteral("mDefaultMoneyDevise"));
        mDefaultMoneyDevise.setGeometry(QRect(240, 100, 86, 25));
        mDefaultMoneyDevise.addItem("Card");
        mDefaultMoneyDevise.addItem("Cheque");
        mDefaultMoneyDevise.addItem("Cash");
    }

}
}
}
}
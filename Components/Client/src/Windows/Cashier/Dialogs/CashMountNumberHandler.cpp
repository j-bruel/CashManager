//!
//! @file CashMountNumberHandler.cpp
//! @author jbruel
//! @date 21/12/18
//!

#include "Windows/Cashier/Dialogs/CashMountNumberHandler.hpp"
#include <QtWidgets/QApplication>

namespace cash
{
namespace win
{
namespace cashier
{
namespace dialog
{

    CashMountNumberHandler::CashMountNumberHandler(QWidget *parent) :  QDialog(parent), mZeroButton(parent), mOneButton(parent), mTwoButton(parent),
                                                                       mThreeButton(parent), mFourButton(parent), mFiveButton(parent),
                                                                       mSixButton(parent), mSevenButton(parent), mEightButton(parent),
                                                                       mNineButton(parent), mSuppButton(parent), mCommaButton(parent)
    {
        initWidgets();
        QObject::connect(&mZeroButton, SIGNAL(clicked()), this, SLOT(accept()));
    }

    void    CashMountNumberHandler::initWidgets()
    {
        QFont   fontForNumbers;
        QFont   fontForSuppButton;
        QFont   fontForCommaButton;

        fontForNumbers.setPointSize(25);
        fontForSuppButton.setPointSize(15);
        fontForSuppButton.setBold(true);
        fontForSuppButton.setWeight(75);
        fontForCommaButton.setPointSize(25);
        fontForCommaButton.setBold(true);
        fontForCommaButton.setWeight(75);
        mZeroButton.setObjectName(QStringLiteral("mZeroButton"));
        mZeroButton.setGeometry(QRect(100, 350, 71, 61));
        mZeroButton.setFont(fontForNumbers);
        mZeroButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mZeroButton.setText(QApplication::translate("Dialog", "0", Q_NULLPTR));
        mOneButton.setObjectName(QStringLiteral("mOneButton"));
        mOneButton.setGeometry(QRect(10, 140, 71, 61));
        mOneButton.setFont(fontForNumbers);
        mOneButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mOneButton.setText(QApplication::translate("Dialog", "1", Q_NULLPTR));
        mTwoButton.setObjectName(QStringLiteral("mTwoButton"));
        mTwoButton.setGeometry(QRect(100, 140, 71, 61));
        mTwoButton.setFont(fontForNumbers);
        mTwoButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mTwoButton.setText(QApplication::translate("Dialog", "2", Q_NULLPTR));
        mThreeButton.setObjectName(QStringLiteral("mThreeButton"));
        mThreeButton.setGeometry(QRect(190, 140, 71, 61));
        mThreeButton.setText(QApplication::translate("Dialog", "3", Q_NULLPTR));
        mThreeButton.setFont(fontForNumbers);
        mThreeButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mFourButton.setObjectName(QStringLiteral("mFourButton"));
        mFourButton.setGeometry(QRect(10, 210, 71, 61));
        mFourButton.setFont(fontForNumbers);
        mFourButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mFourButton.setText(QApplication::translate("Dialog", "4", Q_NULLPTR));
        mFiveButton.setObjectName(QStringLiteral("mFiveButton"));
        mFiveButton.setGeometry(QRect(100, 210, 71, 61));
        mFiveButton.setFont(fontForNumbers);
        mFiveButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mFiveButton.setText(QApplication::translate("Dialog", "5", Q_NULLPTR));
        mSixButton.setObjectName(QStringLiteral("mSixButton"));
        mSixButton.setGeometry(QRect(190, 210, 71, 61));
        mSixButton.setFont(fontForNumbers);
        mSixButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mSixButton.setText(QApplication::translate("Dialog", "6", Q_NULLPTR));
        mSevenButton.setObjectName(QStringLiteral("mSevenButton"));
        mSevenButton.setGeometry(QRect(10, 280, 71, 61));
        mSevenButton.setFont(fontForNumbers);
        mSevenButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mSevenButton.setText(QApplication::translate("Dialog", "7", Q_NULLPTR));
        mEightButton.setObjectName(QStringLiteral("mEightButton"));
        mEightButton.setGeometry(QRect(100, 280, 71, 61));
        mEightButton.setFont(fontForNumbers);
        mEightButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mEightButton.setText(QApplication::translate("Dialog", "8", Q_NULLPTR));
        mNineButton.setObjectName(QStringLiteral("mNineButton"));
        mNineButton.setGeometry(QRect(190, 280, 71, 61));
        mNineButton.setFont(fontForNumbers);
        mNineButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mNineButton.setText(QApplication::translate("Dialog", "9", Q_NULLPTR));
        mSuppButton.setObjectName(QStringLiteral("mSuppButton"));
        mSuppButton.setGeometry(QRect(10, 350, 71, 61));
        mSuppButton.setFont(fontForSuppButton);
        mSuppButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mSuppButton.setText(QApplication::translate("Dialog", "SUPP", Q_NULLPTR));
        mCommaButton.setObjectName(QStringLiteral("mCommaButton"));
        mCommaButton.setGeometry(QRect(190, 350, 71, 61));
        mCommaButton.setFont(fontForCommaButton);
        mCommaButton.setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207)"));
        mCommaButton.setText(QApplication::translate("Dialog", ".", Q_NULLPTR));
    }

}
}
}
}
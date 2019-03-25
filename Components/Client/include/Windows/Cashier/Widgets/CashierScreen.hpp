//!
//! @file CashierScreen.hpp
//! @author jbruel
//! @date 05/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_CASHIER_WIDGETS_CASHIER_HPP
# define CASH_MANAGER_CLIENT_WINDOW_CASHIER_WIDGETS_CASHIER_HPP

# include "Tools/Subject.hpp"
# include "Core/PaymentOrder.hpp"
# include "Windows/Cashier/Dialogs/CreditCardDialog.hpp"
# include <QtCore/QVariant>
# include <QtWidgets/QAction>
# include <QtWidgets/QApplication>
# include <QtWidgets/QButtonGroup>
# include <QtWidgets/QFrame>
# include <QtWidgets/QHeaderView>
# include <QtWidgets/QLabel>
# include <QtWidgets/QListWidget>
# include <QtWidgets/QPushButton>
# include <QtWidgets/QToolButton>
# include <QtWidgets/QWidget>
#include <Core/ArticleGenerator.hpp>
# include "Windows/Cashier/Dialogs/SettingDialog.hpp"
# include "Windows/Cashier/Dialogs/CashPaymentDialog.hpp"
# include "Windows/Cashier/Dialogs/ChequePaymentDialog.hpp"

//!
//! @namespace cash
//!
namespace cash
{
//!
//! @namespace win
//!
namespace win
{
//!
//! @namespace cashier
//!
namespace cashier
{
//!
//! @namespace widget
//!
namespace widget
{

    //!
    //! @class CashierScreen
    //! @brief Cashier screen.
    //!
    class CashierScreen : public QWidget, public tool::Subject<double>, public tool::Subject<core::PaymentOrder>
    {
    public:
        Q_OBJECT

    private:
        QFrame      mOptionsSeparator; //!< Line for separate options.
        QPushButton mScan; //!< Button for scan a article.
        QPushButton mCancel; //!< Button for cancel a article
        QFrame      mBasketSeperator; //!< Line for basket separator.
        QLabel      mBasketImage; //!< Basket image.
        QLabel      mBill; //!< Bill.
        QPushButton mSetting; //!< Setting button.
        QFrame      mArticlesSeparator; //!< Line for article separator.
        QLabel      mSum; //!< Sum text.
        QPushButton      mBillIcon; //!< Bill icon.
        QFrame      mBillSeparator; //!< Line for bill separator.
        QToolButton mCash; //!< Cash button.
        QToolButton mCheque; //!< Cheque button.
        QToolButton mCard; //!< Card button.
        QListWidget mArticles; //!< List of articles scanned.

    private:
        double      mBillValue; //!< User bill.

    private:
        dialog::CreditCardDialog    mCreditCardPaymentDialog; //!< Dialog use for cashier payment informations.
        dialog::SettingDialog       mSettingDialog; //!< Dialog use for setting connexions.
        dialog::CashPaymentDialog   mCashPaymentDialog; //!< Dialog use for cash payment.
        dialog::ChequePaymentDialog mChequePaymentDialog; //!< Dialog use for cheque payment.

    private:
        core::ArticleGenerator    mArticleGenerator; //!< Article generator.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        CashierScreen() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit CashierScreen(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        CashierScreen(CashierScreen &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Bill copy.
        //! @warning Not available.
        //!
        CashierScreen    &operator=(const CashierScreen &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~CashierScreen() override = default;

    public:
        //!
        //! @brief Extract credit card dialog.
        //! @return Credit card dialog.
        //!
        inline dialog::CreditCardDialog    &getCreditCardDialog() { return (mCreditCardPaymentDialog); }

    public slots:
        //!
        //! @todo Scan a article.
        //!
        void    scanArticle();
        //!
        //! @todo REMOVE THIS FUNCTION, FOR DEBUG ONLY.
        //!
        void    runPayment();
        //!
        //! @brief Run payment dialog.
        //!
        void    rundialogPayment();

    private slots:
        //!
        //! @brief Launch cash dialog.
        //!
        void    execCashDialog();
        //!
        //! @brief Launch cheque dialog.
        //!
        void    execChequeDialog();
        //!
        //! @brief Cancel order.
        //!
        void    cancelPayment();
        //!
        //! @brief Article item clicked.
        //!
        void    articleItemClicked(QListWidgetItem *item);

    private:
        //!
        //! @brief Launch a update bill screen order.
        //!
        void    updateBillScreen();

    private:
        //!
        //! @brief Init window information.
        //! @param parent Parent screen.
        //!
        void    initWindow(QWidget *parent);
        //!
        //! @brief Initialize all widgets.
        //!
        void    initWidgets();

    private:
        //!
        //! @brief Initialize scan button.
        //!
        void    initScanButton();
        //!
        //! @brief Initialize setting button.
        //!
        void    initSettingButton();
        //!
        //! @brief Initialize cancel button.
        //!
        void    initCancelButton();
        //!
        //! @brief Initialize cash button.
        //!
        void    initCashButton();
        //!
        //! @brief Initialize cheque button.
        //!
        void    initChequeButton();
        //!
        //! @brief Initialize card button.
        //!
        void    initCardButton();
    };

}
}
}
}

#endif // CASH_MANAGER_CLIENT_WINDOW_CASHIER_WIDGETS_CASHIER_HPP

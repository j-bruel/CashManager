//!
//! @file CashPaymentDialog.hpp
//! @author jbruel
//! @date 18/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_CASHIER_DIALOGS_CASHPAYMENTDIALOG_HPP
# define CASH_MANAGER_CLIENT_WINDOW_CASHIER_DIALOGS_CASHPAYMENTDIALOG_HPP

# include <QtCore/QVariant>
# include <QtWidgets/QAction>
# include <QtWidgets/QApplication>
# include <QtWidgets/QButtonGroup>
# include <QtWidgets/QDialog>
# include <QtWidgets/QDialogButtonBox>
# include <QtWidgets/QHeaderView>
# include <QtWidgets/QLCDNumber>
# include <QtWidgets/QPushButton>
# include <QKeyEvent>
# include "Windows/Cashier/Dialogs/CashMountNumberHandler.hpp"

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
//! @namespace dialog
//!
namespace dialog
{
    //!
    //! @class CashPaymentDialog
    //! @brief Cash payment dialog.
    //!
    class CashPaymentDialog : public QDialog
    {
    public:
        Q_OBJECT

    public:
        QLCDNumber              mBill; //!< User bill.
        QLCDNumber              mUserCash; //!< User cash value.
        QLCDNumber              mUserRefound; //!< User refound.
        CashMountNumberHandler  mMountNumber; //!< Mount Numbers.
        QPushButton             mCashInPayment; //!< Button to open the money (cashier).
        QDialogButtonBox        mValidatePayment; //!< Validate payment.

    private:
        double      mBillValue; //!< User bill.
        std::string mBillString; //!< Cash give by the user.

    private:
        bool        mPaymentValidate; //!< Allow to know if payment is validate.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        CashPaymentDialog() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit CashPaymentDialog(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        CashPaymentDialog(CashPaymentDialog &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Dialog copy.
        //! @warning Not available.
        //!
        CashPaymentDialog &operator=(const CashPaymentDialog &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~CashPaymentDialog() override = default;

    public:
        //!
        //! @brief Initialize bill.
        //! @param bill Bill.
        //!
        inline void setBill(double bill) { mBillValue = bill; }

    public:
        //!
        //! @brief Launch cash dialog.
        //! @return Status.
        //!
        bool    execCashDialog();
        //!
        //! @brief When key are press overload.
        //! @param e Key.
        //!
        void    keyPressEvent(QKeyEvent *e) override;

    private slots:
        //!
        //! @brief Enter pin "1".
        //!
        void    enterPinOne();
        //!
        //! @brief Enter pin "2".
        //!
        void    enterPinTwo();
        //!
        //! @brief Enter pin "3".
        //!
        void    enterPinThree();
        //!
        //! @brief Enter pin "4".
        //!
        void    enterPinFour();
        //!
        //! @brief Enter pin "5".
        //!
        void    enterPinFive();
        //!
        //! @brief Enter pin "6".
        //!
        void    enterPinSix();
        //!
        //! @brief Enter pin "7".
        //!
        void    enterPinSeven();
        //!
        //! @brief Enter pin "8".
        //!
        void    enterPinHeight();
        //!
        //! @brief Enter pin "9".
        //!
        void    enterPinNine();
        //!
        //! @brief Enter pin "0".
        //!
        void    enterPinZero();
        //!
        //! @brief Enter pin ",".
        //!
        void    enterComma();
        //!
        //! @brief Enter supp.
        //!
        void    enterSupp();

    private slots:
        //!
        //! @brief Callback use for valide payment.
        //!
        void    validePayment();
        //!
        //! @brief Payment cash in.
        //!
        void    cashIn();

    private:
        //!
        //! @brief Initialize windows parameters.
        //!
        void initWindow();
        //!
        /// @brief Initialize all widgets.
        //!
        void initWidgets();
    };

}
}
}
}

#endif // CASH_MANAGER_CLIENT_WINDOW_CASHIER_DIALOGS_CASHPAYMENTDIALOG_HPP

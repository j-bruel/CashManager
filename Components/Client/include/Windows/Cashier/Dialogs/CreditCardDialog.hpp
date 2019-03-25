//!
//! @file CreditCardDialog.hpp
//! @author jbruel
//! @date 18/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_PAYMENTTERMINAL_DIALOGS_CREDITCARDDIALOG_HPP
# define CASH_MANAGER_CLIENT_WINDOW_PAYMENTTERMINAL_DIALOGS_CREDITCARDDIALOG_HPP

# include "Windows/PaymentTerminal/Widgets/CodePinHandler.hpp"
# include "Core/PaymentStatus.hpp"
# include "Tools/Observer.hpp"
# include <QtCore/QVariant>
# include <QtWidgets/QAction>
# include <QtWidgets/QApplication>
# include <QtWidgets/QButtonGroup>
# include <QtWidgets/QDialog>
# include <QtWidgets/QDialogButtonBox>
# include <QtWidgets/QHeaderView>
# include <QtWidgets/QLabel>
# include <QtWidgets/QProgressBar>

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
    //! @class CreditCardDialog
    //! @brief Credit card dialog.
    //!
    class CreditCardDialog : public QDialog, public tool::Observer<core::PaymentUpdate>
    {
    public:
        Q_OBJECT

    private:
        //!
        //! @var const std::map<core::PaymentStatus, int>    mPaymentStateMachine
        //! @brief Relation between payment status and %.
        //!
        const std::map<core::PaymentStatus, int>    mPaymentStateMachine = {
                { core::PaymentStatus::PAYMENT_TYPE_CONNECTION_WAITING, 10},
                { core::PaymentStatus::PAYMENT_TYPE_CONNECTION_DONE, 10},
                { core::PaymentStatus::PAYMENT_TYPE_CONNECTION_FAIL, 100},
                { core::PaymentStatus::CREDIT_CARD_INSERT, 20 },
                { core::PaymentStatus::CREDIT_CARD_TAKE_OFF, 90},
                { core::PaymentStatus::CREDIT_CARD_RIPPED_OFF, 100},
                { core::PaymentStatus::PAYMENT_SERVER_CONNECTION_WAITING, 30},
                { core::PaymentStatus::PAYMENT_SERVER_CONNECTION_DONE, 40},
                { core::PaymentStatus::PAYMENT_SERVER_CONNECTION_FAIL, 100},
                { core::PaymentStatus::PAYMENT_SERVER_CONNECTION_RETRY, 30},
                { core::PaymentStatus::MPT_WAITING_CODE, 40},
                { core::PaymentStatus::MPT_ENTER_CODE, 40},
                { core::PaymentStatus::MPT_CANCEL_PAYMENT, 80},
                { core::PaymentStatus::MPT_REMOVE_CODE, 40},
                { core::PaymentStatus::MPT_VALID_CODE, 50},
                { core::PaymentStatus::PAYMENT_SERVER_CHECK_CODE_WAITING, 60},
                { core::PaymentStatus::PAYMENT_SERVER_CHECK_CODE_DONE, 70},
                { core::PaymentStatus::PAYMENT_SERVER_CHECK_CODE_FAIL, 100},
                { core::PaymentStatus::PAYMENT_SERVER_AUTH_PENDING, 80},
                { core::PaymentStatus::PAYMENT_SERVER_AUTH_DONE, 90},
                { core::PaymentStatus::PAYMENT_SERVER_AUTH_FAIL, 100},
                { core::PaymentStatus::PAYMENT_REFUSE, 100},
                { core::PaymentStatus::PAYMENT_VALID, 90},
                { core::PaymentStatus::PAYMENT_BANK_REFUSE, 80},
                { core::PaymentStatus::USER_MUST_REMOVE_CREDIT_CARD, 90},
                { core::PaymentStatus::PROCESS_PAYMENT_FINISH,100 }
        };

    private:
        QDialogButtonBox    mValidateDialogButtons; //!< Validator dialog buttons.
        QLabel              mPaymentStatus; //!< Payment status.
        QProgressBar        mPaymentProgress; //!< Payment status.
        QLabel              mBill; //!< Display bill.

    private:
        double              mBillValue; //!< Bill value.
        QPalette            mPaymentProgressPalette; //!< Payment palette (for color).
        bool                mLastPaymentStatus; //!< Last payment status.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        CreditCardDialog() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit CreditCardDialog(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        CreditCardDialog(CreditCardDialog &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Dialog copy.
        //! @warning Not available.
        //!
        CreditCardDialog    &operator=(const CreditCardDialog &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~CreditCardDialog() override = default;

    public:
        //!
        //! @brief Update bill value.
        //! @param bill Bill.
        //!
        inline void setBill(double bill) { mBillValue = bill; }

    public:
        //!
        //! @brief Running slot.
        //! @return Payment status.
        //!
        bool    execDialog();

    public:
        //!
        //! @brief When key are press overload.
        //! @param e Key.
        //!
        void    keyPressEvent(QKeyEvent *e) override;

    public:
        //!
        //! @brief Callback use when new information are received from mpt.
        //! @brief Callback for state machine.
        //! @return state.
        //!
        bool    update(std::shared_ptr<core::PaymentUpdate> &);

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

#endif // CASH_MANAGER_CLIENT_WINDOW_PAYMENTTERMINAL_DIALOGS_CREDITCARDDIALOG_HPP

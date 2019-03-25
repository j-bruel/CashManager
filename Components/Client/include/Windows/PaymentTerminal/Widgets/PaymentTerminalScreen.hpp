//!
//! @file PaymentTerminalScreen.hpp
//! @authors jbruel qt
//! @date 10/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_WIDGETS_PAYMENT_TERMINAL_SCREEN_HPP
# define CASH_MANAGER_CLIENT_WINDOW_WIDGETS_PAYMENT_TERMINAL_SCREEN_HPP

# include <QtCore/QVariant>
# include <QtWidgets/QAction>
# include <QtWidgets/QApplication>
# include <QtWidgets/QButtonGroup>
# include <QtWidgets/QFrame>
# include <QtWidgets/QHeaderView>
# include <QtWidgets/QLabel>
# include <QtWidgets/QPushButton>
# include <QtWidgets/QWidget>
# include <QtWidgets/QToolButton>
#include <Network/BankAPI.hpp>
#include <Conf/ConnexionsSettings.hpp>
# include "Windows/PaymentTerminal/Widgets/CodePinHandler.hpp"
# include "Windows/PaymentTerminal/Widgets/ContactLess.hpp"

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
//! @namespace term
//!
namespace term
{
//!
//! @namespace widget
//!
namespace widget
{

    //!
    //! @class PaymentTerminalScreen
    //! @brief Payment terminal screen.
    //!
    class   PaymentTerminalScreen : public QWidget
    {
    public:
        Q_OBJECT

    private:
        QFrame      mLine; //!< Separation line for clean ui.
        QFrame      mScreenUserInformation; //!< All payment information.
        QLabel      mPaymentDescription; //!< Payment description (states).
        QLabel      mBill; //!< Payment bill.
        double      mBillValue; //!< Bill value.
        ContactLess mContactLessLogo; //!< Contact less payment logo.
        QToolButton mInsertCard; //!< Insert card zone.

    private:
        CodePinHandler  mCodes;

    private:
        bool    mPaymentProcessRunning; //!< Tell if a payment process is currently running.
        bool    mCardInsert; //!< Tell if the user credit card is insert.
        bool    mBankFinishPayment; //!< Tell if bank finish the payment.
        bool    mCardRipped; //!< Allow to know if the card was ripped off.

    private:
        QMetaObject::Connection mContactLessConnect; //!< Connection for contact less logo.

    private:
        conf::ConnexionsSettings    &mSettings; //!< Connexions settings.
        network::BankAPI            mBank; //!< Bank API.
        std::string                 mBankToken; //!< Bank payement token.
        std::string                 mLastCardNumber; //!< Last card number.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        PaymentTerminalScreen() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit PaymentTerminalScreen(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        PaymentTerminalScreen(PaymentTerminalScreen &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Payment terminal copy.
        //! @warning Not available.
        //!
        PaymentTerminalScreen    &operator=(const PaymentTerminalScreen &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~PaymentTerminalScreen() override = default;

    public:
        //!
        //! @brief Attach credit card dialog.
        //! @param creditCardDialog Credit card dialog.
        //!
        inline void    attachCreditCardDialog(cashier::dialog::CreditCardDialog *creditCardDialog) { mCodes.attach(creditCardDialog); }

    public:
        //!
        //! @brief Launch payment process.
        //! @param bill Bill.
        //! @return Status.
        //!
        bool    payment(double bill);

    public slots:
        //!
        //! @brief Callback when user finish valid his pin code.
        //!
        void    validPinCode();
        //!
        //! @brief Callback when user cancel his pin code.
        //!
        void    cancelPinEnter();

    private slots:
        //!
        //! @brief Callback when credit card is insert.
        //!
        void    insertCreditCard();
        //!
        //! @brief Contact less payment.
        //!
        void    contactLessPayment();

    private:
        //!
        //! @brief Initialize parent window.
        //! @param parent Parent widget.
        //!
        void    initParentWindow(QWidget *parent);
        //!
        //! @brief Initialize screen user information.
        //!
        void    initScreenUserInformationPayment();

    private:
        //!
        //! @brief Initialize payment process.
        //!
        void    startPaymentProcess();
        //!
        //! @brief Finish payment process.
        //!
        void    finishPaymentProcess();
        //!
        //! @brief Update layout for bill the client.
        //!
        void    setBillPayment(double bill);
        //!
        //! @brief Allow user code pin.
        //!
        void    allowUserCodePin();
        //!
        //! @brief Connect the mobile payment terminal to the payment server.
        //! @param paymentType Payment type.
        //! @return State.
        //!
        bool    connectPaymentServer(const std::string &paymentType);
        //!
        //! @brief Callback if server connexion failed.
        //!
        void    serverConnectFail();
        //!
        //! @brief Callback if server refuse payment.
        //!
        void    bankRefusePayment();

    private:
        //!
        //! @brief Generate card number.
        //! @return Card number.
        //!
        std::string generateCardNumber() const;
        //!
        //! @brief Generate a random number.
        //! @param max Max generated number.
        //! @return Random generated number.
        //!
        size_t  generateRandomNumber(size_t max) const;
    };

}
}
}
}

#endif //CASH_MANAGER_CLIENT_WINDOW_WIDGETS_PAYMENT_TERMINAL_SCREEN_HPP

//!
//! @file PaymentTerminal.hpp
//! @author jbruel
//! @date 05/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_PAYMENT_TERMINAL_HPP
# define CASH_MANAGER_CLIENT_WINDOW_PAYMENT_TERMINAL_HPP

# include "Tools/Subject.hpp"
# include "Core/PaymentOrder.hpp"
# include "Windows/PaymentTerminal/Widgets/PaymentTerminalScreen.hpp"
# include <QtWidgets/QWidget>
# include <QtWidgets/QDialog>

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
    //! @class PaymentTerminal
    //! @brief Payment Terminal windows.
    //!
    class   PaymentTerminal : public QWidget, public tool::Observer<core::PaymentOrder>
    {
    private:
        QWidget mPaymentTerminalWindow; //!< Cashier main window.

    private:
        term::widget::PaymentTerminalScreen mTerminal; //!< Payment terminal screen attach to the main window.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        PaymentTerminal() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit PaymentTerminal(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        PaymentTerminal(PaymentTerminal &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Payment terminal copy.
        //! @warning Not available.
        //!
        PaymentTerminal    &operator=(const PaymentTerminal &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~PaymentTerminal() override = default;

    public:
        //!
        //! @brief Attach credit card dialog.
        //! @param creditCardDialog Credit card dialog.
        //!
        inline void    attachCreditCardDialog(cashier::dialog::CreditCardDialog *creditCardDialog) { mTerminal.attachCreditCardDialog(creditCardDialog); }

    public Q_SLOTS:
        //!
        //! @brief Overload of show window function.
        //!
        inline virtual void show() { mPaymentTerminalWindow.show(); }

    public:
        //!
        //! @brief Callback use from cashier to alert the terminal of payment.
        //! @param subject Bill.
        //! @return State.
        //!
        bool    update(std::shared_ptr<core::PaymentOrder> &subject);

    private:
        //!
        //! @brief Initialize cashier window.
        //!
        void    initScreen();
    };

}
}

#endif //CASH_MANAGER_CLIENT_WINDOW_PAYMENT_TERMINAL_HPP

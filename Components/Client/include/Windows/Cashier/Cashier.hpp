//!
//! @file Bill.hpp
//! @author jbruel
//! @date 05/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_CASHIER_HPP
# define CASH_MANAGER_CLIENT_WINDOW_CASHIER_HPP

# include "Windows/Cashier/Widgets/CashierScreen.hpp"
# include <QtWidgets/QWidget>
# include <QtWidgets/QPushButton>
# include <QtWidgets/QShortcut>
# include <QtWidgets/QApplication>
# include <QtGui/QCloseEvent>
# include <Windows/Bill/Bill.hpp>
# include <Windows/PaymentTerminal/PaymentTerminal.hpp>

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
    //! @class Cashier
    //! @brief Cashier windows.
    //!
    class   Cashier : public QWidget
    {
    public:
        Q_OBJECT

    private:
        QWidget     mCashierWindow; //!< Cashier main window.
        QShortcut   mEscape; //!< Escape short cut.

    private:
        cashier::widget::CashierScreen  mCashierScreen; //!< Cashier screen.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        Cashier() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit Cashier(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        Cashier(Cashier &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Bill copy.
        //! @warning Not available.
        //!
        Cashier    &operator=(const Cashier &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~Cashier() override = default;

    public:
        //!
        //! @brief Attach subjects.
        //! @param bill Bill screen.
        //! @param cashier Cashier screen.
        //!
        void    attachSubjets(win::Bill *bill, win::PaymentTerminal *cashier);

    public:
        //!
        //! @brief Extract cashier screen instance.
        //! @return Cashier screen.
        //!
        inline cashier::widget::CashierScreen  &getCashierScreenInstance() { return (mCashierScreen); }

    public Q_SLOTS:
        //!
        //! @brief Overload of show window function.
        //!
        inline virtual void show() { mCashierWindow.show(); }

    private slots:
        //!
        //! @brief Quit application.
        //!
        void    quitApplication();

    private:
        //!
        //! @brief Initialize cashier window.
        //!
        void    initScreen();
        //!
        //! @brief initialize escape handling.
        //!
        void    initEscapeHandling();
    };

}
}

#endif //CASH_MANAGER_CLIENT_WINDOW_CASHIER_HPP

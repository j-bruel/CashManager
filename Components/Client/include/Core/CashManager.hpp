//!
//! @file CashManager.hpp
//! @author jbruel
//! @date 06/12/18
//!

#ifndef CASH_MANAGER_CLIENT_CORE_CASHMANAGER_HPP
# define CASH_MANAGER_CLIENT_CORE_CASHMANAGER_HPP

# include "Windows/Bill/Bill.hpp"
# include "Windows/Cashier/Cashier.hpp"
# include "Windows/PaymentTerminal/PaymentTerminal.hpp"
# include <string>

//!
//! @namespace cash
//!
namespace cash
{
//!
//! @namespace cash
//!
namespace core
{

    //!
    //! @class CashManager
    //! @brief Cash manager.
    //!
    class   CashManager
    {
    private:
        win::Bill               mBill; //!< Bill screen.
        win::Cashier            mCashier; //!< Cashier screen.
        win::PaymentTerminal    mPaymentTerminal; //!< Payment terminal screen.

    public:
        //!
        //! @brief Constructor.
        //!
        CashManager() : mBill(nullptr), mCashier(nullptr), mPaymentTerminal(nullptr) { }
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        CashManager(const CashManager &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Bill copy.
        //! @warning Not available.
        //!
        CashManager &operator=(const CashManager &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~CashManager() = default;

    public:
        //!
        //! @brief Initialize cash manager.
        //!
        void init();
        //!
        //! @brief Run main application.
        //!
        void run();
    };

}
}

#endif //CASH_MANAGER_CLIENT_CORE_CASHMANAGER_HPP

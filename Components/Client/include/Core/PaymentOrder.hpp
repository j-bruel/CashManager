//!
//! @file PaymentOrder.hpp
//! @author jbruel
//! @date 15/12/18
//!

#ifndef CASH_MANAGER_CLIENT_PAYMENTORDER_HPP
# define CASH_MANAGER_CLIENT_PAYMENTORDER_HPP

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
    //! @enum PaymentType
    //! @brief Payment type.
    //!
    enum    PaymentType
    {
        CARD,
        CHEQUE,
        CASH,
        NONE
    };

    //!
    //! @struct PaymentOrder
    //! @brief Payment order.
    //!
    struct  PaymentOrder
    {
        double      mBill; //!< User bill.
        PaymentType mType; //!< Payment type.


        //!
        //! @brief Constructor.
        //! @param bill User bill.
        //! @param type Payment type.
        //!
        PaymentOrder(double bill, PaymentType type)
        {
            mBill = bill;
            mType = type;
        }

        //!
        //! @brief Helper to set all variable at once.
        //! @param bill User bill.
        //! @param type Payment type.
        //!
        void setOrder(double bill, PaymentType type)
        {
            mBill = bill;
            mType = type;
        }
    };

}
}

#endif //CASH_MANAGER_CLIENT_PAYMENTORDER_HPP

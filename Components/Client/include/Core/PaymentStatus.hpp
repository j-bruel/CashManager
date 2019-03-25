//!
//! @file PaymentStatus.hpp
//! @author jbruel
//! @date 19/12/18
//!

#ifndef CASH_MANAGER_CLIENT_CORE_PAYMENTSTATUS_HPP
# define CASH_MANAGER_CLIENT_CORE_PAYMENTSTATUS_HPP

//!
//! @namespace cash
//!
namespace cash
{
//!
//! @namespace core
//!
namespace core
{

    //!
    //! @enum PaymentStatus
    //! @brief Payment status.
    //!
    enum    PaymentStatus
    {
        PAYMENT_TYPE_CONNECTION_WAITING,
        PAYMENT_TYPE_CONNECTION_DONE,
        PAYMENT_TYPE_CONNECTION_FAIL,
        CREDIT_CARD_INSERT,
        CREDIT_CARD_TAKE_OFF,
        CREDIT_CARD_RIPPED_OFF,
        PAYMENT_SERVER_CONNECTION_WAITING,
        PAYMENT_SERVER_CONNECTION_DONE,
        PAYMENT_SERVER_CONNECTION_FAIL,
        PAYMENT_SERVER_CONNECTION_RETRY,
        MPT_WAITING_CODE,
        MPT_ENTER_CODE,
        MPT_CANCEL_PAYMENT,
        MPT_REMOVE_CODE,
        MPT_VALID_CODE,
        PAYMENT_SERVER_CHECK_CODE_WAITING,
        PAYMENT_SERVER_CHECK_CODE_DONE,
        PAYMENT_SERVER_CHECK_CODE_FAIL,
        PAYMENT_SERVER_AUTH_PENDING,
        PAYMENT_SERVER_AUTH_DONE,
        PAYMENT_SERVER_AUTH_FAIL,
        PAYMENT_REFUSE,
        PAYMENT_VALID,
        PAYMENT_BANK_REFUSE,
        USER_MUST_REMOVE_CREDIT_CARD,
        PROCESS_PAYMENT_FINISH
    };

    //!
    //! @struct PaymentOrder
    //! @brief Payment order.
    //!
    struct  PaymentUpdate
    {
        PaymentStatus   mStatus; //!< Payment status.
        std::string     mMsg; //!< Special message.


        //!
        //! @brief Constructor.
        //! @param status Payment status.
        //! @param msg Special message.
        //!
        PaymentUpdate(PaymentStatus status, const std::string &msg)
        {
            mStatus = status;
            mMsg = msg;
        }

        //!
        //! @brief Helper to set all variable at once.
        //! @param status Payment status.
        //! @param msg Special message.
        //!
        void setOrder(PaymentStatus status, const std::string &msg)
        {
            mStatus = status;
            mMsg = msg;
        }
    };

}
}


#endif //CASH_MANAGER_CLIENT_CORE_PAYMENTSTATUS_HPP

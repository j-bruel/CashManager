//!
//! @file CashMountNumberHandler.hpp
//! @author jbruel
//! @date 21/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOWS_CASHIER_DIALOGS_CASHMOUNTNUMBERHANDLER_HPP
# define CASH_MANAGER_CLIENT_WINDOWS_CASHIER_DIALOGS_CASHMOUNTNUMBERHANDLER_HPP

# include <QtWidgets/QWidget>
# include <QtWidgets/QPushButton>
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
//! @namespace cashier
//!
namespace cashier
{
//!
//! @namespace dialog
//!
namespace dialog
{

    class   CashMountNumberHandler : public QDialog
    {
    public:
        QPushButton         mZeroButton; //!< Button for "0".
        QPushButton         mOneButton; //!< Button for "1".
        QPushButton         mTwoButton; //!< Button for "2".
        QPushButton         mThreeButton; //!< Button for "3".
        QPushButton         mFourButton; //!< Button for "4".
        QPushButton         mFiveButton; //!< Button for "5".
        QPushButton         mSixButton; //!< Button for "6".
        QPushButton         mSevenButton; //!< Button for "7".
        QPushButton         mEightButton; //!< Button for "8".
        QPushButton         mNineButton; //!< Button for "9".
        QPushButton         mSuppButton; //!< Button for supp the cashier bill.
        QPushButton         mCommaButton; //!< Button for ",".

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        CashMountNumberHandler() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit CashMountNumberHandler(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        CashMountNumberHandler(CashMountNumberHandler &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Dialog copy.
        //! @warning Not available.
        //!
        CashMountNumberHandler &operator=(const CashMountNumberHandler &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~CashMountNumberHandler() = default;

    private:
        //!
        /// @brief Initialize all widgets.
        //!
        void    initWidgets();
    };

}
}
}
}

#endif //CASH_MANAGER_CLIENT_WINDOWS_CASHIER_DIALOGS_CASHMOUNTNUMBERHANDLER_HPP

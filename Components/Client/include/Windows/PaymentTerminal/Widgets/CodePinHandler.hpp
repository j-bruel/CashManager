//!
//! @file CodePinHandler.hpp
//! @author jbruel
//! @date 16/12/18
//!

#ifndef CASH_MANAGER_CLIENT_CODEPINHANDLER_HPP
# define CASH_MANAGER_CLIENT_CODEPINHANDLER_HPP

# include "Tools/Subject.hpp"
# include "Windows/Cashier/Dialogs/CreditCardDialog.hpp"
# include "Core/PaymentStatus.hpp"
# include <QtWidgets/QPushButton>
# include <QtWidgets/QLabel>

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

    class PaymentTerminalScreen;

    //!
    //! @class CodePinHandler
    //! @brief User pin code handler.
    //!
    class CodePinHandler : public QWidget, public tool::Subject<core::PaymentUpdate>
    {
    public:
        Q_OBJECT

    private:
        std::string mPinCode; //!< User pin code.

    private:
        QPushButton mOneButton; //!< Button "1".
        QPushButton mTwoButton; //!< Button "2".
        QPushButton mThreeButton; //!< Button "3".
        QPushButton mFourButton; //!< Button "4".
        QPushButton mFiveButton; //!< Button "5".
        QPushButton mSixButton; //!< Button 6".
        QPushButton mSevenButton; //!< Button "7".
        QPushButton mEightButton; //!< Button "8".
        QPushButton mNineButton; //!< Button "9".
        QPushButton mUnUseButton; //!< Button "10".
        QPushButton mUnUseButton2; //!< Button "11".
        QPushButton mZeroButton; //!< Button "12".
        QPushButton mCancelButton; //!< Button cancel.
        QPushButton mValidateButton; //!< Button validate.
        QPushButton mCorrectButton; //!< Button correct.

    private:
        PaymentTerminalScreen   *mPaymentTerminal; //!< MPT.
        QLabel                  *mPinLabel; //!< Pin screen output label.

    private:
        QMetaObject::Connection mOneConnect; //!< Connection for button "1".
        QMetaObject::Connection mTwoConnect; //!< Connection for button "2".
        QMetaObject::Connection mThreeConnect; //!< Connection for button "3".
        QMetaObject::Connection mFourConnect; //!< Connection for button "4".
        QMetaObject::Connection mFiveConnect; //!< Connection for button "5".
        QMetaObject::Connection mSixConnect; //!< Connection for button "6".
        QMetaObject::Connection mSevenConnect; //!< Connection for button "7".
        QMetaObject::Connection mHeightConnect; //!< Connection for button "8".
        QMetaObject::Connection mNineConnect; //!< Connection for button "9".
        QMetaObject::Connection mZeroConnect; //!< Connection for button "0".
        QMetaObject::Connection mCorrectConnect; //!< Connection for correct button.
        QMetaObject::Connection mValidateConnect; //!< Connection for validate button.
        QMetaObject::Connection mCancelConnect; //!< Connection for cancel button.

    private:
        bool    mPinsAlreadyConnect;

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        CodePinHandler() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //! @param pinLabel Pin label.
        //! @param mpt Mobile payment terminal.
        //!
        explicit CodePinHandler(QWidget *parent, QLabel *pinLabel, PaymentTerminalScreen *mpt);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        CodePinHandler(CodePinHandler &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Payment terminal copy.
        //! @warning Not available.
        //!
        CodePinHandler    &operator=(const CodePinHandler &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~CodePinHandler() override = default;

    public:
        //!
        //! @brief Set all numbers (for pin code) connexions.
        //!
        void    connectPins();
        //!
        //! @brief Set cancel connexion.
        //!
        void    connectCancel();
        //!
        //! @brief Unset all numbers (for pin code) connexions.
        //!
        void    disconnectPins();

    public:
        //!
        //! @brief Extract user pin code.
        //! @return User pin code.
        //!
        inline const std::string    &getUserPinCode() const { return (mPinCode); }

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

    public slots:
        //!
        //! @brief Enter pin "0".
        //!
        void    correctPin();

    public:
        //!
        //! @brief Notify cashier for a update.
        //! @param status Payment status.
        //! @param msg Payment message.
        //!
        void    notifyCashierUpdate(core::PaymentStatus status, const std::string &msg);

    private:
        //!
        //! @brief Initialize all buttons.
        //!
        void    initButtons();
        //!
        //! @brief Print in the screen pins enter by the user with '*'.
        //!
        void    setPinLabel();

    };

}
}
}
}

#endif //CASH_MANAGER_CLIENT_CODEPINHANDLER_HPP

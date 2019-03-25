//!
//! @file ChequePaymentDialog.hpp
//! @author jbruel
//! @date 18/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_CASHIER_DIALOGS_CHEQUEPAYMENTDIALOG_HPP
# define CASH_MANAGER_CLIENT_WINDOW_CASHIER_DIALOGS_CHEQUEPAYMENTDIALOG_HPP

# include "Core/ChequeInformationGenerator.hpp"
# include <QtCore/QVariant>
# include <QtWidgets/QAction>
# include <QtWidgets/QApplication>
# include <QtWidgets/QButtonGroup>
# include <QtWidgets/QDialog>
# include <QtWidgets/QDialogButtonBox>
# include <QtWidgets/QHeaderView>
# include <QtWidgets/QLabel>
# include <QtWidgets/QProgressBar>
#include <Network/BankAPI.hpp>
#include <Conf/ConnexionsSettings.hpp>

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
    //! @class ChequePaymentDialog
    //! @brief Dialog use for cheque payment.
    //!
    class ChequePaymentDialog : public QDialog
    {
    public:
        Q_OBJECT

    public:
        QDialogButtonBox    mValidatePayment; //!< Validate payment buttons.
        QLabel              mChequeImage; //!< Cheque image.
        QProgressBar        mPaymentProgess; //!< Payment prgress.
        QLabel              mPaymentStatus; //!< Payment status.
        QLabel              mAmountText; //!< Amount text.
        QLabel              mAmonutValue; //!< Amount value.
        QLabel              mDateText; //!< Date text.
        QLabel              mDateValue; //!< Date value.
        QLabel              mFromText; //!< From text.
        QLabel              mFromValue; //!< From value.
        QLabel              mToText; //!< To text.
        QLabel              mToValue; //!< To value.
        QLabel              mWhereText; //!< Where text.
        QLabel              mWhereValue; //!< Where value.
        QLabel              mNumberText; //!< Number cheque text.
        QLabel              mNumberValue; //!< Number cheque value.

    private:
        QPalette    mPaymentProgressPalette; //!< Payment palette (for color).

    private:
        double  mBillValue; //!< User bill.

    private:
        bool    mPaymentValidate; //!< Allow to know if payment is validate.
        bool    mChequeChecked; //!< Tell if the cheque has been check.

    private:
        core::ChequeInfoGenerator   mChequeInfoGenerator; //!< Cheque information generator.

    private:
        conf::ConnexionsSettings    &mSettings; //!< Connexions settings.
        network::BankAPI            mBank; //!< Bank API.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        ChequePaymentDialog() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit ChequePaymentDialog(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        ChequePaymentDialog(ChequePaymentDialog &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Dialog copy.
        //! @warning Not available.
        //!
        ChequePaymentDialog &operator=(const ChequePaymentDialog &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~ChequePaymentDialog() override = default;

    public:
        //!
        //! @brief Initialize bill.
        //! @param bill Bill.
        //!
        inline void setBill(double bill) { mBillValue = bill; }

    public:
        //!
        //! @brief Launch cheque dialog.
        //! @return Status.
        //!
        bool    execChequeDialog();
        //!
        //! @brief When key are press overload.
        //! @param e Key.
        //!
        void    keyPressEvent(QKeyEvent *e) override;

    private slots:
        //!
        //! @brief Callback use for valide payment.
        //!
        void    validePayment();

    private:
        //!
        //! @brief Server connexion.
        //! @param bankToken Bank token.
        //! @return Server status.
        //!
        bool    serverConnexion(std::string &bankToken);
        //!
        //! @brief Server payment.
        //! @param bankToken Bank token.
        //! @return Server status.
        //!
        bool    paymentOrder(const std::string &bankToken);

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

#endif // CASH_MANAGER_CLIENT_WINDOW_CASHIER_DIALOGS_CHEQUEPAYMENTDIALOG_HPP

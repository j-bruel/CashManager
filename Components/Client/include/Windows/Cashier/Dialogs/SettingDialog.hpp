//!
//! @file SettingDialog.hpp
//! @author jbruel
//! @date 05/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_CASHIER_DIALOGS_SETTINGDIALOG_HPP
# define CASH_MANAGER_CLIENT_WINDOW_CASHIER_DIALOGS_SETTINGDIALOG_HPP

# include <QtCore/QVariant>
# include <QtWidgets/QAction>
# include <QtWidgets/QApplication>
# include <QtWidgets/QButtonGroup>
# include <QtWidgets/QCheckBox>
# include <QtWidgets/QDialog>
# include <QtWidgets/QDialogButtonBox>
# include <QtWidgets/QHeaderView>
# include <QtWidgets/QLabel>
# include <QtWidgets/QSpinBox>
#include <QtWidgets/QComboBox>

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
    //! @class SettingDialog
    //! @brief Setting dialog screen.
    //!
    class SettingDialog  : public QDialog
    {
    public:
        Q_OBJECT

    public:
        QDialogButtonBox    mValidateButtons; //!< Validator dialog buttons.
        QLabel              mPaymentConnexionDelayText; //!< Payment connexion delay text label.
        QLabel              mMaximunConnexionAttempsText; //!< Maximun connexion attemps text label.
        QSpinBox            mPaymentConnexionDelaySpinBox; //!< Payment connexion delay spin box.
        QSpinBox            mMaximunConnexionAttempsSpinBox; //!< Maximun connexion attemps spin box.
        QLabel              mDefaultMoneyDeviseText; //!< Default money devise text.
        QComboBox           mDefaultMoneyDevise; //!< Combo box for default money devise.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        SettingDialog() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit SettingDialog(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        SettingDialog(SettingDialog &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Dialog copy.
        //! @warning Not available.
        //!
        SettingDialog    &operator=(const SettingDialog &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~SettingDialog() override = default;

    public slots:
        //!
        //! @brief Slot for running setting dialog.
        //!
        void execSettingDialog();

    private slots:
        //!
        //! @brief Save all settings.
        //!
        void saveSettings();

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

#endif // CASH_MANAGER_CLIENT_WINDOW_CASHIER_DIALOGS_SETTINGDIALOG_HPP

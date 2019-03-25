//!
//! @file LCDBill.hpp
//! @author jbruel
//! @date 05/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WIDGETS_LCDBILL_HPP
# define CASH_MANAGER_CLIENT_WIDGETS_LCDBILL_HPP

# include <QtWidgets/QLCDNumber>
# include <QtWidgets/QLabel>
# include <QtGui/QKeyEvent>

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
//! @namespace bill
//!
namespace bill
{
//!
//! @namespace widget
//!
namespace widget
{

    //!
    //! @class LCDBill
    //! @brief Widget bill.
    //!
    class   LCDBill : public QWidget
    {
    public:
        Q_OBJECT

    private:
        QLCDNumber  mBill; //!< Number (bill) on screen.
        QLabel      mCurrency; //!< Currency print on screen.
        double      mCurrentBillValue; //!< Current bill value.

    public:
        //!
        //! @brief Constructor.
        //! @warning Not available.
        //!
        LCDBill() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit LCDBill(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        LCDBill(LCDBill &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Bill copy.
        //! @warning Not available.
        //!
        LCDBill    &operator=(const LCDBill &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~LCDBill() override = default;

    public:
        //!
        //! @brief Update the bill display on screen.
        //!
        inline void    updateBill() { mBill.display(priceToQString(mCurrentBillValue)); }

    public:
        //!
        //! @brief Update the bill value and display.
        //! @param bill New bill.
        //!
        void     setBill(double bill);
        //!
        //! @brief Update the bill to zero.
        //!
        void     unsetBill();
        //!
        //! @brief Add a specific price to the current bill and update the display.
        //! @param price Price to add to the current bill.
        //!
        void     addPriceToBill(double price);
        //!
        //! @brief Remove price from the current bill and update the display.
        //! @param price Price to remove to the current bill.
        //!
        void     removePriceToBill(double price);
        //!
        //! @brief Extract the current bill.
        //! @return Current bill.
        //!
        double   getBill() const { return (mCurrentBillValue); }

    private:
        //!
        //! @brief Initialize bill layout.
        //!
        void    initBillLayout();
        //!
        //! @brief Initialize the current layout.
        //!
        void    initCurrencyLayout();

    private:
        //!
        //! @brief Transform a price into a QT String.
        //! @param price Price.
        //! @return Price into QString.
        //!
        QString priceToQString(double price) const;
    };

}
}
}
}

#endif //CASH_MANAGER_CLIENT_WIDGETS_LCDBILL_HPP

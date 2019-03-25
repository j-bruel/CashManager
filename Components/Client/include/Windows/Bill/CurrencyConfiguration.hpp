//!
//! @file CurrencyConfiguration.hpp
//! @author jbruel
//! @date 05/12/18
//!

#ifndef CASHMANAGER_CLIENT_WINDOW_BILL_CURRENCYCONFIGURATION_HPP
# define CASHMANAGER_CLIENT_WINDOW_BILL_CURRENCYCONFIGURATION_HPP

# include <QtCore/QString>

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
    //! @static
    //! @brief  Bill currency symbol.
    //! @return Bill currency.
    //!
    static const QString    getBillCurrencySymbol() { return ("€"); }
    const size_t            BillCurrencyFontSize = 72; //!< Bill currency font size.

    //!
    //! @static
    //! @brief Currency background color.
    //! @return Background color.
    //!
    static const QString   getCurrencyBackgroundColor() { return ("background-color: blue; border: none;"); }
    //!
    //! @static
    //! @brief Currency number color.
    //! @return Currency text color.
    //!
    static const QString   getCurrencyColor() { return ("color: white;"); }

}
}
}

#endif //CASHMANAGER_CLIENT_WINDOW_BILL_CURRENCYCONFIGURATION_HPP

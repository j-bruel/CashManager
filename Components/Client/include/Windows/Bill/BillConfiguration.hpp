//!
//! @file BillConfiguration.hpp
//! @author jbruel
//! @date 05/12/18
//!

#ifndef CASHMANAGER_CLIENT_WINDOW_BILL_BILLCONFIGURATION_HPP
# define CASHMANAGER_CLIENT_WINDOW_BILL_BILLCONFIGURATION_HPP

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

    const size_t    WidthWindow = 600; //!< Bill window width size.
    const size_t    HeightWindow = 120; //!< Bill window height size.

    const size_t    BillWidthWindow = 500; //!< Bill (number only) screen width size.
    const size_t    BillHeightWindow = 120; //!< Bill (number only) screen height size.
    const size_t    BillMaxDigits = 8; //!< Bill max digits allow.

    const QString   BillBackgroundColor = "background-color: blue; border: none;"; //!< Bill background color.
    const QString   BillColor = "color: white;"; //!< Bill number color.

}
}
}

#endif //CASHMANAGER_CLIENT_WINDOW_BILL_BILLCONFIGURATION_HPP

//!
//! @file Idx.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef CASHMANAGER_CLIENT_TOOLS_LOG_IDX_HPP
# define CASHMANAGER_CLIENT_TOOLS_LOG_IDX_HPP

//!
//! @namespace cash
//!
namespace cash
{
//!
//! @namespace tool
//!
namespace tool
{
//!
//! @namespace log
//!
namespace log
{

    //!
    //! @enum Idx
    //! @brief Log index, tell witch output log use.
    //!
    enum    Idx
    {
        IN_FILE,
        IN_CONSOLE,
        IN_FILE_AND_CONSOLE
    };

}
}
}

#endif //CASHMANAGER_CLIENT_TOOLS_LOG_IDX_HPP

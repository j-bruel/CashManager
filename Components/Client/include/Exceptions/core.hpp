//!
//! @file core.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef CASHMANAGER_CLIENT_EXCEPTIONS_COREEXCEPTION_HPP
# define CASHMANAGER_CLIENT_EXCEPTIONS_COREEXCEPTION_HPP

# include "Exceptions/exception.hpp"

//!
//! @namespace cash
//!
namespace cash
{
//!
//! @namespace exceptions
//!
namespace exceptions
{
    //!
    //! @class core
    //! @brief Core exception.
    //!
    class   core : public cash::exception
    {
    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit core(const std::string &msg) : cash::exception(msg) { }
    };

}
}


#endif //CASHMANAGER_CLIENT_EXCEPTIONS_COREEXCEPTION_HPP

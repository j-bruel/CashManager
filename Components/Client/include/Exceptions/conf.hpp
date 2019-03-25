//!
//! @file conf.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef CASHMANAGER_CLIENT_EXCEPTIONS_CONF_HPP
# define CASHMANAGER_CLIENT_EXCEPTIONS_CONF_HPP

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
    //! @class conf
    //! @brief Conf exception.
    //!
    class   conf : public cash::exception
    {
    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit conf(const std::string &msg) : cash::exception(msg) { }
    };

}
}


#endif //CASHMANAGER_CLIENT_EXCEPTIONS_CONF_HPP

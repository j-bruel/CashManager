//!
//! @file include/Exceptions/exception.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef CASHMANAGER_CLIENT_EXCEPTION_EXCEPTION_HPP
# define CASHMANAGER_CLIENT_EXCEPTION_EXCEPTION_HPP

# include <string>

//!
//! @namespace cash
//!
namespace cash
{
    //!
    //! @class exception
    //! @brief Exception interface.
    //!
    class   exception : public std::exception
    {
    private:
        std::string     mMsg; //!< Message link to the exception.

    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit exception(const std::string &msg) : mMsg(msg) {}

    public:
        //!
        //! @brief Extract exception message.
        //! @return Exception message.
        //!
        inline const char   *what() const noexcept override { return (mMsg.c_str()); }
    };
}


#endif //CASHMANAGER_CLIENT_EXCEPTION_EXCEPTION_HPP

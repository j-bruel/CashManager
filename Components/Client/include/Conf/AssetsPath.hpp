//!
//! @file AssetsPath.hpp
//! @author jbruel
//! @date 17/12/18
//!

#ifndef CASH_MANAGER_CLIENT_CONF_ASSETSPATH_HPP
# define CASH_MANAGER_CLIENT_CONF_ASSETSPATH_HPP

# include <string>

//!
//! @namespace cash
//!
namespace cash
{
//!
//! @namespace conf
//!
namespace conf
{

    //!
    //! @static
    //! @brief Extract assets path.
    //! @return Assets location path.
    //!
    static const std::string    getAssetPath() { return ("../conf/assets/"); }

}
}

#endif //CASH_MANAGER_CLIENT_CONF_ASSETSPATH_HPP

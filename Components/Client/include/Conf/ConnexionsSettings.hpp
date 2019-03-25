//!
//! @file ConnexionsSettings.hpp
//! @author jbruel
//! @date 20/12/18
//!

#ifndef CASH_MANAGER_CLIENT_CONF_CONNEXIONSSETINGS_HPP
# define CASH_MANAGER_CLIENT_CONF_CONNEXIONSSETINGS_HPP

//!
//! @namespace cash
//!
#include <cstddef>
#include "Tools/Singleton.hpp"

namespace cash
{
//!
//! @namespace conf
//!
namespace conf
{

    //!
    //! @struct ConnexionsSettings
    //! @brief Connexions settings.
    //!
    struct ConnexionsSettings : tool::Singleton<ConnexionsSettings>
    {
        friend class tool::Singleton<ConnexionsSettings>; //!< Allow current class to become a singleton.

    public:
        size_t  mAttempts; //!< Max attempts allow.
        bool    mIsUnlimitedAttempts; //!< Set if attempts are not limited.
        size_t  mDelay; //!< Max delay allow.

        //!
        //! @brief set connexion setting.
        //! @param attempts Max attemps allow.
        //! @param delay Max delay allow.
        //!
        void    setConnexionsSettings(size_t attempts, size_t delay)
        {
            mAttempts = attempts;
            mIsUnlimitedAttempts = false;
            mDelay = delay;
        }
        //!
        //! @brief set when attempts are not limited.
        //! @param delay Max delay allow.
        //!
        void    setCnnexionsSettings(size_t delay)
        {
            mAttempts = 0;
            mIsUnlimitedAttempts = true;
            mDelay = delay;
        }

    };

}
}

#endif //CASH_MANAGER_CLIENT_CONF_CONNEXIONSSETINGS_HPP

//!
//! @file Observer.hpp
//! @author jbruel
//! @date 12/11/18
//!

#ifndef CASHMANAGER_CLIENT_TOOLS_OBSERVER_HPP
# define CASHMANAGER_CLIENT_TOOLS_OBSERVER_HPP

# include <memory>

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
    //! @class Observer
    //! @brief Pattern observer
    //!
    template <class T>
    class Observer
    {
    public:
        //!
        //! @brief Constructor
        //!
        Observer() = default;
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        Observer(const Observer &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @warning Not available.
        //!
        Observer &operator=(const Observer &) = delete;
        //!
        //! @brief Destructor.
        //!
        virtual ~Observer() = default;

    public:
        //!
        //! @brief Callback.
        //! @param subject Called subject.
        //! @return State.
        //!
        virtual bool    update(std::shared_ptr<T> &subject) = 0;
    };

}
}

#endif //CASHMANAGER_CLIENT_TOOLS_OBSERVER_HPP

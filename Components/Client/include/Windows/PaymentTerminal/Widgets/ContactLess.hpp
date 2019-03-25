//!
//! @file LCDBill.hpp
//! @author jbruel
//! @date 05/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_PAYMENTTERMINAl_WIDGETS_CONTACTLESS_HPP
# define CASH_MANAGER_CLIENT_WINDOW_PAYMENTTERMINAl_WIDGETS_CONTACTLESS_HPP

# include <QtWidgets/QWidget>
# include <QtWidgets/QLabel>

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
namespace term
{
//!
//! @namespace widget
//!
namespace widget
{

    //!
    //! @class ContactLess
    //! @brief Widget for contact less logo.
    //!
    class   ContactLess : public QLabel
    {
    public:
        Q_OBJECT

    public:
        //!
        //! @brief Constructor.
        //! @warning Not available.
        //!
        ContactLess() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit ContactLess(QWidget *parent) : QLabel(parent) {}
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        ContactLess(ContactLess &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Bill copy.
        //! @warning Not available.
        //!
        ContactLess    &operator=(const ContactLess &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~ContactLess() override = default;

    signals:
        //!
        //! @brief Clicked signal.
        //!
        void    clicked();

    protected:
        //!
        //! @brief Callback when mouse click.
        //!
        void    mousePressEvent(QMouseEvent *) { emit clicked(); }

    };

}
}
}
}

#endif //CASH_MANAGER_CLIENT_WINDOW_PAYMENTTERMINAl_WIDGETS_CONTACTLESS_HPP

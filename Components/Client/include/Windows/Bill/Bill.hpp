//!
//! @file Bill.hpp
//! @author jbruel
//! @date 05/12/18
//!

#ifndef CASH_MANAGER_CLIENT_WINDOW_BILL_HPP
# define CASH_MANAGER_CLIENT_WINDOW_BILL_HPP

# include "Windows/Bill/Widgets/LCDBill.hpp"
# include "Tools/Observer.hpp"
# include <QtWidgets/QWidget>

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
    //! @class Bill
    //! @brief Bill window.
    //!
    class   Bill : public QWidget, public tool::Observer<double>
    {
    private:
        QWidget                 mBillWindow; //!< Current Bill window.
        bill::widget::LCDBill   mBill; //!< Bill widgets.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        Bill() = delete;
        //!
        //! @brief Constructor.
        //! @param parent Parent widget.
        //!
        explicit Bill(QWidget *parent);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        Bill(Bill &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Bill copy.
        //! @warning Not available.
        //!
        Bill    &operator=(const Bill &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~Bill() override { mBillWindow.close(); }

    public Q_SLOTS:
        //!
        //! @brief Overload of show window function.
        //!
        inline virtual void show() { mBillWindow.show(); }

    public:
        //!
        //! @brief Update callback for observer patern.
        //! @param subject Subject.
        //! @return Status.
        //!
        bool    update(std::shared_ptr<double> &subject);

    private:
        //!
        //! @brief Initialize bill window.
        //!
        void initBillWindow();
    };

}
}
#endif //CASH_MANAGER_CLIENT_WINDOW_BILL_HPP

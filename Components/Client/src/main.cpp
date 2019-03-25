//!
//! @file T-ARC-Client-CashManager_2018/src/main.cpp
//! @author jbruel
//! @date 05/12/18
//!

#include "Core/CashManager.hpp"
#include "exception.hpp"
#include <QtWidgets/QApplication>
#include <Tools/Log/Initializer.hpp>
#include <plog/Log.h>

//!
//! @static
//! @brief Extract log path.
//! @return File log path.
//!
static const std::string   getLogPath() { return ("./cashmanager.log"); }

//!
//! @static
//! @brief Initialize logs
//!
static void initLog()
{
    cash::tool::log::initialize(getLogPath(), plog::verbose, plog::verbose);
    LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Log output file is " << getLogPath();
}

int main(int argc, char *argv[])
{
    QApplication            app(argc, argv);

    initLog();

    cash::core::CashManager cashManager;

    try {
        cashManager.init();
        cashManager.run();
    }
    catch (cash::exception &e) {
        LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::fatal) << "Fatal Error:  " << e.what();
        return (EXIT_FAILURE);
    }
    return (QApplication::exec());
}

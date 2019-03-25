//!
//! @file Initializer.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef CASHMANAGER_CLIENT_TOOLS_LOG_INITIALIZER_HPP
# define CASHMANAGER_CLIENT_TOOLS_LOG_INITIALIZER_HPP

# include "Tools/Log/PLogConsoleFormatter.hpp"
# include "Tools/Log/Idx.hpp"
# include <plog/Formatters/CsvFormatter.h>
# include <plog/Appenders/RollingFileAppender.h>
# include <plog/Appenders/ColorConsoleAppender.h>
# include <plog/Init.h>

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
    //! @static
    //! @fn static void initialize(const std::string &logFilePath)
    //! @brief Initialize logger system
    //! @param logFilePath Log file path.
    //! @param file Log in file severity level.
    //! @param console Log in console severity level.
    //!
    static void     initialize(const std::string &logFilePath, plog::Severity file, plog::Severity console)
    {
        static plog::RollingFileAppender<plog::CsvFormatter>        fileAppend(logFilePath.c_str());
        static plog::ColorConsoleAppender<plog::PLogConsoleFormatter>    consoleAppender;

        plog::init<IN_FILE>(file, &fileAppend);
        plog::init<IN_CONSOLE>(console, &consoleAppender);
        plog::init<IN_FILE_AND_CONSOLE>(plog::verbose, &fileAppend).addAppender(&consoleAppender);
    }

}
}
}

#endif //CASHMANAGER_CLIENT_TOOLS_LOG_INITIALIZER_HPP

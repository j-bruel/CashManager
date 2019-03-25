//!
//! @file ExceptionTest.cpp
//! @author jbruel
//! @date 01/11/18
//!

#include "Exceptions/exception.hpp"
#include "Exceptions/conf.hpp"
#include "Exceptions/core.hpp"
#include <gtest/gtest.h>

//!
 //! @test Own exceptions interface.
 //!
TEST (Exception, exceptions)
{
    try {
        throw cash::exception("Conf exception test.");
    }
    catch (cash::exception &e) {
        EXPECT_STRCASEEQ(e.what(), "Conf exception test.");
        return ;
    }
    FAIL() << "IException excepted.";
}

//!
//! @test Core exception
//!
TEST (Exception, core)
{
    try {
        throw cash::exceptions::core("Core exception test.");
    }
    catch (cash::exception &e) {
        EXPECT_STRCASEEQ(e.what(), "Core exception test.");
        return ;
    }
    FAIL() << "IException excepted.";
}

//!
//! @test Configuration exception
//!
TEST (Exception, conf)
{
    try {
        throw cash::exceptions::conf("Help exception test.");
    }
    catch (cash::exception &e) {
        EXPECT_STRCASEEQ(e.what(), "Help exception test.");
        return ;
    }
    FAIL() << "IException excepted.";
}

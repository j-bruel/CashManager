##
## Cmake minimun version
##
cmake_minimum_required(VERSION 3.8.1)

##
## Projet Name
##
project(cash-manager-client)

##
## C++ Stantard compilation
##
set(CMAKE_CXX_STANDARD 14)

##
## Binary / Library location
##
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

##
## Instruct CMake to run moc automatically when needed.
##
set(CMAKE_AUTOMOC ON)

##
## Flags
##
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -g3  -W -Wall -Wextra -fPIC -DQT_NO_VERSION_TAGGING")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -fPIC -DQT_NO_VERSION_TAGGING")

##
## Cmake variables
##
set(CASHMANAGER_LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Libs/")
set(CASHMANAGER_GTEST_DIR "${CASHMANAGER_LIBS_DIR}/googletest/googletest")
set(CASHMANAGER_PLOG_DIR "${CASHMANAGER_LIBS_DIR}/plog")
set(QT_ROOT_DIR "$ENV{QT_ROOT_DIR}")
set(QT_INCLUDEDIR "$ENV{QT_INCLUDEDIR}")
set(QT_LIBRARYDIR "$ENV{QT_LIBRARYDIR}")

##
## Give message from variables setting
##
if (QT_ROOT_DIR)
    message(STATUS "The QT root directory (QT_ROOT_DIR) is " ${QT_ROOT_DIR})
else()
    message(WARNING "The Qt root directory (QT_ROOT_DIR) is undefine.")
endif()
if (QT_INCLUDEDIR)
    message(STATUS "The include directory of boost (QT_INCLUDEDIR) is " ${QT_INCLUDEDIR})
else()
    message(FATAL_ERROR "The include directory of boost (QT_INCLUDEDIR) is undefine.")
endif()
if (QT_LIBRARYDIR)
    message(STATUS "The library of boost (QT_LIBRARYDIR) is " ${QT_LIBRARYDIR})
else()
    message(FATAL_ERROR "The library of boost (QT_LIBRARYDIR) is undefine.")
endif()

##
## Headers included
##
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CASHMANAGER_PLOG_DIR}/include)
include_directories(${QT_INCLUDEDIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/include)

##
## Find QT packages
##
find_package( ${QT_LIBRARYDIR}/cmake/Qt5Core/Qt5Core REQUIRED )
find_package( ${QT_LIBRARYDIR}/cmake/Qt5Widgets/Qt5Widgets REQUIRED )
find_package( ${QT_LIBRARYDIR}/cmake/Qt5Gui/Qt5Gui REQUIRED )

##
## Sources files
##
file(GLOB_RECURSE SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

##
## Special files with Q_OBJECT
##
set(WIDGET_SOURCE_FILES include/Windows/Bill/Widgets/LCDBill.hpp
                        include/Windows/Cashier/Cashier.hpp
                        include/Windows/PaymentTerminal/Widgets/PaymentTerminalScreen.hpp
                        include/Windows/PaymentTerminal/Widgets/CodePinHandler.hpp
                        include/Windows/PaymentTerminal/Widgets/ContactLess.hpp
                        include/Windows/Cashier/Widgets/CashierScreen.hpp
                        include/Windows/Cashier/Dialogs/CreditCardDialog.hpp
                        include/Windows/Cashier/Dialogs/SettingDialog.hpp
                        include/Windows/Cashier/Dialogs/ChequePaymentDialog.hpp
                        include/Network/ARequest.hpp
                        include/Network/NetworkAPI.hpp
                        include/Network/BankAPI.hpp
                        include/Network/WarehouseAPI.hpp
                        include/Network/Request/Authenticate.hpp
                        include/Network/Request/BankCheck.hpp
                        include/Network/Request/CardPayment.hpp
                        include/Network/Request/CardPaymentContactless.hpp
                        include/Network/Request/ArticleList.hpp
                        include/Network/Request/ArticleScan.hpp
                        include/Windows/Cashier/Widgets/CashierScreen.hpp
                        include/Windows/Cashier/Dialogs/CashPaymentDialog.hpp)

##
## Create binary / Link
##
QT5_WRAP_CPP(manager_moc ${WIDGET_SOURCE_FILES})
add_executable(${PROJECT_NAME}          ${SOURCE_FILES}
                                        ${INCLUDE_FILES}
                                        ${manager_moc})
QT5_USE_MODULES(${PROJECT_NAME} Widgets)
QT5_USE_MODULES(${PROJECT_NAME} Core)
QT5_USE_MODULES(${PROJECT_NAME} Gui)
target_link_libraries(${PROJECT_NAME}   pthread
                                        Qt5::Widgets
                                        Qt5::Core
                                        Qt5::Gui
                                        Qt5::Network)

##
## Testing with gtests
##
enable_testing()

##
## GTests path variables
##
set(GTESTS_ROOT "${CASHMANAGER_GTEST_DIR}")
set(GTESTS_INCLUDEDIR "${CASHMANAGER_GTEST_DIR}/include")
set(GTESTS_LIBRARYDIR "${CASHMANAGER_GTEST_DIR}/build")

##
## Add GTests headers
##
include_directories(${GTESTS_INCLUDEDIR})

##
## Enable testing
##
enable_testing()

##
## Sources files
##
file(GLOB_RECURSE SOURCE_TESTS_FILES    ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp
                                        ${CMAKE_CURRENT_SOURCE_DIR}/test/*.hpp)
file(GLOB_RECURSE SOURCES_BINARY_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SOURCES_BINARY_FILES   ${CMAKE_SOURCE_DIR}/src/main.cpp)
list(FILTER SOURCES_BINARY_FILES EXCLUDE REGEX ".*src/App.cpp$")

##
## Create binary / Link
##
QT5_WRAP_CPP(manager_moc ${WIDGET_SOURCE_FILES})
add_executable(${PROJECT_NAME}-ut           ${SOURCES_BINARY_FILES}
                                            ${SOURCE_TESTS_FILES}
                                            ${manager_moc})
QT5_USE_MODULES(${PROJECT_NAME}-ut Widgets)
QT5_USE_MODULES(${PROJECT_NAME}-ut Core)
QT5_USE_MODULES(${PROJECT_NAME}-ut Gui)
QT5_USE_MODULES(${PROJECT_NAME}-ut Network)
QT5_USE_MODULES(${PROJECT_NAME}-ut Test)
target_link_libraries(${PROJECT_NAME}-ut    ${GTESTS_LIBRARYDIR}/libgtest.a
                                            ${GTESTS_LIBRARYDIR}/libgtest_main.a
                                            pthread
                                            Qt5::Widgets
                                            Qt5::Core
                                            Qt5::Gui
                                            Qt5::Network
                                            Qt5::Test)

cmake_minimum_required(VERSION 3.5)

project(QtFinance VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
        # Main
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        # Class
        Class/Expense.h
        Class/Expense.cpp
        Class/Income.h
        Class/Income.cpp
        # Code
        Code/Messages.h
        Code/Messages.cpp
        Code/Style.h
        Code/Style.cpp
        Code/SqlFilter.h
        Code/SqlFilter.cpp
        Code/PeriodTypes.h
        Code/PeriodTypes.cpp
        # Database
        Database/DatabaseManager.h
        Database/DatabaseManager.cpp
        # DatabaseClass
        DatabaseClass/ExpenseDao.h
        DatabaseClass/ExpenseDao.cpp
        DatabaseClass/IncomeDao.h
        DatabaseClass/IncomeDao.cpp
        DatabaseClass/ExpenseAnalysis.h
        DatabaseClass/ExpenseAnalysis.cpp
        # Dialog
        Dialog/ExpenseDialog.h
        Dialog/ExpenseDialog.cpp
        Dialog/ExpenseDialog.ui
        Dialog/IncomeDialog.h
        Dialog/IncomeDialog.cpp
        Dialog/IncomeDialog.ui
        # Model
        Model/ExpenseModel.h
        Model/ExpenseModel.cpp
        Model/IncomeModel.h
        Model/IncomeModel.cpp
        # Widget
        Widget/ExpenseWidget.h
        Widget/ExpenseWidget.cpp
        Widget/ExpenseWidget.ui
        Widget/IncomeWidget.h
        Widget/IncomeWidget.cpp
        Widget/IncomeWidget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtFinance
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(QtFinance SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(QtFinance
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QtFinance PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(QtFinance PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(QtFinance PRIVATE Qt${QT_VERSION_MAJOR}::Core)

set_target_properties(QtFinance PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QtFinance
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtFinance)
endif()

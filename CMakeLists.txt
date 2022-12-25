cmake_minimum_required(VERSION 3.20)

project(QtFinance VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

set(PROJECT_SOURCES
        # Main
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)

add_subdirectory(Widget)
add_subdirectory(Dialog)

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

add_subdirectory(Class)
add_subdirectory(Code)
add_subdirectory(Database)
add_subdirectory(DatabaseClass)
add_subdirectory(Model)


target_link_libraries(QtFinance PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(QtFinance PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(QtFinance PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(QtFinance PRIVATE Qt${QT_VERSION_MAJOR}::Network)

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

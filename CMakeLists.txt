cmake_minimum_required(VERSION 3.5)

project(qt-desktop-window VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(LIBRARY_SOURCES
    desktopwindow.cpp desktopwindow.h
)

add_library(qt-desktop-window STATIC
    ${LIBRARY_SOURCES}
)

target_link_libraries(qt-desktop-window PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set(SAMPLE_SOURCES
        main.cpp
        samplewindow.cpp
        samplewindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt-desktop-window-sample
        MANUAL_FINALIZATION
        ${SAMPLE_SOURCES}
    )
else()
    add_executable(qt-desktop-window-sample
        ${SAMPLE_SOURCES}
    )
endif()

target_link_libraries(qt-desktop-window-sample PRIVATE qt-desktop-window)
target_link_libraries(qt-desktop-window-sample PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt-desktop-window-sample)
endif()

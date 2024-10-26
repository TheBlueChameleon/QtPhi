cmake_minimum_required(VERSION 3.16)

# ============================================================================ #
# language definition

project(QtPhi
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ............................................................................ #
# AVX

# set this to NO if your target does not support AVX CPU instructions
set (ENABLE_AVX YES)

if (ENABLE_AVX)
    set (CMAKE_CXX_FLAGS "-mavx512f")
    message(STATUS "AVX EXTENSION ENABLED")
else()
    message(STATUS "AVX EXTENSION DISABLED")
endif()

# ============================================================================ #
# source file definitions

include_directories(
    src/
)

# ............................................................................ #
# base

add_library(Phi-base STATIC
    src/base/base.h
    src/base/errors.h src/base/errors.cpp
    src/base/coordinates/grid.h
    src/base/coordinates/coordinate.h   src/base/coordinates/coordinate.txx src/base/coordinates/coordinate.cpp
    src/base/coordinates/basegrid.h     src/base/coordinates/basegrid.txx   src/base/coordinates/basegrid.cpp
)

# ............................................................................ #
# physics

add_library(Phi-physics STATIC
    src/physics/physics.h
    src/physics/gridfactory.h src/physics/gridfactory.cpp
    src/physics/potential/potentialgrid.h src/physics/potential/potentialgrid.cpp
)

if (NOT ENABLE_AVX)
    target_compile_definitions(Phi-physics PUBLIC NO_AVX_ACCELERATION)
endif()

# ............................................................................ #
# ui

set(UI_SOURCES
        src/main.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
)

# ============================================================================ #
# QT components

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtPhi
        MANUAL_FINALIZATION
        ${UI_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtPhi APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtPhi SHARED
            ${UI_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtPhi
            ${UI_SOURCES}
        )
    endif()
endif()

# ============================================================================ #
# unit test framework

# ============================================================================ #
# linker setup

target_link_libraries(QtPhi PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Phi-base
    Phi-physics
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QtPhi)
endif()
set_target_properties(QtPhi PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QtPhi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtPhi)
endif()

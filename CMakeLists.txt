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
set (ENABLE_AVX NO)

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
    src/base/concepts.h
    src/base/errors.h src/base/errors.cpp
    src/base/geometry/coordinate.h src/base/geometry/coordinate.txx src/base/geometry/coordinate.cpp
    src/base/geometry/rect.h src/base/geometry/rect.txx src/base/geometry/rect.cpp
    src/base/geometry/grid.h
    src/base/geometry/basegrid.h src/base/geometry/basegrid.txx src/base/geometry/basegrid.cpp
    src/base/geometry/imposablegrid.h src/base/geometry/imposablegrid.txx src/base/geometry/imposablegrid.cpp
)

if (ENABLE_AVX)
    target_compile_definitions(Phi-base PUBLIC ENABLE_AVX)
endif()

# ............................................................................ #
# physics

add_library(Phi-physics STATIC
    src/physics/physics.h
    src/physics/gridfactory.h src/physics/gridfactory.cpp
    src/physics/potential/potentialgrid.h src/physics/potential/potentialgrid.cpp
)

if (ENABLE_AVX)
    target_compile_definitions(Phi-physics PUBLIC ENABLE_AVX)
endif()

# ............................................................................ #
# ui

set(UI_SOURCES
        src/main.cpp
        src/ui/mainwindow.h src/ui/mainwindow.cpp src/ui/mainwindow.ui
)

# ============================================================================ #
# QT components

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets Test
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets Test
)

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


# ============================================================================ #
# unit test framework

add_executable(unittest
    unittest/unittest_main.cpp
    unittest/base/coordinatetest.h unittest/base/coordinatetest.cpp
    unittest/base/recttest.h unittest/base/recttest.cpp
    unittest/base/basegridtest.h unittest/base/basegridtest.cpp
    unittest/base/imposablegridtest.h unittest/base/imposablegridtest.cpp
)

target_link_libraries(unittest PRIVATE
    Phi-base

    Qt6::Core
    Qt6::Gui
    Qt6::Test
    Qt6::Widgets
)

# ............................................................................ #
# static assert test files

# add_executable(unittest_failToCompile
#     unittest/assertFailToCompile.cpp
# )

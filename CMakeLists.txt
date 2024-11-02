cmake_minimum_required(VERSION 3.16)

# ============================================================================ #
# language definition

project(PhiGame
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
# QT components

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets Test
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets Test
)

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
    src/base/errors.h                       src/base/errors.cpp
    src/base/functions/functions.h          src/base/functions/functions.cpp
    src/base/geometry/coordinate.h          src/base/geometry/coordinate.cpp
    src/base/geometry/rect.h                src/base/geometry/rect.cpp
    src/base/geometry/pixelrectiterator.h   src/base/geometry/pixelrectiterator.cpp
    src/base/grid/basegrid.h                src/base/grid/basegrid.cpp
    src/base/grid/imposablegrid.h           src/base/grid/imposablegrid.cpp
    src/base/interpolation/interpolation.h  src/base/interpolation/interpolation.cpp
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
# gui

add_library(Phi-gui STATIC
    src/ui/mainwindow.h             src/ui/mainwindow.cpp
    src/ui/colormap/colormap.h
    src/ui/colormap/lerpcolormap.h  src/ui/colormap/lerpcolormap.cpp
    src/ui/widgets/colormaplegend.h src/ui/widgets/colormaplegend.cpp
    src/ui/widgets/gridsview.h      src/ui/widgets/gridsview.cpp
)

# ............................................................................ #
# main

set(MAIN_SOURCES
    src/main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Phi-main
        MANUAL_FINALIZATION
        ${MAIN_SOURCES}
    )
else()
    qt_add_executable(Phi-main
        ${MAIN_SOURCES}
    )
endif()

# ============================================================================ #
# linker setup

target_link_libraries(Phi-gui PRIVATE
    Phi-base

    Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(Phi-main PRIVATE
    Phi-base
    Phi-physics
    Phi-gui

    Qt${QT_VERSION_MAJOR}::Widgets
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Phi-main)
endif()
set_target_properties(Phi-main PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Phi-main
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Phi-main)
endif()

# ============================================================================ #
# unit test framework

add_executable(unittest
    unittest/unittest_main.cpp
    unittest/base/coordinatetest.h unittest/base/coordinatetest.cpp
    unittest/base/recttest.h unittest/base/recttest.cpp
    unittest/base/basegridtest.h unittest/base/basegridtest.cpp
    unittest/base/imposablegridtest.h unittest/base/imposablegridtest.cpp
    unittest/base/interpolationtest.h unittest/base/interpolationtest.cpp
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

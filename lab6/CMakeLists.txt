cmake_minimum_required(VERSION 3.10)

project(Lab5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

add_executable(Lab5
    main.cpp
    param.h
    param.cpp
    mainwindow.cpp
)

target_include_directories(Lab5 PRIVATE /opt/homebrew/opt/qt/lib/QtWidgets.framework/Headers)
target_include_directories(Lab5 PRIVATE /opt/homebrew/opt/qt/lib/QtGui.framework/Headers)
target_include_directories(Lab5 PRIVATE /opt/homebrew/opt/qt/lib/QtCore.framework/Headers)

target_link_libraries(Lab5
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
)

set_target_properties(Lab5 PROPERTIES
    COMPILE_OPTIONS "-F;/opt/homebrew/opt/qt/lib"
)

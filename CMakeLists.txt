cmake_minimum_required(VERSION 3.1.0)

project(rook)

set(CMAKE_CXX_STANDARD 14)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Auto handling of qrc resource files
set(CMAKE_AUTORCC ON)

set (CMAKE_PREFIX_PATH "D:/Qt/5.12.3/msvc2017_64")

# Find the Qt libraries
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core)

get_target_property(QtCore_location Qt5::Core LOCATION)

# Populate a CMake variable with the sources
set(rook_SRCS
        resources.qrc
        cpuPlayer.cpp
        cpuPlayer.h
        gamecontroller.cpp
        gamecontroller.h
        mainwindow.cpp
        mainwindow.h
        messageBox.ui
        messageBox.h
        messageBox.cpp
        nestDialog.ui
        nestDialog.h
        nestDialog.cpp
        bidDialog.ui
        bidDialog.h
        bidDialog.cpp
        trumpLabel.cpp
        trumpLabel.h
        trumpDialog.ui
        trumpDialog.h
        trumpDialog.cpp
        clickableCard.h
        clickableCard.cpp
        main.cpp
)

# Tell Cmake to create the hello world executable
add_executable(rook WIN32 ${rook_SRCS})

# Use the Widgets module from Qt 5
target_link_libraries(rook Qt5::Widgets)
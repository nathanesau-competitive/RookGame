cmake_minimum_required(VERSION 3.1.0)

project(rook)

set(CMAKE_CXX_STANDARD 17)

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
        src/bidDialog.cpp
        src/bidDialog.h
        src/bidDialog.ui
        src/card.cpp
        src/card.h
        src/clickableCard.cpp
        src/clickableCard.h
        src/cpuPlayer.cpp
        src/cpuPlayer.h
        src/gameController.cpp
        src/gameController.h
        src/gameInfoWidget.cpp
        src/gameInfoWidget.h
        src/handInfo.cpp
        src/handInfo.h
        src/main.cpp
        src/mainWidget.cpp
        src/mainWidget.h
        src/mainWindow.cpp
        src/mainWindow.h
        src/messageBox.cpp
        src/messageBox.h
        src/messageBox.ui
        src/middleDialog.cpp
        src/middleDialog.h
        src/middleDialog.ui
        src/player.cpp
        src/player.h
        src/resources.qrc
        src/roundSummaryDialog.cpp
        src/roundSummaryDialog.h
        src/trumpLabel.cpp
        src/trumpLabel.h
        src/utils.cpp
        src/utils.h
)

# Tell Cmake to create the hello world executable
add_executable(rook WIN32 ${rook_SRCS})

# Use the Widgets module from Qt 5
target_link_libraries(rook Qt5::Widgets)
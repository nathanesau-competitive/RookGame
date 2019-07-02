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

# Set Qt Path
set(QtPath "D:/Qt/5.12.3/msvc2017_64")
set(CMAKE_PREFIX_PATH ${QtPath})

# Find the Qt libraries
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core)

get_target_property(QtCore_location Qt5::Core LOCATION)

# Populate a CMake variable with the sources
set(rook_SRCS
        src/appearancePage.cpp
        src/appearancePage.h
        src/bidDialog.cpp
        src/bidDialog.h
        src/bidDialog.ui
        src/card.cpp
        src/card.h
        src/clickableCard.cpp
        src/clickableCard.h
        src/common.cpp
        src/common.h
        src/cpuPlayer.cpp
        src/cpuPlayer.h
        src/gameController.cpp
        src/gameController.h
        src/gameInfoWidget.cpp
        src/gameInfoWidget.h
        src/gameMenuWidget.cpp
        src/gameMenuWidget.h
        src/gamePage.cpp
        src/gamePage.h
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
        src/nestDialog.cpp
        src/nestDialog.h
        src/overallInfo.cpp
        src/overallInfo.h
        src/player.cpp
        src/player.h
        src/partnerDialog.cpp
        src/partnerDialog.h
        src/preferencesDialog.cpp
        src/preferencesDialog.h
        src/resources.qrc
        src/roundInfo.h
        src/roundInfo.cpp
        src/roundSummaryDialog.cpp
        src/roundSummaryDialog.h
        src/trumpDialog.cpp
        src/trumpDialog.h
        src/utils.cpp
        src/utils.h
)

add_executable(rook WIN32 ${rook_SRCS})

# Copy Qt debug dlls
configure_file(${QtPath}/bin/Qt5Widgetsd.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Widgetsd.dll COPYONLY)
configure_file(${QtPath}/bin/Qt5Cored.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Cored.dll COPYONLY)
configure_file(${QtPath}/bin/Qt5Guid.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Guid.dll COPYONLY)

# link the Qt libraries
target_link_libraries(rook Qt5::Widgets)
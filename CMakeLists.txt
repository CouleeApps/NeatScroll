cmake_minimum_required(VERSION 3.0)
set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk)

project(NeatScroll)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        NeatScroll/SynapticsTouchpad.cpp
        NeatScroll/stdafx.cpp
        NeatScroll/TaskViewDetector.cpp
        NeatScroll/NeatScroll.cpp
        NeatScroll/Movement.cpp
        NeatScroll/GestureHandler.cpp
        NeatScroll/MovementDetector.cpp
        NeatScroll/Gesture.cpp
        NeatScroll/Gestures/FourFingersUpGesture.cpp
        NeatScroll/Gestures/FourFingersRightGesture.cpp
        NeatScroll/Gestures/FourFingersLeftGesture.cpp
        NeatScroll/Gestures/FourFingersDownGesture.cpp
        NeatScroll/Actions/TaskViewOpenPerformer.cpp
        NeatScroll/Actions/TaskViewClosePerformer.cpp
        NeatScroll/Actions/VirtualDesktopLeftPerformer.cpp
        NeatScroll/Actions/VirtualDesktopRightPerformer.cpp
)

include_directories(NeatScroll/Include)
link_directories(NeatScroll/Lib/x64)

add_executable(NeatScroll ${SOURCE_FILES})
target_link_libraries(NeatScroll SynCom)

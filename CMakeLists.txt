cmake_minimum_required(VERSION 3.0)
set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk)

project(NeatScroll)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        NeatScroll/SynapticsTouchpad.cpp
        NeatScroll/stdafx.cpp
        NeatScroll/NeatScroll.cpp
        NeatScroll/Movement.cpp
        NeatScroll/GestureHandler.cpp
        NeatScroll/MovementDetector.cpp
        NeatScroll/Gesture.cpp
        NeatScroll/Gestures/SwipeGestureRecognizer.h
        NeatScroll/Actions/ConditionalPerformer.h
        NeatScroll/Actions/CombiningPerformer.h
        NeatScroll/Actions/CombiningPerformer.cpp
        NeatScroll/Actions/KeyPressPerformer.cpp
        NeatScroll/Actions/KeyPressPerformer.h
        NeatScroll/Gestures/SwipeGestureRecognizer.cpp
        NeatScroll/ProcessDetector.cpp
        NeatScroll/ProcessDetector.h
        NeatScroll/Timer.h
        NeatScroll/HighPerformanceTimer.cpp
        NeatScroll/HighPerformanceTimer.h
        NeatScroll/WindowDetector.cpp
        NeatScroll/WindowDetector.h
)

source_group("Actions" REGULAR_EXPRESSION Actions/.*)
source_group("Gestures" REGULAR_EXPRESSION Gestures/.*)

include_directories(NeatScroll/Include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(NeatScroll/Lib/x64)

add_executable(NeatScroll ${SOURCE_FILES})
target_link_libraries(NeatScroll SynCom)

target_compile_definitions(NeatScroll PRIVATE UNICODE _UNICODE)

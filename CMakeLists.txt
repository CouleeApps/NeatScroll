cmake_minimum_required(VERSION 3.0)
set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk)

project(NeatScroll)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        NeatScroll/SynapticsTouchpad.cpp
        NeatScroll/stdafx.cpp
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

add_library(NeatScroll STATIC ${SOURCE_FILES})
target_link_libraries(NeatScroll ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/Lib/x64/SynCom.lib)

link_directories("3rdparty/Lib/x64")
include_directories(3rdparty/Include)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/NeatScroll")
add_definitions(-DUNICODE -D_UNICODE)

add_executable(TestGestures TestGestures/TestGestures.cpp)
target_link_libraries(TestGestures NeatScroll)
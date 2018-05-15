cmake_minimum_required(VERSION 3.0)
set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk)

project(NeatScroll)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        # Abstract interfaces
        NeatScroll/Timer.h
        NeatScroll/Touchpad.hpp

        # Logic and data control
        NeatScroll/Gesture.cpp
        NeatScroll/Gesture.hpp
        NeatScroll/Movement.cpp
        NeatScroll/Movement.h
        NeatScroll/GestureHandler.cpp
        NeatScroll/GestureHandler.hpp
        NeatScroll/MovementDetector.cpp
        NeatScroll/MovementDetector.hpp
        
        # Extra math utils
        NeatScroll/bezier.h

        # Actions
        NeatScroll/Actions/CombiningPerformer.cpp
        NeatScroll/Actions/CombiningPerformer.h
        NeatScroll/Actions/ConditionalPerformer.h
        NeatScroll/Actions/KeyPressPerformer.cpp
        NeatScroll/Actions/KeyPressPerformer.h

        # Gestures
        NeatScroll/Gestures/SwipeGestureRecognizer.cpp
        NeatScroll/Gestures/SwipeGestureRecognizer.h

        # Windows-specific classes
        NeatScroll/HighPerformanceTimer.cpp
        NeatScroll/HighPerformanceTimer.h
        NeatScroll/ProcessDetector.cpp
        NeatScroll/ProcessDetector.h
        NeatScroll/SynapticsTouchpad.cpp
        NeatScroll/SynapticsTouchpad.hpp
        NeatScroll/WindowDetector.cpp
        NeatScroll/WindowDetector.h

        # Dirty Windows files!
        NeatScroll/stdafx.cpp
        NeatScroll/stdafx.h
        NeatScroll/targetver.h
)

source_group("Actions" REGULAR_EXPRESSION Actions/.*)	
source_group("Gestures" REGULAR_EXPRESSION Gestures/.*)

add_library(NeatScroll STATIC ${SOURCE_FILES})

link_directories("3rdparty/Lib/x64")
include_directories(3rdparty/Include)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/NeatScroll")
add_definitions(-DUNICODE -D_UNICODE)
target_link_libraries(NeatScroll SynCom)

add_executable(TestGestures TestGestures/TestGestures.cpp)
target_link_libraries(TestGestures NeatScroll)
target_link_libraries(TestGestures SynCom)
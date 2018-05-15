cmake_minimum_required(VERSION 3.0)
set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk)

project(NeatScroll)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        # Abstract interfaces
        NeatScroll/Timer.hpp
        NeatScroll/Touchpad.hpp

        # Logic and data control
        NeatScroll/Gesture.cpp
        NeatScroll/Gesture.hpp
        NeatScroll/Movement.cpp
        NeatScroll/Movement.hpp
        NeatScroll/GestureHandler.cpp
        NeatScroll/GestureHandler.hpp
        NeatScroll/MovementDetector.cpp
        NeatScroll/MovementDetector.hpp
        
        # Extra math utils
        NeatScroll/Bezier.hpp

        # Actions
        NeatScroll/Actions/CombiningPerformer.cpp
        NeatScroll/Actions/CombiningPerformer.hpp
        NeatScroll/Actions/ConditionalPerformer.hpp
        NeatScroll/Actions/KeyPressPerformer.cpp
        NeatScroll/Actions/KeyPressPerformer.hpp

        # Gestures
        NeatScroll/Gestures/SwipeGestureRecognizer.cpp
        NeatScroll/Gestures/SwipeGestureRecognizer.hpp

        # Windows-specific classes
        NeatScroll/HighPerformanceTimer.cpp
        NeatScroll/HighPerformanceTimer.hpp
        NeatScroll/ProcessDetector.cpp
        NeatScroll/ProcessDetector.hpp
        NeatScroll/SynapticsTouchpad.cpp
        NeatScroll/SynapticsTouchpad.hpp
        NeatScroll/WindowDetector.cpp
        NeatScroll/WindowDetector.hpp

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
#include "stdafx.h"
#include <functional>
#include "Touchpad.hpp"
#include "SynapticsTouchpad.hpp"
#include "MovementDetector.hpp"
#include "GestureHandler.hpp"
#include "Actions/ConditionalPerformer.h"
#include "Actions/KeyPressPerformer.h"
#include "Gestures/SwipeGestureRecognizer.h"
#include "ProcessDetector.h"
#include "WindowDetector.h"
#include <thread>

int main(int argc, const char **argv) {
	using namespace std::placeholders;

	SynapticsTouchpad touchpad;
	MovementDetector detector(touchpad);
	GestureHandler handler;
	touchpad.setHandler(&detector);
	detector.setGestureHandler(&handler);
	
	//Gesture recognizers
	auto up3Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Up, 3, 0.2f);
	auto down3Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Down, 3, 0.2f);
	auto left3Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Left, 3, 0.2f);
	auto right3Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Right, 3, 0.2f);
	//Detect task view by its active window in the foreground
	auto taskViewProcessDetector = ProcessDetector("explorer.exe");
	auto taskViewWindowDetector = WindowDetector("Task View");
	auto isTaskView = [&]() {
		return taskViewProcessDetector.isProcessDetected() && taskViewWindowDetector.isWindowDetected();
	};

	//Gesture performers
	auto winTabPerf = KeyPressPerformer({ VK_LWIN, VK_TAB });
	auto openTaskViewPerf = ConditionalPerformer{ winTabPerf, [&isTaskView]() { return !isTaskView(); } };
	auto closeTaskViewPerf = ConditionalPerformer{ winTabPerf, isTaskView };
	auto vDeskLeftPerf = KeyPressPerformer({ VK_LWIN, VK_LCONTROL, VK_LEFT });
	auto vDeskRightPerf = KeyPressPerformer({ VK_LWIN, VK_LCONTROL, VK_RIGHT });

	//Construct and add the actual gestures
	Gesture ffuGesture{ up3Rec, openTaskViewPerf };
	Gesture ffdGesture{ down3Rec, closeTaskViewPerf };
	Gesture fflGesture{ left3Rec, vDeskLeftPerf };
	Gesture ffrGesture{ right3Rec, vDeskRightPerf };
	handler.addGesture(&ffuGesture);
	handler.addGesture(&ffdGesture);
	handler.addGesture(&fflGesture);
	handler.addGesture(&ffrGesture);

	if (!touchpad.connect()) {
		fprintf(stderr, "Could not connect to touchpad\n");
		return EXIT_FAILURE;
	}

	//To disable the system using this, uncomment this line.
	// Just make sure you have a mouse nearby in case the program crashes
	touchpad.acquire(true);

	while (true) {
		if (!touchpad.poll()) {
			break;
		}
		//Performance
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	if (!touchpad.disconnect()) {
		fprintf(stderr, "Error disconnecting touchpad\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

#include "stdafx.h"
#include <functional>
#include "Touchpad.hpp"
#include "SynapticsTouchpad.hpp"
#include "MovementDetector.hpp"
#include "GestureHandler.hpp"
#include "Actions/TaskViewClosePerformer.h"
#include "Actions/TaskViewOpenPerformer.h"
#include "Actions/VirtualDesktopLeftPerformer.h"
#include "Actions/VirtualDesktopRightPerformer.h"
#include "Gestures/SwipeGestureRecognizer.h"
#include <thread>

int main(int argc, const char **argv) {
	using namespace std::placeholders;

	SynapticsTouchpad touchpad;
	MovementDetector detector(touchpad);
	GestureHandler handler;
	touchpad.setHandler(&detector);
	detector.setGestureHandler(&handler);

	Gesture ffuGesture{ SwipeGestureRecognizer<Up, 4>(0.2f), TaskViewOpenPerformer() };
	Gesture ffdGesture{ SwipeGestureRecognizer<Down, 4>(0.2f), TaskViewClosePerformer() };
	Gesture fflGesture{ SwipeGestureRecognizer<Left, 4>(0.2f), VirtualDesktopLeftPerformer() };
	Gesture ffrGesture{ SwipeGestureRecognizer<Right, 4>(0.2f), VirtualDesktopRightPerformer() };
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

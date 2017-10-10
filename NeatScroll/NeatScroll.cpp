#include "stdafx.h"
#include <functional>
#include "Touchpad.hpp"
#include "SynapticsTouchpad.hpp"
#include "GestureDetector.hpp"
#include "GestureHandler.hpp"
#include "FourFingersUpGesture.h"
#include "FourFingersDownGesture.h"
#include "FourFingersLeftGesture.h"
#include "FourFingersRightGesture.h"
#include <thread>

int main(int argc, const char **argv) {
	using namespace std::placeholders;

	SynapticsTouchpad touchpad;
	GestureDetector detector(touchpad);
	GestureHandler handler;
	touchpad.setHandler(&detector);
	detector.setGestureHandler(&handler);

	Gesture ffuGesture{ FourFingersUpGestureRecognizer(), FourFingersUpGesturePerformer() };
	Gesture ffdGesture{ FourFingersDownGestureRecognizer(), FourFingersDownGesturePerformer() };
	Gesture fflGesture{ FourFingersLeftGestureRecognizer(), FourFingersLeftGesturePerformer() };
	Gesture ffrGesture{ FourFingersRightGestureRecognizer(), FourFingersRightGesturePerformer() };
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
	//touchpad.acquire(true);

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

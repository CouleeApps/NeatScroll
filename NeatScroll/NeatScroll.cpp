#include "stdafx.h"
#include <functional>
#include "Touchpad.hpp"
#include "SynapticsTouchpad.hpp"
#include "GestureDetector.hpp"
#include "GestureHandler.hpp"
#include "FourFingersUpGesture.h"
#include "WinTabDetector.h"
#include <thread>

int main(int argc, const char **argv) {
	using namespace std::placeholders;

	SynapticsTouchpad touchpad;
	GestureDetector detector(touchpad);
	GestureHandler handler;
	touchpad.setHandler(&detector);
	detector.setGestureHandler(&handler);

	Gesture ffuGesture{ FourFingersUpGestureRecognizer(), FourFingersUpGesturePerformer() };
	handler.addGesture(&ffuGesture);

	if (!touchpad.connect()) {
		fprintf(stderr, "Could not connect to touchpad\n");
		return EXIT_FAILURE;
	}

	WinTabDetector::start();

	//To disable the system using this, uncomment this line.
	// Just make sure you have a mouse nearby in case the program crashes
	//touchpad.acquire(true);

	while (true) {
		if (!touchpad.poll()) {
			break;
		}
		WinTabDetector::update();
		//Performance
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	if (!touchpad.disconnect()) {
		fprintf(stderr, "Error disconnecting touchpad\n");
		return EXIT_FAILURE;
	}

	WinTabDetector::stop();

	return EXIT_SUCCESS;
}

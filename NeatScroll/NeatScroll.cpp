#include "stdafx.h"
#include <functional>
#include "Touchpad.hpp"
#include "SynapticsTouchpad.hpp"
#include "GestureRecognizer.hpp"

int main(int argc, const char **argv) {
	using namespace std::placeholders;

	SynapticsTouchpad touchpad;
	GestureRecognizer movement(touchpad);
	touchpad.setHandler(&movement);

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
		Sleep(10);
	}

	if (!touchpad.disconnect()) {
		fprintf(stderr, "Error disconnecting touchpad\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
#include "stdafx.h"
#include <conio.h>
#include <functional>
#include "TouchpadManager.hpp"
#include "MovementManager.hpp"

int main(int argc, const char **argv) {
	using namespace std::placeholders;

	TouchpadManager touchpad;

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
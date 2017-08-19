#include "stdafx.h"
#include <conio.h>
#include "TouchpadManager.hpp"

int main(int argc, const char **argv) {
	TouchpadManager touchpad([](const std::vector<TouchpadManager::TouchPoint> &points) {
		for (const auto &tp : points) {
			printf("%u %f %f %f %i\n", tp.timestamp, tp.origin.x, tp.origin.y, tp.size, tp.palm);
		}
	});

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
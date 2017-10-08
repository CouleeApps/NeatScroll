#include "stdafx.h"
#include "MovementManager.hpp"
#include "bezier.h"

MovementManager::MovementManager(Touchpad &touchpad) : mTouchpad(touchpad) {
}

MovementManager::~MovementManager() {
}

void MovementManager::update(const std::vector<Touchpad::TouchPoint> &points) {
	for (const auto &point : points) {
		printf("%5i %5i %5i ", point.origin.x, point.origin.y, point.origin.z);
	}
	for (int i = 0; i < 5; i++) {
		printf("                  ");
	}
	printf("\r");

	switch (points.size()) {
	case 1:
		break;
	case 4: {

		break;
	}
	default:
		break;
	}

}
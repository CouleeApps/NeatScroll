#pragma once
#include "Touchpad.hpp"
#include <list>

class MovementManager {
	Touchpad &mTouchpad;

public:
	MovementManager(Touchpad &touchpad);
	~MovementManager();

	void update(const std::vector<Touchpad::TouchPoint> &points);
};


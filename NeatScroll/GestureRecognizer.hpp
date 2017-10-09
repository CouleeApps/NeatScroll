#pragma once
#include "Touchpad.hpp"
#include <unordered_map>
#include "Gesture.h"

class GestureRecognizer {
public:
	GestureRecognizer(Touchpad &touchpad);
	~GestureRecognizer();

	void update(const std::vector<Touchpad::TouchPoint> &points);
private:
	Touchpad &mTouchpad;
	Gesture mGesture;
	bool mGestureActive;
	float mGestureThreshold;

	void touchStart(const std::vector<Touchpad::TouchPoint> &points);
	void touchStop(const std::vector<Touchpad::TouchPoint> &points);
	void touchMove(const std::vector<Touchpad::TouchPoint> &points);
};


#pragma once
#include "Touchpad.hpp"
#include <unordered_map>
#include "Gesture.h"

class GestureHandler {
public:
	virtual void onGestureStart(const Gesture &gesture) = 0;
	virtual void onGestureMove(const Gesture &gesture) = 0;
	virtual void onGestureStop(const Gesture &gesture) = 0;
};

class GestureRecognizer : public TouchpadUpdateHandler {
public:
	GestureRecognizer(Touchpad &touchpad);
	~GestureRecognizer();

	void setGestureHandler(GestureHandler *handler) { mHandler = handler; }
	virtual void update(const std::vector<Touchpad::TouchPoint> &points) override;
private:
	Touchpad &mTouchpad;
	Gesture mGesture;
	bool mGestureActive;
	float mGestureThreshold;
	GestureHandler *mHandler;

	void touchStart(const std::vector<Touchpad::TouchPoint> &points);
	void touchStop(const std::vector<Touchpad::TouchPoint> &points);
	void touchMove(const std::vector<Touchpad::TouchPoint> &points);
};


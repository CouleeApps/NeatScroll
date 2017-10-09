#pragma once
#include "Touchpad.hpp"
#include <unordered_map>
#include "Gesture.h"

class GestureUpdateHandler {
public:
	virtual void onGestureStart(const Gesture &gesture) = 0;
	virtual void onGestureMove(const Gesture &gesture) = 0;
	virtual void onGestureStop(const Gesture &gesture) = 0;
};

class GestureDetector : public TouchpadUpdateHandler {
public:
	GestureDetector(Touchpad &touchpad);
	~GestureDetector();

	void setGestureHandler(GestureUpdateHandler *handler) { mHandler = handler; }
	virtual void update(const std::vector<Touchpad::TouchPoint> &points) override;
private:
	Touchpad &mTouchpad;
	Gesture mGesture;
	bool mGestureActive;
	float mGestureThreshold;
	GestureUpdateHandler *mHandler;

	void touchStart(const std::vector<Touchpad::TouchPoint> &points);
	void touchStop(const std::vector<Touchpad::TouchPoint> &points);
	void touchMove(const std::vector<Touchpad::TouchPoint> &points);
};


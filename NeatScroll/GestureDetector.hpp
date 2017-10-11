#pragma once
#include "Touchpad.hpp"
#include <unordered_map>
#include "Movement.h"

class GestureUpdateHandler {
public:
	virtual void onMovementStart(const Movement &movement) = 0;
	virtual void onMovementMove(const Movement &movement) = 0;
	virtual void onMovementStop(const Movement &movement) = 0;
};

class GestureDetector : public TouchpadUpdateHandler {
public:
	GestureDetector(Touchpad &touchpad);
	~GestureDetector();

	void setGestureHandler(GestureUpdateHandler *handler) { mHandler = handler; }
	virtual void update(const std::vector<Touchpad::TouchPoint> &points) override;
private:
	Touchpad &mTouchpad;
	Movement mMovement;
	bool mGestureActive;
	bool mMetThreshold;
	float mGestureThreshold;
	GestureUpdateHandler *mHandler;

	void touchStart(const std::vector<Touchpad::TouchPoint> &points);
	void touchStop(const std::vector<Touchpad::TouchPoint> &points);
	void touchMove(const std::vector<Touchpad::TouchPoint> &points);
};


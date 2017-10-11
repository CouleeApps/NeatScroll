#pragma once
#include "Touchpad.hpp"
#include <unordered_map>
#include "Movement.h"

class GestureDetector {
public:
	virtual void onMovementStart(const Movement &movement) = 0;
	virtual void onMovementMove(const Movement &movement) = 0;
	virtual void onMovementStop(const Movement &movement) = 0;
};

class MovementDetector : public TouchpadUpdateHandler {
public:
	MovementDetector(Touchpad &touchpad);
	~MovementDetector();

	void setGestureHandler(GestureDetector *handler) { mHandler = handler; }
	virtual void update(const std::vector<Touchpad::TouchPoint> &points) override;
private:
	Touchpad &mTouchpad;
	Movement mMovement;
	bool mGestureActive;
	bool mMetThreshold;
	float mGestureThreshold;
	GestureDetector *mHandler;

	void touchStart(const std::vector<Touchpad::TouchPoint> &points);
	void touchStop(const std::vector<Touchpad::TouchPoint> &points);
	void touchMove(const std::vector<Touchpad::TouchPoint> &points);
};


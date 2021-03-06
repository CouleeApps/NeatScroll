#include "stdafx.h"
#include "MovementDetector.hpp"
#include "Bezier.hpp"

MovementDetector::MovementDetector(Touchpad &touchpad) : mTouchpad(touchpad) {
	mGestureActive = false;
	mGestureThreshold = 50.f;
}

MovementDetector::~MovementDetector() {
}

void MovementDetector::update(const std::vector<Touchpad::TouchPoint> &points) {
	if (points.size() > 0) {
		//Start a gesture if we've stopped
		if (!mGestureActive) {
			touchStart(points);
		}
		//If we change fingers finish the current one and start new
		if (mMovement.mPointCount != points.size()) {
			//Reset gesture and make a new one
			touchStop(points);

			//Changing # of fingers down often causes inadvertant gestures
			if (mMovement.mPointCount > points.size()) {
				mGestureThreshold = 200.f;
			}
			touchStart(points);
		} else if (mMetThreshold) {
			//Changing # of fingers often causes inadvertant gestures
			if (mMovement.mPointCount > points.size()) {
				mGestureThreshold = 200.f;
			}
		}
		//Update current gesture
		touchMove(points);
	} else {
		//Stop anything we're currently doing
		if (mGestureActive) {
			touchStop(points);
		}
		//Hands off, become more sensitive
		mGestureThreshold = 50.0f;
	}
}

void MovementDetector::touchStart(const std::vector<Touchpad::TouchPoint> &points) {
	//Gesture is not actually recognized as "starting" here, this simply starts detecting updates
	mGestureActive = true;
	//Reset current gesture
	mMovement.mPointCount = static_cast<int>(points.size());
	mMovement.mStartPoints = points;
	mMetThreshold = false;
}

void MovementDetector::touchStop(const std::vector<Touchpad::TouchPoint> &points) {
	if (!mGestureActive) {
		return;
	}
	mGestureActive = false;

	//Don't care if we haven't started
	if (!mMetThreshold) {
		return;
	}

	//On gesture finish
	if (mHandler) {
		mHandler->onMovementStop(mMovement);
	}
}

void MovementDetector::touchMove(const std::vector<Touchpad::TouchPoint> &points) {
	if (!mGestureActive) {
		return;
	}

	//Update the current gesture's state
	mMovement.mPoints = points;

	//Check average distance moved by all fingers. If this meets the threshold then
	// we can say a gesture has started.

	//TODO: Is this better or worse than 'if any finger meets the threshold'?
	glm::vec3 avgDelta = mMovement.getAverageDelta();

	//If we haven't started yet, check to see if we meet the threshold.
	if (!mMetThreshold) {
		if (glm::length(avgDelta) > mGestureThreshold) {
			mMetThreshold = true;
			//On gesture start
			if (mHandler) {
				mHandler->onMovementStart(mMovement);
			}
		} else {
			//Can't say we've updated if we haven't started
			return;
		}
	}

	//On gesture update
	if (mHandler) {
		mHandler->onMovementMove(mMovement);
	}
}

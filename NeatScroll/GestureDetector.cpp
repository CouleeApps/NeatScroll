#include "stdafx.h"
#include "GestureDetector.hpp"
#include "bezier.h"

GestureDetector::GestureDetector(Touchpad &touchpad) : mTouchpad(touchpad) {
	mGestureActive = false;
	mGestureThreshold = 50.f;
}

GestureDetector::~GestureDetector() {
}

void GestureDetector::update(const std::vector<Touchpad::TouchPoint> &points) {
	if (points.size() > 0) {
		//Start a gesture if we've stopped
		if (!mGestureActive) {
			touchStart(points);
		}
		//If we change fingers finish the current one and start new
		if (mGesture.mPointCount != points.size()) {
			//Reset gesture and make a new one
			touchStop(points);

			//Changing # of fingers down often causes inadvertant gestures
			if (mGesture.mPointCount > points.size()) {
				mGestureThreshold = 200.f;
			}
			touchStart(points);
		} else if (mGesture.mMetThreshold) {
			//Changing # of fingers often causes inadvertant gestures
			if (mGesture.mPointCount > points.size()) {
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

void GestureDetector::touchStart(const std::vector<Touchpad::TouchPoint> &points) {
	//Gesture is not actually recognized as "starting" here, this simply starts detecting updates
	mGestureActive = true;
	//Reset current gesture
	mGesture.mPointCount = static_cast<int>(points.size());
	mGesture.mStartPoints = points;
	mGesture.mMetThreshold = false;
}

void GestureDetector::touchStop(const std::vector<Touchpad::TouchPoint> &points) {
	if (!mGestureActive) {
		return;
	}
	mGestureActive = false;

	//Don't care if we haven't started
	if (!mGesture.mMetThreshold) {
		return;
	}

	//On gesture finish
	if (mHandler) {
		mHandler->onMovementStop(mGesture);
	}
}

void GestureDetector::touchMove(const std::vector<Touchpad::TouchPoint> &points) {
	if (!mGestureActive) {
		return;
	}

	//Update the current gesture's state
	mGesture.mPoints = points;

	//Check average distance moved by all fingers. If this meets the threshold then
	// we can say a gesture has started.

	//TODO: Is this better or worse than 'if any finger meets the threshold'?
	std::vector<glm::lvec3> deltas = mGesture.getDeltas();
	glm::vec3 avgDelta;
	for (const glm::lvec3 &delta : deltas) {
		avgDelta += glm::vec3(delta);
	}
	avgDelta /= (float)mGesture.mPointCount;

	//If we haven't started yet, check to see if we meet the threshold.
	if (!mGesture.mMetThreshold) {
		if (glm::length(avgDelta) > mGestureThreshold) {
			mGesture.mMetThreshold = true;
			//On gesture start
			if (mHandler) {
				mHandler->onMovementStart(mGesture);
			}
		} else {
			//Can't say we've updated if we haven't started
			return;
		}
	}

	//On gesture update
	if (mHandler) {
		mHandler->onMovementMove(mGesture);
	}
}

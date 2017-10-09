#include "stdafx.h"
#include "GestureRecognizer.hpp"
#include "bezier.h"

GestureRecognizer::GestureRecognizer(Touchpad &touchpad) : mTouchpad(touchpad) {
	mGestureActive = false;
	mGestureThreshold = 50.f;
}

GestureRecognizer::~GestureRecognizer() {
}

void GestureRecognizer::update(const std::vector<Touchpad::TouchPoint> &points) {
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

void GestureRecognizer::touchStart(const std::vector<Touchpad::TouchPoint> &points) {
	//Gesture is not actually recognized as "starting" here, this simply starts detecting updates
	mGesture.mPointCount = points.size();
	mGesture.mStartPoints = points;
	mGesture.mMetThreshold = false;
	mGestureActive = true;
}

void GestureRecognizer::touchStop(const std::vector<Touchpad::TouchPoint> &points) {
	if (!mGestureActive) {
		return;
	}
	mGestureActive = false;

	if (!mGesture.mMetThreshold) {
		return;
	}

	//On gesture finish
	//printf("\n");
}

void GestureRecognizer::touchMove(const std::vector<Touchpad::TouchPoint> &points) {
	if (!mGestureActive) {
		return;
	}

	mGesture.mPoints = points;

	std::vector<glm::lvec3> deltas = mGesture.getDeltas();
	glm::vec3 avgDelta;
	for (const glm::lvec3 &delta : deltas) {
		avgDelta += glm::vec3(delta);
	}
	avgDelta /= (float)mGesture.mPointCount;

	if (!mGesture.mMetThreshold) {
		if (glm::length(avgDelta) > mGestureThreshold) {
			mGesture.mMetThreshold = true;
			//On gesture start
		} else {
			return;
		}

	}

	//On gesture update
	//printf("%d finger gesture delta %8g %8g %8g\r", mGesture.mPointCount, avgDelta.x, avgDelta.y, avgDelta.z);
}

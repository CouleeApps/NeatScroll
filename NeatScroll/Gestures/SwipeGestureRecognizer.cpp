//
// Created by glennsmith on 12/17/2017.
//

#include "stdafx.h"
#include "SwipeGestureRecognizer.h"

bool SwipeGestureRecognizer::onMovementStart(const Movement &movement) {
	if (movement.mPointCount != mFingerCount) {
		return false;
	}

	mHistory.clear();
	mTimer->start();
	return onMovementMove(movement);
}

bool SwipeGestureRecognizer::onMovementMove(const Movement &movement) {
	if (movement.mPointCount != mFingerCount) {
		return false;
	}

	//Get current timer info
	Timer::TickType elapsed = mTimer->getTickCount();
	Timer::TickType frequency = mTimer->getTicksPerSecond();

	//Prune any history older than elapsed - timeout
	Timer::TickType latestWithin = elapsed - static_cast<Timer::TickType>(static_cast<float>(frequency) * mTimeout);
	for (auto it = mHistory.cbegin(); it != mHistory.cend(); ) {
		if (it->first < latestWithin) {
			//Too old, remove
			it = mHistory.erase(it);
		} else {
			++it;
		}
	}
	//New history
	mHistory.emplace_back(elapsed, movement);

	glm::vec3 delta = Movement::getAverageRelativeDelta(mHistory[0].second.mPoints, movement.mPoints);
	switch (mDirection) {
		case Up:
			return delta.y > mThreshold;
		case Left:
			return delta.x < -mThreshold;
		case Down:
			return delta.y < -mThreshold;
		case Right:
			return delta.x > mThreshold;
	}
	return false;
}

bool SwipeGestureRecognizer::onMovementStop(const Movement &movement) {
	if (movement.mPointCount != mFingerCount) {
		return false;
	}

	mHistory.clear();
	return onMovementMove(movement);
}

//
// Created by glennsmith on 12/17/2017.
//

#include "stdafx.h"
#include "SwipeGestureRecognizer.h"

bool SwipeGestureRecognizer::onMovementStart(const Movement &movement) {
	return false;
}

bool SwipeGestureRecognizer::onMovementMove(const Movement &movement) {
	if (movement.mPointCount != mFingerCount) {
		return false;
	}

	switch (mDirection) {
		case Up:
			return movement.getAverageRelativeDelta().y > mThreshold;
		case Left:
			return movement.getAverageRelativeDelta().x < -mThreshold;
		case Down:
			return movement.getAverageRelativeDelta().y < -mThreshold;
		case Right:
			return movement.getAverageRelativeDelta().x > mThreshold;
	}
	return false;
}

bool SwipeGestureRecognizer::onMovementStop(const Movement &movement) {
	return onMovementMove(movement);
}

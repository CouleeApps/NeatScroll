#include "../stdafx.h"
#include "FourFingersRightGesture.h"

bool FourFingersRightGestureRecognizer::onMovementStart(const Movement &movement) {
	return false;
}

bool FourFingersRightGestureRecognizer::onMovementMove(const Movement &movement) {
	if (movement.mPointCount != 4) {
		return false;
	}

	//See if all fingers on the gesture moved up by ~2/10 the scale
	return movement.getAverageRelativeDelta().x > 0.2f;
}

bool FourFingersRightGestureRecognizer::onMovementStop(const Movement &movement) {
	return onMovementMove(movement);
}

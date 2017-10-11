#include "../stdafx.h"
#include "FourFingersLeftGesture.h"

bool FourFingersLeftGestureRecognizer::onMovementStart(const Movement &movement) {
	return false;
}

bool FourFingersLeftGestureRecognizer::onMovementMove(const Movement &movement) {
	if (movement.mPointCount != 4) {
		return false;
	}

	//See if all fingers on the gesture moved up by ~2/10 the scale
	return movement.getAverageRelativeDelta().x < -0.2f;
}

bool FourFingersLeftGestureRecognizer::onMovementStop(const Movement &movement) {
	return onMovementMove(movement);
}


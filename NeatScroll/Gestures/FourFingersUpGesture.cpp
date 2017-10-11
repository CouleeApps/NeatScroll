#include "../stdafx.h"
#include "FourFingersUpGesture.h"

bool FourFingersUpGestureRecognizer::onMovementStart(const Movement &movement) {
	return false;
}

bool FourFingersUpGestureRecognizer::onMovementMove(const Movement &movement) {
	if (movement.mPointCount != 4) {
		return false;
	}

	//See if all fingers on the gesture moved up by ~2/10 the scale
	if (movement.getAverageRelativeDelta().y < 0.2f) {
		return false;
	}
	return true;
}

bool FourFingersUpGestureRecognizer::onMovementStop(const Movement &movement) {
	return onMovementMove(movement);
}

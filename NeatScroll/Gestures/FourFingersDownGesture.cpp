#include "../stdafx.h"
#include "FourFingersDownGesture.h"

bool FourFingersDownGestureRecognizer::onMovementStart(const Movement &movement) {
	return false;
}

bool FourFingersDownGestureRecognizer::onMovementMove(const Movement &movement) {
	if (movement.mPointCount != 4) {
		return false;
	}

	//See if all fingers on the gesture moved up by ~2/10 the scale
	if (movement.getAverageRelativeDelta().y > -0.2f) {
		return false;
	}
	return true;
}

bool FourFingersDownGestureRecognizer::onMovementStop(const Movement &movement) {
	return onMovementMove(movement);
}

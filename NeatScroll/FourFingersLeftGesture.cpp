#include "stdafx.h"
#include "FourFingersLeftGesture.h"
#include <Windows.h>

bool FourFingersLeftGestureRecognizer::onMovementStart(const Movement &movement) {
	return false;
}

bool FourFingersLeftGestureRecognizer::onMovementMove(const Movement &movement) {
	if (movement.mPointCount != 4) {
		return false;
	}

	//See if all fingers on the gesture moved up by ~3/10 the scale
	float avgSide = 0;
	for (int i = 0; i < movement.mPointCount; i++) {
		glm::lvec3 scale = movement.mPoints[0].scale;
		glm::vec3 delta = glm::vec3(movement.mPoints[i].origin - movement.mStartPoints[i].origin);
		avgSide += delta.x /= scale.x;
	}
	return avgSide < -0.3f;
}

bool FourFingersLeftGestureRecognizer::onMovementStop(const Movement &movement) {
	return onMovementMove(movement);
}

void FourFingersLeftGesturePerformer::onGestureStart(const Movement &movement) {
	INPUT winDown = { 0 };
	winDown.type = INPUT_KEYBOARD;
	winDown.ki.wVk = VK_LWIN;
	INPUT ctrlDown = { 0 };
	ctrlDown.type = INPUT_KEYBOARD;
	ctrlDown.ki.wVk = VK_LCONTROL;
	INPUT leftDown = { 0 };
	leftDown.type = INPUT_KEYBOARD;
	leftDown.ki.wVk = VK_LEFT;
	INPUT downs[3] = { winDown, ctrlDown, leftDown };
	SendInput(3, downs, sizeof(INPUT));

	INPUT leftUp = { 0 };
	leftUp.type = INPUT_KEYBOARD;
	leftUp.ki.wVk = VK_LEFT;
	leftUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ctrlUp = { 0 };
	ctrlUp.type = INPUT_KEYBOARD;
	ctrlUp.ki.wVk = VK_LCONTROL;
	ctrlUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT winUp = { 0 };
	winUp.type = INPUT_KEYBOARD;
	winUp.ki.wVk = VK_LWIN;
	winUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ups[3] = { leftUp, ctrlUp, winUp };
	SendInput(3, ups, sizeof(INPUT));
}

void FourFingersLeftGesturePerformer::onGestureMove(const Movement &movement) {
}

void FourFingersLeftGesturePerformer::onGestureStop(const Movement &movement) {
}

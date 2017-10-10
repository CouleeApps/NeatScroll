#include "stdafx.h"
#include "FourFingersRightGesture.h"
#include <Windows.h>

bool FourFingersRightGestureRecognizer::onMovementStart(const Movement &movement) {
	return false;
}

bool FourFingersRightGestureRecognizer::onMovementMove(const Movement &movement) {
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
	return avgSide > 0.3f;
}

bool FourFingersRightGestureRecognizer::onMovementStop(const Movement &movement) {
	return onMovementMove(movement);
}

void FourFingersRightGesturePerformer::onGestureStart(const Movement &movement) {
	INPUT winDown = { 0 };
	winDown.type = INPUT_KEYBOARD;
	winDown.ki.wVk = VK_LWIN;
	INPUT ctrlDown = { 0 };
	ctrlDown.type = INPUT_KEYBOARD;
	ctrlDown.ki.wVk = VK_LCONTROL;
	INPUT rightDown = { 0 };
	rightDown.type = INPUT_KEYBOARD;
	rightDown.ki.wVk = VK_RIGHT;
	INPUT downs[3] = { winDown, ctrlDown, rightDown };
	SendInput(3, downs, sizeof(INPUT));

	INPUT rightUp = { 0 };
	rightUp.type = INPUT_KEYBOARD;
	rightUp.ki.wVk = VK_RIGHT;
	rightUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ctrlUp = { 0 };
	ctrlUp.type = INPUT_KEYBOARD;
	ctrlUp.ki.wVk = VK_LCONTROL;
	ctrlUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT winUp = { 0 };
	winUp.type = INPUT_KEYBOARD;
	winUp.ki.wVk = VK_LWIN;
	winUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ups[3] = { rightUp, ctrlUp, winUp };
	SendInput(3, ups, sizeof(INPUT));
}

void FourFingersRightGesturePerformer::onGestureMove(const Movement &movement) {
}

void FourFingersRightGesturePerformer::onGestureStop(const Movement &movement) {
}

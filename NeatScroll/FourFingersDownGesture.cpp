#include "stdafx.h"
#include "FourFingersDownGesture.h"
#include <Windows.h>
#include "TaskViewDetector.h"

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
	if (!TaskViewDetector::isTaskView()) {
		return false;
	}
	return true;
}

bool FourFingersDownGestureRecognizer::onMovementStop(const Movement &movement) {
	return onMovementMove(movement);
}

void FourFingersDownGesturePerformer::onGestureStart(const Movement &movement) {
	INPUT winDown = { 0 };
	winDown.type = INPUT_KEYBOARD;
	winDown.ki.wVk = VK_LWIN;
	INPUT tabDown = { 0 };
	tabDown.type = INPUT_KEYBOARD;
	tabDown.ki.wVk = VK_TAB;
	INPUT downs[2] = { winDown, tabDown };
	SendInput(2, downs, sizeof(INPUT));

	INPUT tabUp = { 0 };
	tabUp.type = INPUT_KEYBOARD;
	tabUp.ki.wVk = VK_TAB;
	tabUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT winUp = { 0 };
	winUp.type = INPUT_KEYBOARD;
	winUp.ki.wVk = VK_LWIN;
	winUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ups[2] = { tabUp, winUp };
	SendInput(2, ups, sizeof(INPUT));
}

void FourFingersDownGesturePerformer::onGestureMove(const Movement &movement) {
}

void FourFingersDownGesturePerformer::onGestureStop(const Movement &movement) {
}

#include "../stdafx.h"
#include "TaskViewClosePerformer.h"
#include "../TaskViewDetector.h"
#include <Windows.h>

bool TaskViewClosePerformer::onGestureStart(const Movement &movement) {
	if (!TaskViewDetector::isTaskView()) {
		return false;
	}
	INPUT winDown = {0 };
	winDown.type = INPUT_KEYBOARD;
	winDown.ki.wVk = VK_LWIN;
	INPUT tabDown = {0 };
	tabDown.type = INPUT_KEYBOARD;
	tabDown.ki.wVk = VK_TAB;
	INPUT downs[2] = {winDown, tabDown };
	SendInput(2, downs, sizeof(INPUT));

	INPUT tabUp = {0 };
	tabUp.type = INPUT_KEYBOARD;
	tabUp.ki.wVk = VK_TAB;
	tabUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT winUp = {0 };
	winUp.type = INPUT_KEYBOARD;
	winUp.ki.wVk = VK_LWIN;
	winUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ups[2] = {tabUp, winUp };
	SendInput(2, ups, sizeof(INPUT));
	return true;
}

bool TaskViewClosePerformer::onGestureMove(const Movement &movement) {
	return true;
}

bool TaskViewClosePerformer::onGestureStop(const Movement &movement) {
	return true;
}
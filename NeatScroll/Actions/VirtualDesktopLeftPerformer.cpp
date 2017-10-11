#include "../stdafx.h"
#include "VirtualDesktopLeftPerformer.h"
#include <Windows.h>

bool VirtualDesktopLeftPerformer::onGestureStart(const Movement &movement) {
	INPUT winDown = {0 };
	winDown.type = INPUT_KEYBOARD;
	winDown.ki.wVk = VK_LWIN;
	INPUT ctrlDown = {0 };
	ctrlDown.type = INPUT_KEYBOARD;
	ctrlDown.ki.wVk = VK_LCONTROL;
	INPUT leftDown = {0 };
	leftDown.type = INPUT_KEYBOARD;
	leftDown.ki.wVk = VK_LEFT;
	INPUT downs[3] = {winDown, ctrlDown, leftDown };
	SendInput(3, downs, sizeof(INPUT));

	INPUT leftUp = {0 };
	leftUp.type = INPUT_KEYBOARD;
	leftUp.ki.wVk = VK_LEFT;
	leftUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ctrlUp = {0 };
	ctrlUp.type = INPUT_KEYBOARD;
	ctrlUp.ki.wVk = VK_LCONTROL;
	ctrlUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT winUp = {0 };
	winUp.type = INPUT_KEYBOARD;
	winUp.ki.wVk = VK_LWIN;
	winUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ups[3] = {leftUp, ctrlUp, winUp };
	SendInput(3, ups, sizeof(INPUT));
	return true;
}

bool VirtualDesktopLeftPerformer::onGestureMove(const Movement &movement) {
	return true;
}

bool VirtualDesktopLeftPerformer::onGestureStop(const Movement &movement) {
	return true;
}
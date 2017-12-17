#include "stdafx.h"
#include "VirtualDesktopRightPerformer.h"
#include <Windows.h>

bool VirtualDesktopRightPerformer::onGestureStart(const Movement &movement) {
	INPUT winDown = {0 };
	winDown.type = INPUT_KEYBOARD;
	winDown.ki.wVk = VK_LWIN;
	INPUT ctrlDown = {0 };
	ctrlDown.type = INPUT_KEYBOARD;
	ctrlDown.ki.wVk = VK_LCONTROL;
	INPUT rightDown = {0 };
	rightDown.type = INPUT_KEYBOARD;
	rightDown.ki.wVk = VK_RIGHT;
	INPUT downs[3] = {winDown, ctrlDown, rightDown };
	SendInput(3, downs, sizeof(INPUT));

	INPUT rightUp = {0 };
	rightUp.type = INPUT_KEYBOARD;
	rightUp.ki.wVk = VK_RIGHT;
	rightUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ctrlUp = {0 };
	ctrlUp.type = INPUT_KEYBOARD;
	ctrlUp.ki.wVk = VK_LCONTROL;
	ctrlUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT winUp = {0 };
	winUp.type = INPUT_KEYBOARD;
	winUp.ki.wVk = VK_LWIN;
	winUp.ki.dwFlags = KEYEVENTF_KEYUP;
	INPUT ups[3] = {rightUp, ctrlUp, winUp };
	SendInput(3, ups, sizeof(INPUT));
	return true;
}

bool VirtualDesktopRightPerformer::onGestureMove(const Movement &movement) {
	return true;
}

bool VirtualDesktopRightPerformer::onGestureStop(const Movement &movement) {
	return true;
}
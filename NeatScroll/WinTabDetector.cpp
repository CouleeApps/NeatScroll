#include "stdafx.h"
#include "WinTabDetector.h"
#include <Windows.h>

HHOOK WinTabDetector::mKeyboardHook;
MSG WinTabDetector::mMsg;

bool WinTabDetector::mIsWinTab = false;
bool WinTabDetector::mWinDown = false;

LRESULT WinTabDetector::LowLevelKeyboardProc(int code, WPARAM wparam, LPARAM lparam) {
	KBDLLHOOKSTRUCT& kllhs = *(KBDLLHOOKSTRUCT*)lparam;

	if (code == HC_ACTION) {
		switch (wparam) {
		case WM_KEYDOWN:
			switch (kllhs.vkCode) {
			case VK_TAB:
				if ((GetAsyncKeyState(VK_LWIN) < 0 || GetAsyncKeyState(VK_RWIN) < 0)) {
					if (mIsWinTab) {
						mIsWinTab = false;
						mWinDown = false;
					} else {
						mIsWinTab = true;
						mWinDown = true;
					}
				}
				break;
			case VK_ESCAPE:
			case VK_RETURN:
			case VK_SPACE:
				if (mIsWinTab) {
					mIsWinTab = false;
				}
				break;
			}
			break;
		case WM_KEYUP:
			switch (kllhs.vkCode) {
			case VK_LWIN:
			case VK_RWIN:
				if (mWinDown) {
					mWinDown = false;
					break;
				}
				if (mIsWinTab) {
					mIsWinTab = false;
				}
				break;
			}
			break;
		}
	}
	return CallNextHookEx(0, code, wparam, lparam);
}

void WinTabDetector::start() {
	mKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, &LowLevelKeyboardProc, NULL, 0);
}

void WinTabDetector::stop() {
	UnhookWindowsHookEx(mKeyboardHook);
}

void WinTabDetector::update() {
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

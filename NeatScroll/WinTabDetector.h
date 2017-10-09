#pragma once

#include <Windows.h>

class WinTabDetector {
public:
	static void start();
	static void stop();
	static void update();

	static bool isWinTab() { return mIsWinTab; }
private:
	static bool mIsWinTab;
	static bool mWinDown;
	static HHOOK mKeyboardHook;
	static MSG mMsg;
	static LRESULT LowLevelKeyboardProc(int code, WPARAM wparam, LPARAM lparam);
};


#include "stdafx.h"
#include "TaskViewDetector.h"
#include <Windows.h>
#include <string>
#include <chrono>

bool foundShell = false;

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam) {
	TCHAR buffer[1024];
	memset(buffer, 0, 1024 * sizeof(TCHAR));
	int wClass = GetClassName(hWnd, buffer, 1024);
#ifdef UNICODE
	std::wstring windowClass = std::wstring(buffer);
	foundShell = (windowClass == L"Shell_TrayWnd");
#else
	std::string windowClass = std::string(buffer);
	foundShell = (windowClass == "Shell_TrayWnd");
#endif

	//This window only exists as a child window when the Task View is closed
	if (foundShell) {
		return FALSE;
	}
	return TRUE;
}

bool TaskViewDetector::isTaskView() {
	static std::chrono::system_clock::time_point lastUpdate = std::chrono::system_clock::now();

	//This is slow so only update occasionally
	if ((std::chrono::system_clock::now() - lastUpdate) > std::chrono::milliseconds(50)) {
		lastUpdate = std::chrono::system_clock::now();
		foundShell = false;
		EnumChildWindows(GetDesktopWindow(), EnumChildProc, NULL);
	}
	return !foundShell;
}

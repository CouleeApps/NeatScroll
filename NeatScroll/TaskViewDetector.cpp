#include "stdafx.h"
#include "TaskViewDetector.h"
#include <Windows.h>
#include <string>
#include <chrono>

bool foundShell = false;

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam) {
	TCHAR *buffer = new TCHAR[1024];
	memset(buffer, 0, 1024 * sizeof(TCHAR));
	int wClass = GetClassName(hWnd, buffer, 1024);
	std::wstring windowClass = std::wstring(buffer);
	delete[] buffer;

	//This window only exists as a child window when the Task View is closed
	if (windowClass == L"Shell_TrayWnd") {
		foundShell = true;
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

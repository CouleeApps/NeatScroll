#include "stdafx.h"
#include "TaskViewDetector.h"
#include <Windows.h>
#include <string>

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
	foundShell = false;
	EnumChildWindows(GetDesktopWindow(), EnumChildProc, NULL);
	return !foundShell;
}

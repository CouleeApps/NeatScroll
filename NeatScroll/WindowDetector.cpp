//
// Created by glennsmith on 12/17/2017.
//

#include "stdafx.h"
#include "WindowDetector.h"
#include <Windows.h>

#if UNICODE
#include <locale>
#include <codecvt>
#else
#error This requires unicode! Build with -DUNICODE -D_UNICODE
#endif

WindowDetector::WindowDetector(const std::string &windowName) : mWindowName(windowName) {

}

bool WindowDetector::isWindowDetected() const {
	//Get the foreground window's name

	//https://stackoverflow.com/a/40921081/214063
	HWND fgWindow = GetForegroundWindow();

	//Get the name of the process
	TCHAR windowName[MAX_PATH] = L"";
	GetWindowText(fgWindow, windowName, MAX_PATH);
	std::wstring nameStr(windowName);

	//Convert wstring exe to string, https://stackoverflow.com/a/18374698/214063
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(nameStr).find(mWindowName) != std::wstring::npos;
}



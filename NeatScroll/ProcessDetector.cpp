//
// Created by glennsmith on 12/17/2017.
//

#include "stdafx.h"
#include "ProcessDetector.hpp"
#include <Windows.h>
#include <Psapi.h>

#if UNICODE
#include <locale>
#include <codecvt>
#else
#error This requires unicode! Build with -DUNICODE -D_UNICODE
#endif

ProcessDetector::ProcessDetector(const std::string &procName) : mProcName(procName) {

}

bool ProcessDetector::isProcessDetected() const {
	//Get the foreground window's process name

	//https://stackoverflow.com/a/40921081/214063
	HWND fgWindow = GetForegroundWindow();

	//Get thread and pid from the foreground window
	DWORD processId;
	GetWindowThreadProcessId(fgWindow, &processId);
	//Get process info from the window
	DWORD desiredAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
	bool inheritHandle = false;
	HANDLE process = OpenProcess(desiredAccess, inheritHandle, processId);
	if (INVALID_HANDLE_VALUE == process) {
		return false;
	}

	//Get the name of the process
	TCHAR modFilename[MAX_PATH] = L"";
	GetProcessImageFileName(process, modFilename, MAX_PATH);
	CloseHandle(process);

	//And grab whatever's after the last \ for the proc exe
	std::wstring nameStr(modFilename);
	auto lastSlash = nameStr.find_last_of('\\');
	if (lastSlash == std::wstring::npos) {
		return false;
	}
	std::wstring exe = nameStr.substr(lastSlash + 1);

	//Convert wstring exe to string, https://stackoverflow.com/a/18374698/214063
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(exe) == mProcName;
}



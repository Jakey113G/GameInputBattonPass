#pragma once
#include <windows.h>
#include <string>
#include <vector>

//Designed to only store one handle, not sure what to do if we have many valid handles
class HandleHelper
{
public:
	HandleHelper();

	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

	HWND FindHwnd(const char* nameOfWindow);
	HWND GetStoredHandle() const { return hWnd; }
private:
	HWND hWnd;

	//Static as it is used in a static call back - don't try to use this async
	static const char* s_WindowProcQueryString;
};

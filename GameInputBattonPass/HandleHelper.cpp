#include "HandleHelper.h"

const char* HandleHelper::s_WindowProcQueryString = "";

HandleHelper::HandleHelper()
{
	hWnd = NULL;
}

BOOL CALLBACK HandleHelper::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char buffer[128];
	int written = GetWindowTextA(hwnd, buffer, 128);
	if (written && strstr(buffer, s_WindowProcQueryString) != NULL) {
		*(HWND*)lParam = hwnd;
		return FALSE;
	}
	return TRUE;
}

HWND HandleHelper::FindHwnd(const char* nameOfWindow)
{
	s_WindowProcQueryString = nameOfWindow;
	BOOL result = EnumWindows(EnumWindowsProc, (LPARAM)&hWnd);
	return hWnd;
}

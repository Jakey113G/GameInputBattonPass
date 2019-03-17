#pragma once
#include <windows.h>

#include <thread>

#include "HandleHelper.h"
#include "InputChecker.h"
#include "ConfigOptions.h"

#include <iostream>

#define SW_MAXIMIZED 3

void FocusGameWindow(HWND windowHandle);
int main()
{
	HandleHelper windowFinder;
	InputChecker inputChecker;
	ConfigOptions options;

	std::cout << "Loading Window to priority focus to from file list" << std::endl;
	//Look through list for first match
	for (std::string const& windowName : options.m_WindowPriorityList)
	{
		if (windowFinder.FindHwnd(windowName.c_str()) != NULL)
		{
			break;
		}
	}

	std::cout << "We are ready to try to focus the window on game input..." << std::endl;
	//Program runs until closed, we thread sleep to reduce spam from every tick to every few milliseconds
	while (true)
	{
		inputChecker.UpdateInputStates();
		if (inputChecker.HasInputChanged())
		{
			if (GetHandleInformation(windowFinder.GetStoredHandle(), NULL) == FALSE)
			{
				//Try and find a window NOW, as the old one is not valid! Critical to have it now!
				for (std::string const& windowName : options.m_WindowPriorityList)
				{
					if (windowFinder.FindHwnd(windowName.c_str()) != NULL)
					{
						break;
					}
				}
			}

			FocusGameWindow(windowFinder.GetStoredHandle());
		}

		std::this_thread::sleep_for(options.m_PollTime);
	}
	return 0;
}

void FocusGameWindow(HWND windowHandle)
{
	if (windowHandle != NULL && 
		GetForegroundWindow() != windowHandle)
	{
		std::cout << "++ Changing focus to game window ++" << std::endl;
		ShowWindow(windowHandle, SW_MAXIMIZED);
		SetFocus(windowHandle);
		SendMessage(windowHandle, WM_SETFOCUS, 0, 0);
		SetForegroundWindow(windowHandle);
		SetActiveWindow(windowHandle);
	}
}
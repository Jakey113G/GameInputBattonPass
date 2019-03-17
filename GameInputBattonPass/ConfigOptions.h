#pragma once
#include <vector>
#include <string>

#include <chrono>

//Just a hard coded options class. Just wanted to store things that could be configured in future in a single location
struct ConfigOptions
{
	ConfigOptions();

	std::vector<std::string> m_WindowPriorityList;
	std::chrono::duration<double, std::milli> const m_PollTime;
};
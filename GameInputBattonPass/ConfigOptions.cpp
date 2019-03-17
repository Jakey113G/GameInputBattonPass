#include "ConfigOptions.h"

#include <fstream>
#include <string>

ConfigOptions::ConfigOptions() : m_PollTime(5.0f)
{
	std::ifstream file("WindowNamePriorityList.txt");
	std::string str;
	while (std::getline(file, str))
	{
		m_WindowPriorityList.push_back(str);
	}
}

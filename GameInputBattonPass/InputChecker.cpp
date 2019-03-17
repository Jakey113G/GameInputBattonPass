#include <windows.h>
#include "InputChecker.h"

InputChecker::InputChecker()
{
	memset(m_InputStates, 0, sizeof(InputState));
}

void InputChecker::UpdateInputStates()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		InputState& inputState = m_InputStates[i];

		DWORD previousPacketNumber = inputState.m_CurrentState.dwPacketNumber;
		dwResult = XInputGetState(i, &inputState.m_CurrentState);
		if (dwResult == ERROR_SUCCESS)
		{
			//Controller connected
			inputState.m_LastPacketNumber = previousPacketNumber;
			inputState.m_Connected = true;
		}
		else
		{
			//No controller
			m_InputStates[i].m_LastPacketNumber = 0;
			inputState.m_Connected = false;
		}
	}
}

bool InputChecker::HasInputChanged() const
{
	//we want to see if the packet number is different
	for (int i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (m_InputStates[i].m_Connected && 
			m_InputStates[i].m_LastPacketNumber != 0 &&
			m_InputStates[i].m_CurrentState.dwPacketNumber != m_InputStates[i].m_LastPacketNumber)
		{
			return true;
		}
	}
	return false;
}


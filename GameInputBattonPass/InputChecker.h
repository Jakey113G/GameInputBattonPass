#pragma once
#include <minwindef.h>
#include <Xinput.h>

struct InputState
{
	XINPUT_STATE m_CurrentState;
	DWORD m_LastPacketNumber;
	bool m_Connected;
};

class InputChecker
{
public:
	InputChecker();

	void UpdateInputStates();
	bool HasInputChanged() const;

	InputState m_InputStates[XUSER_MAX_COUNT];
};
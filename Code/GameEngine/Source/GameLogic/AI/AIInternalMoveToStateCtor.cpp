// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class StateMachine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);
	virtual ~State();

private:
	unsigned char m_head[0x20];
};

struct BFMEAIPosition
{
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

};

struct BFMEAIPathState
{
	float x;
	float y;
	float z;
	unsigned int ambientPlayingHandle;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		ambientPlayingHandle = 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, AsciiString name);

private:
	BFMEAIPosition m_goalPosition;
	BFMEAIPathState m_pathState;
	int m_goalLayer;
	unsigned int m_pathTimestamp;
	unsigned int m_blockedRepathTimestamp;
	bool m_adjustDestinations;
	bool m_waitingForPath;
	bool m_tryOneMoreRepath;
};

AIInternalMoveToState::AIInternalMoveToState(StateMachine *machine, AsciiString name) :
	State(machine, name)
{
	m_goalPosition.zero();
	m_pathState.zero();
	m_goalLayer = 1;
	m_pathTimestamp = 0;
	m_blockedRepathTimestamp = 0;
	m_adjustDestinations = true;
	m_waitingForPath = false;
	m_tryOneMoreRepath = false;
}

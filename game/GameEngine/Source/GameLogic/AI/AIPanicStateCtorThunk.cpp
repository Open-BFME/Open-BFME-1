// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class StateMachine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, AsciiString name);
};

extern int g_AIPanicStateVTable;

// upstream source: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
// The declared AIFollowWaypointPathState constructor is inline in the retail header;
// these fields model its portion of the derived object after inlining.
class AIPanicState : public AIInternalMoveToState
{
public:
	AIPanicState(StateMachine *machine);

private:
	int *volatile m_vftable;
	char m_baseFields[0x4C];
	volatile int m_groupOffsetX;
	volatile int m_groupOffsetY;
	volatile int m_angle;
	volatile int m_framesSleeping;
	volatile int m_currentWaypoint;
	volatile int m_priorWaypoint;
	volatile bool m_appendGoalPosition;
	volatile bool m_moveAsGroup;
	volatile bool m_isFollowWaypointPathState;
	volatile int m_waitFrames;
	volatile int m_timer;
};

// ??0AIPanicState@@QAE@PAVStateMachine@@@Z
AIPanicState::AIPanicState(StateMachine *machine) :
	AIInternalMoveToState(machine, "AIFollowWaypointPathState")
{
	m_groupOffsetX = 0;
	m_groupOffsetY = 0;
	m_angle = 0;
	m_framesSleeping = 0;
	m_currentWaypoint = 0;
	m_priorWaypoint = 0;
	m_appendGoalPosition = false;
	m_moveAsGroup = false;
	m_waitFrames = 0;
	m_timer = 0;
	m_isFollowWaypointPathState = true;
	m_vftable = &g_AIPanicStateVTable;
}

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x001720D0 installs 0x010985B0, AIIdleState's vtable: its name slot
// returns "AIIdleState", slot 6 is AIIdleState::update and slot 7 returns true.
// The face-state constructor at 0x00180320 also passes "AIIdleState", so the
// state name alone does not identify this class.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class StateMachine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State( StateMachine *machine, AsciiString name );

	virtual void stateAnchor();
};

// upstream source and layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIIdleState : public State
{
public:
	enum AIIdleTargetingType
	{
		LOOK_FOR_TARGETS,
		DO_NOT_LOOK_FOR_TARGETS
	};

	AIIdleState( StateMachine *machine, AIIdleTargetingType shouldLookForTargets );

private:
	char m_stateBaseTail[ 0x20 ];
	unsigned short m_initialSleepOffset;
	bool m_shouldLookForTargets;
	bool m_inited;
};

// upstream source: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
AIIdleState::AIIdleState( StateMachine *machine, AIIdleTargetingType shouldLookForTargets ) :
	State( machine, AsciiString( "AIIdleState" ) ),
	m_shouldLookForTargets( shouldLookForTargets == LOOK_FOR_TARGETS )
{
	m_inited = false;
	m_initialSleepOffset = 0xFFFF;
}

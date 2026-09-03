// cl: /DNDEBUG /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}
	StringBase<char> m_string;
};

class StateMachine;

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );
};

extern int g_AIFollowWaypointPathStateVTable;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIFollowWaypointPathState : public Rva0014F280StateBase
{
public:
	AIFollowWaypointPathState( StateMachine *machine, bool asGroup );

private:
	int *volatile m_vftable;
	char m_baseFields[ 0x4C ];
	volatile int m_groupOffsetX;
	volatile int m_groupOffsetY;
	volatile int m_angle;
	volatile int m_framesSleeping;
	volatile int m_currentWaypoint;
	volatile int m_priorWaypoint;
	volatile bool m_appendGoalPosition;
	volatile bool m_moveAsGroup;
	volatile bool m_isFollowWaypointPathState;
};

AIFollowWaypointPathState::AIFollowWaypointPathState( StateMachine *machine, bool asGroup )
	: Rva0014F280StateBase( machine, AsciiString( "AIFollowWaypointPathState" ) )
{
	bool savedAsGroup = asGroup;
	m_vftable = &g_AIFollowWaypointPathStateVTable;
	m_groupOffsetX = 0;
	m_groupOffsetY = 0;
	m_angle = 0;
	m_framesSleeping = 0;
	m_currentWaypoint = 0;
	m_priorWaypoint = 0;
	m_appendGoalPosition = false;
	m_moveAsGroup = savedAsGroup;
	m_isFollowWaypointPathState = true;
}

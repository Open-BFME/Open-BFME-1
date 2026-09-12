// cl: /DNDEBUG /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text ) : m_data( text ) {}
	StringBase<char> m_data;
};

class StateMachine;

class AIInternalMoveToState
{
public:
	AIInternalMoveToState( void *machine, AsciiString name );
};

extern int g_AIAttackFireDuringApproachStateVTable;

class AIAttackFireDuringApproachState : public AIInternalMoveToState
{
public:
	AIAttackFireDuringApproachState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_baseFields[ 0x4C ];
	volatile int m_field50;
	volatile int m_field54;
	volatile int m_field58;
	volatile int m_field5C;
	volatile int m_field60;
	volatile int m_field64;
	volatile int m_field68;
	volatile bool m_field6C;
};

AIAttackFireDuringApproachState::AIAttackFireDuringApproachState( StateMachine *machine )
	: AIInternalMoveToState( machine, AsciiString( "AIAttackFireDuringApproachState" ) )
{
	m_field50 = 0;
	m_vftable = &g_AIAttackFireDuringApproachStateVTable;
	m_field54 = 0;
	m_field58 = 0;
	m_field5C = 0;
	m_field60 = 0;
	m_field64 = 0;
	m_field68 = 0;
	m_field6C = false;
}

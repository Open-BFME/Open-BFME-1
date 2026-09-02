// cl: /DNDEBUG /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

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

extern int g_AIAttackFireDuringApproachStateVTable;

class AIAttackFireDuringApproachState : public Rva0014F280StateBase
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
	: Rva0014F280StateBase( machine, AsciiString( "AIAttackFireDuringApproachState" ) )
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

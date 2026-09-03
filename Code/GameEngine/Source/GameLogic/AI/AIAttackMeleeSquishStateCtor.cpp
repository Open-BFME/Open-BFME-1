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

extern int g_AIAttackMeleeSquishStateVTable;

class AIAttackMeleeSquishState : public Rva0014F280StateBase
{
public:
	AIAttackMeleeSquishState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_baseFields[ 0x4C ];
	volatile int m_targetId;
	volatile int m_startX;
	volatile int m_startY;
	volatile int m_startZ;
	volatile int m_goalX;
	volatile int m_goalY;
	volatile bool m_initialPass;
};

AIAttackMeleeSquishState::AIAttackMeleeSquishState( StateMachine *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIAttackMeleeSquishState" ) )
{
	m_targetId = 0;
	m_vftable = &g_AIAttackMeleeSquishStateVTable;
	m_startX = 0;
	m_startY = 0;
	m_startZ = 0;
	m_goalX = 0;
	m_goalY = 0;
	m_initialPass = true;
}

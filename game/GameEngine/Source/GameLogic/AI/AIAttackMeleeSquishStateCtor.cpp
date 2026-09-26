// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class StateMachine;

class AIInternalMoveToState
{
public:
	AIInternalMoveToState( void *machine, AsciiString name );
};

extern int g_AIAttackMeleeSquishStateVTable;

class AIAttackMeleeSquishState : public AIInternalMoveToState
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
	: AIInternalMoveToState( machine, AsciiString( "AIAttackMeleeSquishState" ) )
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

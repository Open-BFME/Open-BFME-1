// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class StateMachine;

class AIInternalMoveToState
{
public:
	AIInternalMoveToState( void *machine, AsciiString name );
};

extern int g_AIAttackMeleeHordeApproachTargetStateVTable;

class AIAttackMeleeHordeApproachTargetState : public AIInternalMoveToState
{
public:
	AIAttackMeleeHordeApproachTargetState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_baseFields[ 0x4C ];
	volatile int m_field50;
	volatile int m_field54;
	volatile int m_field58;
	volatile int m_field5C;
	volatile bool m_successOnPathFailure;
	volatile bool m_isInitialApproach;
};

AIAttackMeleeHordeApproachTargetState::AIAttackMeleeHordeApproachTargetState( StateMachine *machine )
	: AIInternalMoveToState( machine, AsciiString( "AIAttackMeleeHordeApproachTargetState" ) )
{
	m_vftable = &g_AIAttackMeleeHordeApproachTargetStateVTable;
	m_field50 = 0;
	m_field54 = 0;
	m_field58 = 0;
	m_field5C = 0;
	m_successOnPathFailure = false;
	m_isInitialApproach = true;
}

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class StateMachine;

class AIInternalMoveToState
{
public:
	AIInternalMoveToState( void *machine, AsciiString name );
};

// Retail's vftable for this class is 0x0109A640, pinned in symbols.csv as
// ??_7AIAttackFireDuringApproachState@@6B@ and confirmed by this constructor and
// by the class's key function ??_GAIAttackFireDuringApproachState@@MAEPAXI@Z at
// 0x00185410 (AITargetMovementDeletingDestructors.cpp), which is the TU that
// emits it.  The stand-in name below resolved nothing; __identifier spells the
// compiler-emitted symbol so the reference links to that real definition.
extern "C" const char __identifier("??_7AIAttackFireDuringApproachState@@6B@")[];

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
	m_vftable = (int *)__identifier("??_7AIAttackFireDuringApproachState@@6B@");
	m_field54 = 0;
	m_field58 = 0;
	m_field5C = 0;
	m_field60 = 0;
	m_field64 = 0;
	m_field68 = 0;
	m_field6C = false;
}

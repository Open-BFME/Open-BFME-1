// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class StateMachine;

// Retail's AIPickUpCrateState constructor is 0x0015CD70, reached through the
// 0x00018B92 ILT. Its vtable 0x010960D0 holds ??_GAIPickUpCrateState,
// AIPickUpCrateState::onEnter and AIPickUpCrateState::update. AIStateMachine
// and the attack-move state machines inline this same sequence.
class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );
};

extern int g_AIPickUpCrateStateVTable;

class AIPickUpCrateState : public Rva0014F280StateBase
{
public:
	AIPickUpCrateState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x4C ];
	volatile int m_delayCounter;
};

AIPickUpCrateState::AIPickUpCrateState( StateMachine *machine )
	: Rva0014F280StateBase( machine,
		AsciiString( "AIAttackPickUpCrateState" ) )
{
	m_vftable = &g_AIPickUpCrateStateVTable;
	m_delayCounter = 0;
}

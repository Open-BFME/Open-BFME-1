// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class StateMachine;

// Retail's AIPickUpCrateState constructor is 0x0015CD70, reached through the
// 0x00018B92 ILT. Its vtable 0x010960D0 holds ??_GAIPickUpCrateState,
// AIPickUpCrateState::onEnter and AIPickUpCrateState::update. AIStateMachine
// and the attack-move state machines inline this same sequence.
//
// That base ctor is AIInternalMoveToState's, reached through the 5-byte base
// ctor thunk at 0x00032182, so the shim is spelled with the real class name and
// its real (StateMachine*, AsciiString) signature.
class AIInternalMoveToState
{
public:
	AIInternalMoveToState( StateMachine *machine, AsciiString name );
};

extern int g_AIPickUpCrateStateVTable;

class AIPickUpCrateState : public AIInternalMoveToState
{
public:
	AIPickUpCrateState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x4C ];
	volatile int m_delayCounter;
};

AIPickUpCrateState::AIPickUpCrateState( StateMachine *machine )
	: AIInternalMoveToState( machine,
		AsciiString( "AIAttackPickUpCrateState" ) )
{
	m_vftable = &g_AIPickUpCrateStateVTable;
	m_delayCounter = 0;
}

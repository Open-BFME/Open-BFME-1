// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class StateMachine;

// Retail's AIPickUpCrateState constructor is reached through the
// 0x000464E8 ILT.  Its vtable at 0x010C7D30 contains the established
// AIPickUpCrateState name, onEnter, update, and computePath slots.  BFME writes
// the state-specific delay counter before installing that final vtable.
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

// ??0AIPickUpCrateState@@QAE@PAVStateMachine@@@Z
AIPickUpCrateState::AIPickUpCrateState( StateMachine *machine )
	: Rva0014F280StateBase( machine,
		AsciiString( "AIAttackPickUpCrateState" ) )
{
	m_delayCounter = 0;
	m_vftable = &g_AIPickUpCrateStateVTable;
}

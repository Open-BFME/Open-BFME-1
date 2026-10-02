// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class StateMachine;

// Retail 0x002C1150 is reached through the 0x000464E8 ILT. It inlines
// AIPickUpCrateState's constructor -- the same base, the same
// "AIAttackPickUpCrateState" name and the +0x50 delay counter -- and then
// installs its own vtable 0x010C7D30. That table inherits AIPickUpCrateState's
// name slot and base slots but has its own deleting destructor (0x002C11A0) and
// overrides slots 4 to 6. The class name is not recovered; the body sits among
// the GiantBird states.
//
// That base ctor is AIInternalMoveToState's, reached through the 5-byte base
// ctor thunk at 0x00032182, so the shim is spelled with the real class name and
// its real (StateMachine*, AsciiString) signature.
class AIInternalMoveToState
{
public:
	AIInternalMoveToState( StateMachine *machine, AsciiString name );
};

extern int g_Rva010C7D30StateVTable;

class Rva002C1150PickUpCrateState : public AIInternalMoveToState
{
public:
	Rva002C1150PickUpCrateState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x4C ];
	volatile int m_delayCounter;
};

Rva002C1150PickUpCrateState::Rva002C1150PickUpCrateState( StateMachine *machine )
	: AIInternalMoveToState( machine,
		AsciiString( "AIAttackPickUpCrateState" ) )
{
	m_delayCounter = 0;
	m_vftable = &g_Rva010C7D30StateVTable;
}

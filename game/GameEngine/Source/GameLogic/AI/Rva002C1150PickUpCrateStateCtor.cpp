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

void j_00012193();
void j_00026c60();
void j_00025fa4();
void j_0002d411();
void j_0001adf7();
void j_0000733d();
void j_00022345();
void j_0000c79d();
void j_00028b87();
void j_00023416();
void j_00015d9d();
void j_000273bd();
void j_0002cb42();
void j_00021a7b();
void j_000351b1();
void j_00007405();
void j_00016b3a();
void j_0002ca66();

// Retail VA010C7D30: eighteen existing ILT entries.
void *g_Va010C7D30[18] = {
	reinterpret_cast<void *>(&j_00012193),
	reinterpret_cast<void *>(&j_00026c60),
	reinterpret_cast<void *>(&j_00025fa4),
	reinterpret_cast<void *>(&j_0002d411),
	reinterpret_cast<void *>(&j_0001adf7),
	reinterpret_cast<void *>(&j_0000733d),
	reinterpret_cast<void *>(&j_00022345),
	reinterpret_cast<void *>(&j_0000c79d),
	reinterpret_cast<void *>(&j_00028b87),
	reinterpret_cast<void *>(&j_00023416),
	reinterpret_cast<void *>(&j_00015d9d),
	reinterpret_cast<void *>(&j_000273bd),
	reinterpret_cast<void *>(&j_0002cb42),
	reinterpret_cast<void *>(&j_00021a7b),
	reinterpret_cast<void *>(&j_000351b1),
	reinterpret_cast<void *>(&j_00007405),
	reinterpret_cast<void *>(&j_00016b3a),
	reinterpret_cast<void *>(&j_0002ca66),
};

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
	m_vftable = reinterpret_cast<int *>(g_Va010C7D30);
}

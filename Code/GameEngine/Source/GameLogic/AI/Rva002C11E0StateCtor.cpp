// cl: /DNDEBUG /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// Address-derived state constructor: name literal "GiantBirdGuardAttackAggressorState"
// verified at 0x010C7DDC; base ctor at the already-named thunk 0x000035B2
// (State(StateMachine*, AsciiString), retail body 0x000A19E0); two vtable-like
// pointer fields at offsets 0 and 0x24 are overwritten with this derived
// class's own vtables after the base ctor returns (multiple-inheritance base
// layout modelled as plain fields, matching the family in
// Code/GameEngine/Source/GameLogic/AI/AIAttackMeleeEngageStateCtor.cpp).
class AsciiString
{
public:
	AsciiString( const char *text ) : m_data( text ) {}
	StringBase<char> m_data;
};

class StateMachine;

class Rva002C11E0StateBase
{
public:
	Rva002C11E0StateBase( void *machine, AsciiString name );
};

extern int g_Rva002C11E0VTableA;
extern int g_Rva002C11E0VTableB;

class Rva002C11E0State : public Rva002C11E0StateBase
{
public:
	Rva002C11E0State( void *machine );

private:
	int *volatile m_vtableA;
	char m_pad1[ 0x24 - 4 ];
	int *volatile m_vtableB;
	volatile int m_28;
	volatile int m_2c;
	volatile int m_30;
	volatile int m_34;
	volatile int m_38;
	volatile int m_3c;
	volatile int m_40;
	volatile bool m_44;
};

Rva002C11E0State::Rva002C11E0State( void *machine )
	: Rva002C11E0StateBase( machine, AsciiString( "GiantBirdGuardAttackAggressorState" ) )
{
	m_vtableA = &g_Rva002C11E0VTableA;
	m_28 = 0;
	m_38 = 0;
	m_3c = 0;
	m_vtableB = &g_Rva002C11E0VTableB;
	m_2c = 0;
	m_30 = 0;
	m_34 = 0;
	m_44 = false;
	m_40 = 0;
}

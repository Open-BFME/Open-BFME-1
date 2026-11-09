// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// GiantBirdGuardOuterState constructor.  Retail writes +0x28 then +0x24 then
// the derived vftable then the trailing zeros; a polymorphic derived class
// always stores the vftable before the body, so this TU uses the same
// volatile-vptr overlay as AIAttackMeleeSquishStateCtor.cpp.  The name passed
// to the State base is the GiantBirdNormalFlightState literal.

#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );
};

void j_0001c260();
void j_000127ab();
void j_00022a1b();
void j_0002329a();
void j_00014597();
void j_00015ac3();
void j_000387da();
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

// Retail VA010C7CB8: seventeen existing ILT entries (vtable_lookup.py), the vftable the
// constructors at 0x002C0550 and 0x002C05C0 install.
void *g_GiantBirdGuardVftable[17] = {
	reinterpret_cast<void *>(&j_0001c260),
	reinterpret_cast<void *>(&j_000127ab),
	reinterpret_cast<void *>(&j_00022a1b),
	reinterpret_cast<void *>(&j_0002329a),
	reinterpret_cast<void *>(&j_00014597),
	reinterpret_cast<void *>(&j_00015ac3),
	reinterpret_cast<void *>(&j_000387da),
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
};

class GiantBirdGuardOuterState : public Rva000A19E0StateBase
{
public:
	GiantBirdGuardOuterState( void *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x20 ];
	volatile unsigned char m_byte24;
	char m_gap25[ 3 ];
	volatile int m_int28;
	volatile int m_int2c;
	volatile int m_int30;
	volatile int m_int34;
};

GiantBirdGuardOuterState::GiantBirdGuardOuterState( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "GiantBirdNormalFlightState" ) )
{
	m_int28 = 0;
	m_byte24 = 1;
	m_vftable = reinterpret_cast<int *>(g_GiantBirdGuardVftable);
	m_int2c = 0;
	m_int30 = 0;
	m_int34 = 0;
}

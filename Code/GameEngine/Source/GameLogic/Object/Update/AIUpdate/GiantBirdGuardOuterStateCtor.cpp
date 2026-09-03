// cl: /DNDEBUG /MD /EHsc
// GiantBirdGuardOuterState constructor.  Retail writes +0x28 then +0x24 then
// the derived vftable then the trailing zeros; a polymorphic derived class
// always stores the vftable before the body, so this TU uses the same
// volatile-vptr overlay as AIAttackMeleeSquishStateCtor.cpp.  The name passed
// to the State base is the GiantBirdNormalFlightState literal.

#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}

	StringBase<char> m_string;
};

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );
};

extern int g_GiantBirdGuardOuterStateVTable;

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
	m_vftable = &g_GiantBirdGuardOuterStateVTable;
	m_int2c = 0;
	m_int30 = 0;
	m_int34 = 0;
}

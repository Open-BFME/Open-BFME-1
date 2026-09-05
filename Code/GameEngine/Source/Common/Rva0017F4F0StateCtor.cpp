// Near-twin of the state-constructor family in StateSelfNamingCtorsWithFields.cpp
// (see that file's header for the shared shape and why identity is not
// recovered for this family). This one shares the Rva0014F280StateBase base
// (same base constructor call, 0x00032182) with several entries there, and
// installs the same vtable style, but the member layout differs: retail
// leaves a 4-byte gap right after the base subobject (uninitialised member,
// never stored) before four zero-initialised members -- an int, a byte, a
// byte three bytes later, then another int -- instead of the single
// "m_gap0[0x4C]; int m_field0;" shape used elsewhere in that file.
//
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}

	StringBase<char> m_string;
};

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class Rva0017F4F0State : public Rva0014F280StateBase
{
public:
	Rva0017F4F0State( void *machine );

	char m_gap0[ 0x4C ];
	int m_field0;
	unsigned char m_field1;
	char m_gap2[ 0x3 ];
	unsigned char m_field2;
	char m_gap3[ 0x3 ];
	int m_field3;
};

Rva0017F4F0State::Rva0017F4F0State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIFearState" ) )
{
	// retail stores these out of declaration/address order (+0x54, then
	// +0x50, +0x58, +0x5c) -- writing them as body assignments instead of
	// initialisers keeps that exact schedule.
	m_field1 = 0;
	m_field0 = 0x0;
	m_field2 = 0;
	m_field3 = 0x0;
}

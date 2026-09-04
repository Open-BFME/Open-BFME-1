// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

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

extern int g_Rva010C74D4;
extern int g_Rva002C03F0StateVTable;
extern int g_Rva002C04D0StateVTable;

class Rva002C03F0State : public Rva000A19E0StateBase
{
public:
	Rva002C03F0State( void *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x20 ];
	volatile int m_int24;
	volatile int m_int28;
	volatile int m_int2c;
	volatile int m_int30;
	volatile int m_int34;
	volatile int m_int38;
	volatile int m_int3c;
	volatile int m_int40;
	volatile unsigned char m_byte44;
};

Rva002C03F0State::Rva002C03F0State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "GiantBirdGuardInner" ) )
{
	m_vftable = &g_Rva002C03F0StateVTable;
	m_int28 = 0;
	m_int38 = 0;
	m_int3c = 0;
	m_int24 = (int)&g_Rva010C74D4;
	m_int2c = 0;
	m_int30 = 0;
	m_int34 = 0;
	m_int40 = 0;
	m_byte44 = 0;
}

class Rva002C04D0State : public Rva000A19E0StateBase
{
public:
	Rva002C04D0State( void *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x20 ];
	volatile int m_int24;
	volatile int m_int28;
	volatile int m_int2c;
	volatile int m_int30;
	volatile int m_int34;
	volatile int m_int38;
	volatile int m_int3c;
	volatile int m_int40;
	volatile unsigned char m_byte44;
};

Rva002C04D0State::Rva002C04D0State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "GiantBirdGuardOuter" ) )
{
	m_vftable = &g_Rva002C04D0StateVTable;
	m_int28 = 0;
	m_int38 = 0;
	m_int3c = 0;
	m_int24 = (int)&g_Rva010C74D4;
	m_int2c = 0;
	m_int30 = 0;
	m_int34 = 0;
	m_byte44 = 0;
	m_int40 = 0;
}

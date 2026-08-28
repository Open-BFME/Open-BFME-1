// 26 more constructors of the family landed in StateSelfNamingCtors.cpp --
// same prologue, same `StringBase<char>` temporary built from a state-name
// literal, same base constructor taking (machine, name) -- differing only in
// what each one initialises after the base returns:
//
//     ... call <base constructor> / mov [esi],<vftable> /
//     <one or more member stores> / mov eax,esi / pop esi / pop ecx / ret 4
//
// WHAT THE STORES ARE.  Constants written at fixed displacements from `this`
// once the base is built and the vftable seated: member initialisers.  Their
// widths are read off the store (`mov dword` or `mov byte`) and their values
// are the immediates.  Whether a zero arrives as an immediate or from `eax`
// after an `xor eax,eax` is the scheduler's choice and changes nothing about
// what is initialised.
//
// The members ahead of each initialised one are spelled as gap arrays: the
// bytes witness where the initialised members sit and nothing about what lies
// between them; the first gap starts at four because the base sub-object is
// one vftable slot wide here.  A store whose value is itself an address inside
// the image is written as the address of a global rather than as a number.
//
// WHAT IS NOT IN THIS FILE.  Twenty-one further bodies of the same family are
// left as dumps.  In those, retail writes the members in an order that is not
// their offset order -- several zero stores through one register, and in two
// cases a member written BEFORE the vftable.  Declaration order fixes both the
// layout and the emission order in C++, so an initialiser list cannot produce
// both at once, and assignments in the constructor body cannot precede the
// vftable store at all.  Rather than guess a member layout that happens to
// schedule the same way, those are left for a pass that can recover the real
// declaration order.
//
// Read StateSelfNamingCtors.cpp's header for why the literal does not settle
// the class name, and for the bases and their pins.  IDENTITY IS NOT RECOVERED:
// every name here is derived from an address.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}

	StringBase<char> m_string;
};

extern int g_Va0109B558;

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class Rva000250BDStateBase
{
public:
	Rva000250BDStateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class Rva0014F420State : public Rva000A19E0StateBase
{
public:
	Rva0014F420State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva0014F420State::Rva0014F420State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIDockWaitForClearanceState" ) ),
	  m_field0( 0x0 )
{
}

class Rva0014F710State : public Rva000A19E0StateBase
{
public:
	Rva0014F710State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
	int m_field1;
};

Rva0014F710State::Rva0014F710State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIDockProcessDockState" ) ),
	  m_field0( 0x0 ),
	  m_field1( 0x0 )
{
}

class Rva0015CD70State : public Rva0014F280StateBase
{
public:
	Rva0015CD70State( void *machine );

	char m_gap0[ 0x4C ];
	int m_field0;
};

Rva0015CD70State::Rva0015CD70State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIAttackPickUpCrateState" ) ),
	  m_field0( 0x0 )
{
}

class Rva0015CF50State : public Rva0014F280StateBase
{
public:
	Rva0015CF50State( void *machine );

	char m_gap0[ 0x4C ];
	int m_field0;
};

Rva0015CF50State::Rva0015CF50State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIGuardReturn" ) ),
	  m_field0( 0x0 )
{
}

class Rva0015EC40State : public Rva0014F280StateBase
{
public:
	Rva0015EC40State( void *machine );

	char m_gap0[ 0x4C ];
	int m_field0;
};

Rva0015EC40State::Rva0015EC40State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIGuardRetaliateReturn" ) ),
	  m_field0( 0x0 )
{
}

class Rva0015FDB0State : public Rva000A19E0StateBase
{
public:
	Rva0015FDB0State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva0015FDB0State::Rva0015FDB0State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIHarvestPrepareSiteState" ) ),
	  m_field0( 0x0 )
{
}

class Rva0015FE20State : public Rva000A19E0StateBase
{
public:
	Rva0015FE20State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva0015FE20State::Rva0015FE20State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIHarvestWorkSiteState" ) ),
	  m_field0( 0x0 )
{
}

class Rva00171060State : public Rva000A19E0StateBase
{
public:
	Rva00171060State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva00171060State::Rva00171060State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIBackAwayAndCowerState" ) ),
	  m_field0( 0x0 )
{
}

class Rva001710C0State : public Rva000A19E0StateBase
{
public:
	Rva001710C0State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva001710C0State::Rva001710C0State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIAttackMeleeHordeWaitState" ) ),
	  m_field0( 0x0 )
{
}

class Rva00171120State : public Rva000A19E0StateBase
{
public:
	Rva00171120State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
	int m_field1;
};

Rva00171120State::Rva00171120State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIAttackMeleeHordeWaitPathState" ) ),
	  m_field0( 0x0 ),
	  m_field1( 0x0 )
{
}

class Rva00171480State : public Rva000A19E0StateBase
{
public:
	Rva00171480State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
	unsigned char m_field1;
};

Rva00171480State::Rva00171480State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIHarvestState" ) ),
	  m_field0( 0x0 ),
	  m_field1( 0 )
{
}

class Rva001715A0State : public Rva000A19E0StateBase
{
public:
	Rva001715A0State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva001715A0State::Rva001715A0State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIMeleeReAcquireState" ) ),
	  m_field0( 0x0 )
{
}

class Rva00171610State : public Rva000A19E0StateBase
{
public:
	Rva00171610State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva00171610State::Rva00171610State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIExitState" ) ),
	  m_field0( 0x0 )
{
}

class Rva001716D0State : public Rva000A19E0StateBase
{
public:
	Rva001716D0State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva001716D0State::Rva001716D0State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGuardState" ) ),
	  m_field0( 0x0 )
{
}

class Rva00171820State : public Rva000A19E0StateBase
{
public:
	Rva00171820State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
	int m_field1;
};

Rva00171820State::Rva00171820State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIHuntState" ) ),
	  m_field0( 0x0 ),
	  m_field1( 0x0 )
{
}

class Rva001719F0State : public Rva000A19E0StateBase
{
public:
	Rva001719F0State( void *machine );

	char m_gap0[ 0x20 ];
	unsigned char m_field0;
	char m_gap1[ 0x3 ];
	int m_field1;
	int m_field2;
};

Rva001719F0State::Rva001719F0State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIRampageState" ) ),
	  m_field0( 0 ),
	  m_field1( 0x0 ),
	  m_field2( 0xFFFFFFFF )
{
}

class Rva00171D50State : public Rva000A19E0StateBase
{
public:
	Rva00171D50State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva00171D50State::Rva00171D50State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIMoveOntoWallState" ) ),
	  m_field0( 0x0 )
{
}

class Rva00173620State : public Rva0014F280StateBase
{
public:
	Rva00173620State( void *machine );

	char m_gap0[ 0x4C ];
	int m_field0;
	unsigned char m_field1;
};

Rva00173620State::Rva00173620State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIMoveToStateSA" ) ),
	  m_field0( 0x0 ),
	  m_field1( 0 )
{
}

class Rva001744C0State : public Rva000A19E0StateBase
{
public:
	Rva001744C0State( void *machine );

	char m_gap0[ 0x20 ];
	unsigned char m_field0;
};

Rva001744C0State::Rva001744C0State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AICowerState" ) ),
	  m_field0( 1 )
{
}

class Rva0017FDC0State : public Rva0014F280StateBase
{
public:
	Rva0017FDC0State( void *machine );

	char m_gap0[ 0x4C ];
	unsigned char m_field0;
};

Rva0017FDC0State::Rva0017FDC0State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIMoveToPositionAndDieState" ) ),
	  m_field0( 0 )
{
}

class Rva001800A0State : public Rva0014F280StateBase
{
public:
	Rva001800A0State( void *machine );

	char m_gap0[ 0x4C ];
	int m_field0;
	int m_field1;
};

Rva001800A0State::Rva001800A0State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIEnterAndAttackState" ) ),
	  m_field0( 0x0 ),
	  m_field1( 0x0 )
{
}

class Rva00180550State : public Rva0014F280StateBase
{
public:
	Rva00180550State( void *machine );

	char m_gap0[ 0x4C ];
	unsigned char m_field0;
	char m_gap1[ 0x3 ];
	int m_field1;
	unsigned char m_field2;
	unsigned char m_field3;
};

Rva00180550State::Rva00180550State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIChargeTargetState" ) ),
	  m_field0( 0 ),
	  m_field1( 0x1 ),
	  m_field2( 0 ),
	  m_field3( 0 )
{
}

class Rva0018AC40State : public Rva000A19E0StateBase
{
public:
	Rva0018AC40State( void *machine );

	char m_gap0[ 0x20 ];
	void *m_field0;
	int m_field1;
};

Rva0018AC40State::Rva0018AC40State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AITNGuardInner" ) ),
	  m_field0( &g_Va0109B558 ),
	  m_field1( 0x0 )
{
}

class Rva0018AD60State : public Rva0014F280StateBase
{
public:
	Rva0018AD60State( void *machine );

	char m_gap0[ 0x4C ];
	int m_field0;
	int m_field1;
};

Rva0018AD60State::Rva0018AD60State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIEnterState" ) ),
	  m_field0( 0x0 ),
	  m_field1( 0x0 )
{
}

class Rva002BDB30State : public Rva000250BDStateBase
{
public:
	Rva002BDB30State( void *machine );

	char m_gap0[ 0x58 ];
	int m_field0;
};

Rva002BDB30State::Rva002BDB30State( void *machine )
	: Rva000250BDStateBase( machine, AsciiString( "GiantBirdFollowPathState" ) ),
	  m_field0( 0x0 )
{
}

class Rva002C0470State : public Rva000A19E0StateBase
{
public:
	Rva002C0470State( void *machine );

	char m_gap0[ 0x20 ];
	int m_field0;
};

Rva002C0470State::Rva002C0470State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "GiantBirdGuardIdleState" ) ),
	  m_field0( 0x0 )
{
}


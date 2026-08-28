// 85 eleven-byte __thiscall members with one shape:
//
//     mov dword ptr [ecx],<offset vftable> / jmp <rel32>
//
// WHAT THE BODY IS.  A destructor of a derived class with an empty body: MSVC
// 7.1 re-seats the vptr to the class being destroyed and then tail-jumps into
// the base destructor, which is a jump rather than a call precisely because
// nothing follows it.  It cannot be a constructor -- MSVC returns `this` in eax
// from every constructor and none is set up here -- and the absence of any
// `this` adjustment before the jump proves the base sub-object sits at +0x00,
// which in turn means the vptr belongs to the base and the destructor being
// jumped to is virtual.
//
// WHERE THE JUMP GOES.  The displacement is decoded from the retail bytes, so
// each base is an ADDRESS first and a name second.  4 of the 29 distinct
// targets are already a named virtual destructor in the ledger, and those bases
// are declared here under that name so the relocation resolves through the
// ledger with no pin.  The other 25 are addresses nothing has named: each gets
// an address-derived base declared here and a `reverse/symbols.csv` pin at the
// address the displacement decodes to.  A pin is a candidate, not a proof --
// but these are not guesses: the address IS the jump target, read off the
// instruction, and the name attached to it asserts nothing beyond "the virtual
// destructor this body jumps into".
//
// Several derived classes share a base, which is what a base class is for; the
// bases are declared once each below.
//
// IDENTITY IS NOT RECOVERED for the derived classes.  Every name is derived
// from an address.

class Rva00009E35TailBase
{
public:
	virtual ~Rva00009E35TailBase();
};

class Rva0000DBA7TailBase
{
public:
	virtual ~Rva0000DBA7TailBase();
};

class Rva0001AA9BTailBase
{
public:
	virtual ~Rva0001AA9BTailBase();
};

class Rva00020BA3TailBase
{
public:
	virtual ~Rva00020BA3TailBase();
};

class Rva00020D9CTailBase
{
public:
	virtual ~Rva00020D9CTailBase();
};

class Rva00021FC1TailBase
{
public:
	virtual ~Rva00021FC1TailBase();
};

class Rva00026175TailBase
{
public:
	virtual ~Rva00026175TailBase();
};

class Rva00026FC6TailBase
{
public:
	virtual ~Rva00026FC6TailBase();
};

class Rva00028763TailBase
{
public:
	virtual ~Rva00028763TailBase();
};

class Rva00028ECATailBase
{
public:
	virtual ~Rva00028ECATailBase();
};

class Rva0002B8C8TailBase
{
public:
	virtual ~Rva0002B8C8TailBase();
};

class Rva00031D5ETailBase
{
public:
	virtual ~Rva00031D5ETailBase();
};

class Rva00033875TailBase
{
public:
	virtual ~Rva00033875TailBase();
};

class Rva00035D46TailBase
{
public:
	virtual ~Rva00035D46TailBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	virtual ~UserPreferences();
};

class Rva0004584ATailBase
{
public:
	virtual ~Rva0004584ATailBase();
};

class Rva000491E3TailBase
{
public:
	virtual ~Rva000491E3TailBase();
};

class Rva0004B227TailBase
{
public:
	virtual ~Rva0004B227TailBase();
};

class Rva0082AE40TailBase
{
public:
	virtual ~Rva0082AE40TailBase();
};

class Rva00832090TailBase
{
public:
	virtual ~Rva00832090TailBase();
};

class Rva0083F730TailBase
{
public:
	virtual ~Rva0083F730TailBase();
};

class Rva008B2DF0TailBase
{
public:
	virtual ~Rva008B2DF0TailBase();
};

class Rva008D5F70TailBase
{
public:
	virtual ~Rva008D5F70TailBase();
};

class Rva0092B6A0TailBase
{
public:
	virtual ~Rva0092B6A0TailBase();
};

class Rva00943E70TailBase
{
public:
	virtual ~Rva00943E70TailBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8FVFCategoryContainer
{
public:
	virtual ~DX8FVFCategoryContainer();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFile.h
class LocalFile
{
public:
	virtual ~LocalFile();
};

class Rva009EB810TailBase
{
public:
	virtual ~Rva009EB810TailBase();
};

#define BFME_VPTR_TAIL_JUMP_DTOR( NAME, BASE )                                \
	class NAME : public BASE                                                  \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

BFME_VPTR_TAIL_JUMP_DTOR( Rva0006B140TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0006B690TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00086320TailDtor, UserPreferences )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0009C1E0TailDtor, UserPreferences )
BFME_VPTR_TAIL_JUMP_DTOR( Rva000AAFC0TailDtor, UserPreferences )
BFME_VPTR_TAIL_JUMP_DTOR( Rva000AAFD0TailDtor, UserPreferences )
BFME_VPTR_TAIL_JUMP_DTOR( Rva000C4040TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00105350TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00121D10TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00124B20TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00124BF0TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0014E640TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0015B9D0TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0015E730TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0015F730TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016AB00TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016AB50TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016ABA0TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016ABF0TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016AC40TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016AC60TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016ACE0TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016B230TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016B5A0TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016CB60TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00189B00TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0018C2D0TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0024F3F0TailDtor, Rva0004B227TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002B6420TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002BBAC0TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002BBCF0TailDtor, Rva00035D46TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002C0360TailDtor, Rva00020D9CTailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002C59E0TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002C8120TailDtor, Rva00031D5ETailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002ED430TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00321FE0TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0033C070TailDtor, Rva00020BA3TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0035F110TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00410290TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva004133C0TailDtor, Rva0000DBA7TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0048CCD0TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0052CC80TailDtor, Rva00021FC1TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00538210TailDtor, Rva0083F730TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0059D1E0TailDtor, Rva0001AA9BTailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0059FB40TailDtor, Rva0001AA9BTailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00602EC0TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00602F10TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00603120TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00604550TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00607BD0TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0063FC80TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva006BA460TailDtor, Rva00026FC6TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva006BA490TailDtor, Rva00033875TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva006C0590TailDtor, Rva000491E3TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva006C05F0TailDtor, Rva00028763TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva006E1730TailDtor, Rva00009E35TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00711B20TailDtor, Rva00943E70TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00750230TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007502D0TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00751700TailDtor, Rva0004584ATailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00759350TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0077F250TailDtor, Rva0002B8C8TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0078ABD0TailDtor, Rva00026175TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0078F5B0TailDtor, Rva00028ECATailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0081C520TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0083E8B0TailDtor, Rva0082AE40TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0083F810TailDtor, Rva0083F730TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00840900TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00843D90TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00843E30TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008441B0TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008441F0TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008444E0TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008444F0TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00847F30TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00847FD0TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00848070TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00848110TailDtor, Rva00832090TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008B3980TailDtor, Rva008B2DF0TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008D5FD0TailDtor, Rva008D5F70TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008D5FF0TailDtor, Rva008D5F70TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0092BAC0TailDtor, Rva0092B6A0TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva009471E0TailDtor, DX8FVFCategoryContainer )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00972950TailDtor, Rva009EB810TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva009D1950TailDtor, LocalFile )

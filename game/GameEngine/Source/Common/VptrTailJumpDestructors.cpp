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
// an address-derived base declared here and a `targets/game/reverse/symbols.csv` pin at the
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

// 0x00031D5E is retail's ILT to the matched StateMachine destructor
// (??1StateMachine@@MAE@XZ at 0x000A1130); the base is retail's real
// StateMachine, whose destructor is protected.
class StateMachine
{
protected:
	virtual ~StateMachine();
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
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

// STLport 4.5.3 locale::facet's destructor (src/locale_impl.cpp: an empty body).
// Retail 0x00832090 re-seats the vptr to 0x0112E940, the facet vftable retail
// RTTI names, and returns; the messages destructors at 0x00848A30/0x00848B20
// and the facet destructors in stlport_locale_facet_destructors.cpp reach it as
// 1facet@locale@_STL@@MAE@XZ (decorated, leading ?? dropped).
namespace _STL
{
class locale
{
public:
	class facet
	{
	protected:
		virtual ~facet();
	};
};
}

__declspec(noinline) _STL::locale::facet::~facet() {}

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8FVFCategoryContainer
{
public:
	virtual ~DX8FVFCategoryContainer();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFile.h
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
BFME_VPTR_TAIL_JUMP_DTOR( Rva0015B9D0TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0015E730TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0015F730TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016AB00TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016AB50TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016ABA0TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016ABF0TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016AC40TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016AC60TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016ACE0TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016B230TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0016B5A0TailDtor, StateMachine )
// 0x0016CB60: ILT 0x00006BDB, called by the matched scalar-deleting
// destructor ??_GAIAttackThenIdleStateMachine (0x0016F310).
class AIAttackThenIdleStateMachine : public StateMachine
{
protected:
	virtual ~AIAttackThenIdleStateMachine();
};
AIAttackThenIdleStateMachine::~AIAttackThenIdleStateMachine()
{
}
BFME_VPTR_TAIL_JUMP_DTOR( Rva00189B00TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0018C2D0TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0024F3F0TailDtor, Rva0004B227TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002B6420TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002BBAC0TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002BBCF0TailDtor, Rva00035D46TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002C0360TailDtor, Rva00020D9CTailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002C59E0TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002C8120TailDtor, StateMachine )
BFME_VPTR_TAIL_JUMP_DTOR( Rva002ED430TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00321FE0TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0033C070TailDtor, Rva00020BA3TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0035F110TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0048CCD0TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0052CC80TailDtor, Rva00021FC1TailBase )
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
BFME_VPTR_TAIL_JUMP_DTOR( Rva0081C520TailDtor, SubsystemInterface )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008B3980TailDtor, Rva008B2DF0TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008D5FD0TailDtor, Rva008D5F70TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva008D5FF0TailDtor, Rva008D5F70TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva0092BAC0TailDtor, Rva0092B6A0TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva009471E0TailDtor, DX8FVFCategoryContainer )
BFME_VPTR_TAIL_JUMP_DTOR( Rva00972950TailDtor, Rva009EB810TailBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva009D1950TailDtor, LocalFile )

// 0x0014E640 re-seats AIDockMachine's vftable (the vtable its matched
// constructor 0x0014F7C0 installs) and is reached from the matched
// scalar deleting destructor 0x0014F120 through ILT 0x0000B7C6
// (identity_evidence/0014e640-aidockmachine-dtor.md).
class AIDockMachine : public StateMachine
{
protected:
	virtual ~AIDockMachine();
};

AIDockMachine::~AIDockMachine()
{
}

// Ten unclaimed eleven-byte __thiscall bodies with one shape:
//
//     mov dword ptr [ecx],<offset vftable> / jmp <base destructor>
//
// An empty destructor of a derived class: it re-seats the vftable at +0 and
// tail-jumps into the base destructor (precedent: VptrTailJumpDestructors.cpp,
// whose comment gives the full reasoning).  Each body sat in a .text gap no
// ledger row covered: 16-byte-aligned start after an int3 pad run, the jmp
// followed by int3 padding or the next matched row, and no call, ILT stub,
// table slot, code immediate, pin or dir32 name at the address.
//
// WHERE THE JUMP GOES.  The displacement is read off the retail bytes.  Nine
// bodies jump to 0x007EB6C0, matched as ??1BfmeDirtyBase@@UAE@XZ, and one to
// 0x007FA650, matched as ??1Rva00803890Base@@UAE@XZ; both bases are declared
// here under those names (each is declared in its own source, not a header)
// so the jump resolves through the ledger with no new pin.
//
// WHICH CLASS.  A destructor that only re-seats vftable V and then runs the
// base destructor is ~V or the destructor of any trivially-destructible
// descendant of V: MSVC 7.1 drops a derived class's own vftable store when
// the inlined base destructor re-stores the base one.  So V's owner is not
// this body's owner, and each class keeps the destructor's own address.
//
// IDENTITY IS NOT RECOVERED for the derived classes.  Every name is derived
// from an address.

struct BfmeDirtyBase
{
public:
	virtual ~BfmeDirtyBase();
};

class Rva00803890Base
{
public:
	virtual ~Rva00803890Base();
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

BFME_VPTR_TAIL_JUMP_DTOR( Rva007E9080ReseatTailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F03B0ReseatTailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F1C80ReseatTailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F2200ReseatTailDtor, BfmeDirtyBase )
// 0x0112AF04 is the vftable the dir32 record owns as ??_7Gen007F33E0@@6B@
// (with ??_7Rva007F2F50CleanupDeleting@@6B@ at the same address); this class's
// own vftable was the unrecorded name the dir32 gate debt at 0x0112AF04 retires.
// novtable suppresses it (and its ??_G); the eleven-byte body is the explicit
// store of the recorded vtable followed by the tail-jump into the base dtor.
// retired debt: ??_7Rva007F2E90ReseatTailDtor@@6B@ replaced with ??_7Gen007F33E0@@6B@
extern "C" void *__identifier("??_7Gen007F33E0@@6B@")[];

class __declspec(novtable) Rva007F2E90ReseatTailDtor : public BfmeDirtyBase
{
public:
	virtual ~Rva007F2E90ReseatTailDtor();
};

Rva007F2E90ReseatTailDtor::~Rva007F2E90ReseatTailDtor()
{
	*(volatile void **)this = (void *)__identifier("??_7Gen007F33E0@@6B@");
}
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F3590ReseatTailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F4120ReseatTailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F48A0ReseatTailDtor, Rva00803890Base )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007FADD0ReseatTailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007FBC20ReseatTailDtor, BfmeDirtyBase )

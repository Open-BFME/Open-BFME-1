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

BFME_VPTR_TAIL_JUMP_DTOR( Rva007E9080TailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F03B0TailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F1C80TailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F2200TailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F2E90TailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F3590TailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F4120TailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007F48A0TailDtor, Rva00803890Base )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007FADD0TailDtor, BfmeDirtyBase )
BFME_VPTR_TAIL_JUMP_DTOR( Rva007FBC20TailDtor, BfmeDirtyBase )

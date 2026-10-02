// Seventeen unclaimed seven-byte __thiscall bodies with one shape:
//
//     mov dword ptr [ecx],<offset vftable> / ret
//
// An empty destructor of a polymorphic class: it re-seats a vftable at +0 and
// returns nothing (a constructor would also return `this` in eax).  Precedent:
// TrivialVirtualDestructors.cpp.  Each sat in a .text gap no ledger row
// covered: 16-byte-aligned start after an int3 pad run, ret followed by int3
// padding or the next matched row, and no call, ILT stub, table slot, code
// immediate, pin or dir32 name at the address.
//
// WHICH CLASS.  Re-seating vftable V makes the body ~V or the destructor of
// any trivially-destructible descendant of V: MSVC 7.1 drops a derived class's
// own vftable store when the inlined base destructor re-stores the base one,
// and retail has hundreds of such bodies over far fewer vftables.  So the
// vftable's owner is not proof of this body's owner; each class keeps the
// destructor's own address.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_VTABLE_RESEAT_DTOR( NAME )                                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

BFME_VTABLE_RESEAT_DTOR( Rva007EA6C0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007F48B0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007F48C0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007F8720VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007F8DA0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007F95D0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007FA670VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007FA970VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007FBB50VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007FCFB0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00801420VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00802200VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00802280VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00802870VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00802E30VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva008062F0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00938BC0VtableReseat )

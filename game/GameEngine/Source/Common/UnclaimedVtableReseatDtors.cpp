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
// 0x0112B3AC is the vftable Rva007F4860VptrCtor.cpp emits (ledger dir32 row
// ??_7Rva007F4860Owner@@6B@); this class's own vftable was the unrecorded name
// the dir32 gate debt at 0x0112B3AC retires.  novtable suppresses it (and its
// ??_G); the seven-byte body is the explicit store of the recorded vtable alone,
// matching retail 0x007F48B0.
// retired debt: ??_7Rva007F48B0VtableReseat@@6B@ replaced with ??_7Rva007F4860Owner@@6B@
extern "C" void *__identifier("??_7Rva007F4860Owner@@6B@")[];

class __declspec(novtable) Rva007F48B0VtableReseat
{
public:
	virtual ~Rva007F48B0VtableReseat();
};

Rva007F48B0VtableReseat::~Rva007F48B0VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva007F4860Owner@@6B@");
}
BFME_VTABLE_RESEAT_DTOR( Rva007F48C0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007F8720VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007F8DA0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007F95D0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007FA670VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007FA970VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007FBB50VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva007FCFB0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00801420VtableReseat )
// 0x0112C4E8 is the vftable the dir32 record owns as ??_7Rva00802380Base@@6B@
// (with ??_7T2EmptyDtor_00802360@@6B@ at the same address); this class's own
// vftable was the unrecorded name the dir32 gate debt at 0x0112C4E8 retires.
// novtable suppresses it (and its ??_G); the seven-byte body is the explicit
// store of the recorded vtable alone.
// retired debt: ??_7Rva00802200VtableReseat@@6B@ replaced with ??_7Rva00802380Base@@6B@
extern "C" void *__identifier("??_7Rva00802380Base@@6B@")[];

class __declspec(novtable) Rva00802200VtableReseat
{
public:
	virtual ~Rva00802200VtableReseat();
};

Rva00802200VtableReseat::~Rva00802200VtableReseat()
{
	*(volatile void **)this = (void *)__identifier("??_7Rva00802380Base@@6B@");
}
BFME_VTABLE_RESEAT_DTOR( Rva00802280VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00802870VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00802E30VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva008062F0VtableReseat )
BFME_VTABLE_RESEAT_DTOR( Rva00938BC0VtableReseat )

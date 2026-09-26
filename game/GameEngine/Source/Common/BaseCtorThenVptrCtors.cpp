// 27 twenty-five-byte __thiscall constructors with one shape:
//
//     mov eax,[esp+4] / push esi / push eax / mov esi,ecx /
//     call <base constructor> / mov [esi],<offset vftable> /
//     mov eax,esi / pop esi / ret 4
//
// WHAT THE BODY IS.  `this` is saved in esi across a call, the single dword
// argument is forwarded to that call, and afterwards a vftable is written at
// +0x00 and `this` returned in eax -- which is a constructor of a derived class
// running its base's constructor and then seating its own vftable.  The order
// settles it: MSVC 7.1 writes the derived vptr AFTER the base constructor
// returns, precisely because the base constructor writes the base's own vptr to
// the same slot and the derived's has to win.  No `this` adjustment before the
// call, so the base sub-object is at +0x00 and it is the base that is
// polymorphic.
//
// The argument is forwarded untouched and never stored, so nothing here says
// what it is; it is spelled `void *` because a dword is all the bytes show.
//
// BASES AND PINS.  4 distinct base constructors over 27 bodies, each an
// address decoded from the retail REL32 and pinned in `targets/game/reverse/symbols.csv`
// under an address-derived name.  The pin asserts only "the constructor this
// body calls".
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class Rva0001DD31CtorBase
{
public:
	Rva0001DD31CtorBase( void *argument );

	virtual void ctorBaseAnchor();
};

class Rva0003707ECtorBase
{
public:
	Rva0003707ECtorBase( void *argument );

	virtual void ctorBaseAnchor();
};

class Rva00048F09CtorBase
{
public:
	Rva00048F09CtorBase( void *argument );

	virtual void ctorBaseAnchor();
};

class Rva000493F0CtorBase
{
public:
	Rva000493F0CtorBase( void *argument );

	virtual void ctorBaseAnchor();
};

#define BFME_BASE_CTOR_THEN_VPTR( NAME, BASE )                                \
	class NAME : public BASE                                                  \
	{                                                                         \
	public:                                                                   \
		NAME( void *argument );                                               \
	};                                                                        \
	NAME::NAME( void *argument ) : BASE( argument ) {}

BFME_BASE_CTOR_THEN_VPTR( Rva00296530VptrCtor, Rva0001DD31CtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva002967E0VptrCtor, Rva000493F0CtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva0078FA00VptrCtor, Rva00048F09CtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva0078FCA0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva0078FD30VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva007903F0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00790480VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00790C40VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00790CD0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00791F40VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00791FF0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00792040VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00792070VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00793150VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva007931B0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00793D30VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00793E00VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva007961D0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00796260VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00796A60VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00796AF0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva007974C0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00797550VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00798510VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva007985A0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva007996A0VptrCtor, Rva0003707ECtorBase )
BFME_BASE_CTOR_THEN_VPTR( Rva00799730VptrCtor, Rva0003707ECtorBase )

// One 60-byte two-argument constructor at 0x005E3300 -- the same family
// T1BaseForwardingCtors.cpp documents, at the arity where TWO secondary base
// stores survive instead of one.  Retail:
//
//     mov eax,[esp+8] / push esi / mov esi,ecx / mov ecx,[esp+8]
//     push eax / push ecx / mov ecx,esi / call <BASE CTOR>
//     mov [esi+0x14],<VB1>
//     mov [esi+0x18],<VB2>
//     mov [esi],     <V0>
//     mov [esi+0x14],<V1>
//     mov [esi+0x18],<V2>
//     mov eax,esi / pop esi / ret 8
//
// WHAT THE BYTES SHOW.  `this` in ecx, `ret 8`, `mov eax,esi` returning
// `this`: a __thiscall constructor with two dword parameters.  Neither
// parameter is stored into the object; both are re-pushed unchanged in the
// order that makes the callee see (first, second), so the whole body is a
// member-initialiser forward plus vptr stores.
//
// THREE VPTR SLOTS, AT 0, 0x14 AND 0x18, and 0x14 and 0x18 are each written
// TWICE with two different addresses.  A slot written twice is a base storing
// its own vptr and the derived overwriting it, so this class has three
// polymorphic bases: a FIRST at offset 0 whose constructor is the `call` and
// whose own store MSVC 7.1 eliminated (the derived store to +0 kills only the
// primary base's), and a SECOND and a THIRD at 0x14 and 0x18 whose stores
// survive.  Both of those are INLINED -- there is no call for either -- so
// each has an implicit or trivial constructor and each is a bare vptr, four
// bytes wide.  The first base runs 0x14 wide: a vptr plus four dwords.
//
// The base constructor at 0x005DD290 is the same one three rows of
// T1BaseForwardingCtors.cpp call, which is why it is spelled with that file's
// two-argument signature; it is unclaimed, so it enters here as a declaration
// pinned by address.
//
// IDENTITY IS NOT RECOVERED.  The five vftable dwords are DIR32 operands
// copied from retail; they prove only that no two of the slots hold the same
// class.  Every name here is derived from an address.

class U1First_005E3300
{
public:
	U1First_005E3300( void *a, void *b );
	virtual void s0();
	int m_pad[ 4 ];
};

class U1Second_005E3300
{
public:
	virtual void s0();
};

class U1Third_005E3300
{
public:
	virtual void s0();
};

class U1Ctor_005E3300
	: public U1First_005E3300, public U1Second_005E3300, public U1Third_005E3300
{
public:
	U1Ctor_005E3300( void *a, void *b );
};

U1Ctor_005E3300::U1Ctor_005E3300( void *a, void *b )
	: U1First_005E3300( a, b )
{
}

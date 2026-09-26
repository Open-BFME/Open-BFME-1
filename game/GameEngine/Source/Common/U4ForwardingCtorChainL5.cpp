// cl: /EHs-c-
//
// Three more single-vptr forwarding constructors of the shape this slice is
// full of -- one of them the FIFTH level of the chain
// game/GameEngine/Source/Common/T4ForwardingCtorChainL1.cpp..L3.cpp and
// U4ForwardingCtorChainL4.cpp walk up.  Each level is its own translation unit
// because MSVC 7.1 inlines a callee defined alongside its caller and retail
// keeps a `call`.
//
// Retail, the one-argument arity (0x006054C0 and 0x0060D640, 25 bytes):
//
//     mov eax,[esp+4] / push esi / push eax / mov esi,ecx
//     call <BASE CTOR>
//     mov [esi],<VFT>
//     mov eax,esi / pop esi / ret 4
//
// Retail, the two-argument arity (0x00602E80, 32 bytes):
//
//     mov eax,[esp+8] / push esi / mov esi,ecx / mov ecx,[esp+8]
//     push eax / push ecx / mov ecx,esi
//     call <BASE CTOR>
//     mov [esi],<VFT>
//     mov eax,esi / pop esi / ret 8
//
// WHAT THE BYTES SHOW.  `mov esi,ecx` ... `mov eax,esi` before a `ret` that
// pops the arguments is a __thiscall returning its receiver: a constructor.
// Every argument is re-pushed UNCHANGED and never read, so the body forwards
// its whole parameter list to one base and does nothing else.  Exactly ONE
// constant store survives, at offset 0.  Following T1BaseForwardingCtors.cpp's
// reading -- MSVC 7.1 elides only the PRIMARY base's own vptr store, so a
// secondary base's store would survive -- one store at 0 and none elsewhere
// means ONE base, at offset 0, and the class owns exactly one vptr.  No
// derived-to-base adjustment (`test/je/lea/jmp/xor`) is emitted for the
// forwarded pointer either, which is the same fact read a second way.
//
// 0x006054C0's BASE IS ANOTHER ROW OF THE CHAIN.  Its REL32 resolves to
// 0x00605100, the copy constructor U4ForwardingCtorChainL4.cpp landed, whose
// own base is 0x00604E90 from T4PlainFieldCtors.cpp.  That makes five levels
// stacked here, each an out-of-line `call` into the next: 0x00604E90 ->
// 0x00605100 -> 0x006054C0.  Its argument is therefore spelled as a reference
// to its own class, as the callee's is.
//
// THE OTHER TWO BASES ARE OUTSIDE THIS SLICE and are pinned by address.
// 0x0061BF00 takes one dword; 0x00113DA0 takes two, and retail's own name for
// it is ambiguous -- the ledger already carries that one address under two
// ICF-folded names -- so it is spelled here by address and its parameters by
// width only.  Spelling the arguments `unsigned int` / `void *` rather than a
// declared pointer type is deliberate: their width is all the bytes fix.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address, and each
// vftable dword is a DIR32 operand copied from retail: three distinct
// addresses, so three distinct classes, and nothing more.

// ------------------------------------------------------- bases, declared only

// 0x00604E90 -- game/GameEngine/Source/Common/T4PlainFieldCtors.cpp
class T4Ctor00604E90
{
public:
	T4Ctor00604E90( const T4Ctor00604E90 &other );
	virtual void s0();
	void *m_field04;
};

// 0x00605100 -- game/GameEngine/Source/Common/U4ForwardingCtorChainL4.cpp
class U4Ctor00605100 : public T4Ctor00604E90
{
public:
	U4Ctor00605100( const U4Ctor00605100 &other );
	void *m_field08;
};

// 0x0061BF00, pinned in targets/game/reverse/symbols.csv
class U4Base0061BF00
{
public:
	U4Base0061BF00( unsigned int a );
	virtual void s0();
};

// 0x00113DA0, pinned in targets/game/reverse/symbols.csv
class U4Base00113DA0
{
public:
	U4Base00113DA0( void *a, const void *b );
	virtual void s0();
};

// ------------------------------------------------------------------ the rows

class U4Ctor006054C0 : public U4Ctor00605100
{
public:
	U4Ctor006054C0( const U4Ctor006054C0 &other );
};

U4Ctor006054C0::U4Ctor006054C0( const U4Ctor006054C0 &other )
	: U4Ctor00605100( other )
{
}

class U4Ctor0060D640 : public U4Base0061BF00
{
public:
	U4Ctor0060D640( unsigned int a );
};

U4Ctor0060D640::U4Ctor0060D640( unsigned int a )
	: U4Base0061BF00( a )
{
}

class U4Ctor00602E80 : public U4Base00113DA0
{
public:
	U4Ctor00602E80( void *a, const void *b );
};

U4Ctor00602E80::U4Ctor00602E80( void *a, const void *b )
	: U4Base00113DA0( a, b )
{
}

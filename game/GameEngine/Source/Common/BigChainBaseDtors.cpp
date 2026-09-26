// cl: /DNDEBUG /MD /EHsc
// Twenty-four 89-byte __thiscall destructors, one shape.  Retail:
//
//     push -1 / push <ehdata> / fs:[0] frame ; EH state 0, `this` at [esp+4]
//     ecx = this ? this + 4 : 0              ; test/je/lea/jmp/xor
//     call <REL32>                           ; destroy the base at +4
//     EH state -1
//     ecx = [this]; if (ecx) { eax=[ecx]; push 1; call [eax] }   ; virtual delete
//
// WHAT THE BYTES SHOW.  The NULL-CHECKED POINTER ADJUSTMENT is the whole
// argument.  Destroying a MEMBER at +4 emits a bare `lea ecx,[esi+4]` -- eight
// bytes shorter, measured -- because the address of a member of `this` cannot
// be null.  Destroying a SECOND BASE at +4 emits the guarded form, because the
// derived-to-base pointer conversion is written to yield null for a null
// pointer and MSVC does not special-case `this` here.  So the object at +4 is a
// BASE, not a member, and the class uses multiple inheritance.
//
// The first base, at offset 0, is destroyed second (reverse declaration order)
// and its destructor is INLINED to `if (p) delete p` over a single pointer at
// offset 0 -- `mov eax,[ecx] / push 1 / call [eax]` is slot 0 with flag 1, the
// scalar deleting destructor, so what it points at has a virtual destructor.
// A four-byte first base with an inline destructor is what puts the second base
// at exactly +4 in all twenty-four members.
//
// ONE AXIS: the REL32 destructor of the second base.  Eighteen of the twenty-
// four callees are OTHER MEMBERS OF THIS SAME FAMILY, so the shape describes a
// deep single chain of these classes; that chain is left unasserted here and
// each callee is declared as its own class, which is the weaker claim the bytes
// cannot separate from the chain.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The EH
// data is a DIR32 relocation site the byte gate takes from the target; the base
// destructors are REL32 and are pinned in targets/game/reverse/symbols.csv.

class BigChainVictim
{
public:
	virtual ~BigChainVictim();
};

class BigChainHold
{
public:
	BigChainVictim *m_p;
	~BigChainHold() { if ( m_p ) delete m_p; }
};

#define BFME_CHAIN_SECOND_BASE( ADDR )                                    \
	class Sub##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		~Sub##ADDR();                                                     \
	};

#define BFME_CHAIN_DTOR( NAME, SECOND )                                   \
	class NAME : public BigChainHold, public SECOND                       \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
	};                                                                    \
	NAME::~NAME() {}

BFME_CHAIN_SECOND_BASE( 005C67C0 )
BFME_CHAIN_SECOND_BASE( 005C6890 )
BFME_CHAIN_SECOND_BASE( 005C6970 )
BFME_CHAIN_SECOND_BASE( 005C6A40 )

BFME_CHAIN_DTOR( Rva005C9D30, Sub005C67C0 )
BFME_CHAIN_DTOR( Rva005C9DC0, Sub005C6890 )

class BigChainPad
{
	int m_pad;
};

#define BFME_CHAIN_NESTED_SECOND_BASE( ADDR, TERMINAL )                   \
	class Sub##ADDR##Inner : public BigChainPad, public TERMINAL {};       \
	class Sub##ADDR##Outer : public BigChainPad, public Sub##ADDR##Inner {}; \
	class Sub##ADDR : public BigChainHold, public Sub##ADDR##Outer         \
	{                                                                     \
	public:                                                               \
		~Sub##ADDR();                                                     \
	};                                                                    \
	Sub##ADDR::~Sub##ADDR() {}

BFME_CHAIN_SECOND_BASE( 005C91C0 )
BFME_CHAIN_SECOND_BASE( 005C9240 )
BFME_CHAIN_SECOND_BASE( 005C9E30 )
BFME_CHAIN_SECOND_BASE( 005C9EC0 )
BFME_CHAIN_SECOND_BASE( 005CB030 )
BFME_CHAIN_SECOND_BASE( 005CB0C0 )
BFME_CHAIN_SECOND_BASE( 005CBD40 )
BFME_CHAIN_SECOND_BASE( 005CBDD0 )
BFME_CHAIN_SECOND_BASE( 005CC980 )
BFME_CHAIN_SECOND_BASE( 005CD260 )
BFME_CHAIN_NESTED_SECOND_BASE( 005CD540, Rva005C9D30 )
BFME_CHAIN_NESTED_SECOND_BASE( 005CD5E0, Rva005C9DC0 )
BFME_CHAIN_SECOND_BASE( 005CD660 )
BFME_CHAIN_SECOND_BASE( 005CD700 )
BFME_CHAIN_SECOND_BASE( 005CDA10 )
BFME_CHAIN_SECOND_BASE( 005CDAA0 )
BFME_CHAIN_SECOND_BASE( 005CDB10 )
BFME_CHAIN_SECOND_BASE( 005CDBB0 )
BFME_CHAIN_SECOND_BASE( 005CDEF0 )
BFME_CHAIN_SECOND_BASE( 005CDF80 )

BFME_CHAIN_DTOR( Rva005C91C0, Sub005C6A40 )
BFME_CHAIN_DTOR( Rva005C9240, Sub005C6970 )
BFME_CHAIN_DTOR( Rva005C9E30, Sub005C91C0 )
BFME_CHAIN_DTOR( Rva005C9EC0, Sub005C9240 )
BFME_CHAIN_DTOR( Rva005CB030, Sub005C9E30 )
BFME_CHAIN_DTOR( Rva005CB0C0, Sub005C9EC0 )
BFME_CHAIN_DTOR( Rva005CBD40, Sub005CB030 )
BFME_CHAIN_DTOR( Rva005CBDD0, Sub005CB0C0 )
BFME_CHAIN_DTOR( Rva005CC980, Sub005CBD40 )
BFME_CHAIN_DTOR( Rva005CD260, Sub005CBDD0 )
BFME_CHAIN_DTOR( Rva005CD660, Sub005CC980 )
BFME_CHAIN_DTOR( Rva005CD700, Sub005CD260 )
BFME_CHAIN_DTOR( Rva005CDA10, Sub005CD540 )
BFME_CHAIN_DTOR( Rva005CDAA0, Sub005CD5E0 )
BFME_CHAIN_DTOR( Rva005CDB10, Sub005CD660 )
BFME_CHAIN_DTOR( Rva005CDBB0, Sub005CD700 )
BFME_CHAIN_DTOR( Rva005CDEF0, Sub005CDA10 )
BFME_CHAIN_DTOR( Rva005CDF80, Sub005CDAA0 )
BFME_CHAIN_DTOR( Rva005CDFF0, Sub005CDB10 )
BFME_CHAIN_DTOR( Rva005CE3B0, Sub005CDBB0 )
BFME_CHAIN_DTOR( Rva005CE820, Sub005CDEF0 )
BFME_CHAIN_DTOR( Rva005CE920, Sub005CDF80 )

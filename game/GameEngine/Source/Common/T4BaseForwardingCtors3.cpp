// Twelve more rows of the base-forwarding constructor family that
// game/GameEngine/Source/Common/T1BaseForwardingCtors.cpp already documents,
// found in the 0x005E97B0..0x0060D680 slice.  They are the SAME first base --
// every one of them calls 0x005DD290, the constructor T1 named
// T1A1_005DD290 -- carrying one more secondary base than T1's three rows of
// that shape did.  Retail, the 60-byte arity:
//
//     mov eax,[esp+8] / push esi / mov esi,ecx / mov ecx,[esp+8]
//     push eax / push ecx / mov ecx,esi / call 0x005DD290
//     mov [esi+0x14],<VB1>        ; second base's OWN vptr
//     mov [esi+0x18],<VB2>        ; third base's OWN vptr
//     mov [esi],     <V0>         ; the derived class stamps all three
//     mov [esi+0x14],<V1>
//     mov [esi+0x18],<V2>
//     mov eax,esi / pop esi / ret 8
//
// WHAT THE BYTES SHOW.  The two arguments are re-pushed unchanged in
// __thiscall order and nothing is read out of them, so the body is a
// member-initialiser forward; `mov eax,esi` before `ret 8` makes it a
// constructor.  The reading of the vptr stores is T1's and is not re-derived
// here: a slot written TWICE with two different addresses is a base installing
// its own vptr and the derived overwriting it, and MSVC 7.1 kills only the
// PRIMARY base's store, so a surviving store at +0x14 or +0x18 is a secondary
// base whose constructor was INLINED -- implicit or trivial, with no body to
// call.  Two surviving stores means two such bases; the single `call` is the
// first base, which is out of line and therefore declared without a body.
//
// THE OFFSETS ARE THE SAME ONES T1 MEASURED.  The first base runs 0x14 wide
// (vptr plus four dwords), the second is a bare vptr at 0x14, the third a bare
// vptr at 0x18.  That is why the first base is spelled here exactly as T1
// spells it: same class, same declaration, same already-pinned constructor.
//
// ONE CLASS PER DISTINCT VFTABLE ADDRESS.  The secondary bases are named after
// the address retail stores into their slot, following T1: seven distinct
// addresses appear at +0x14 and six at +0x18 across the twelve rows, and rows
// that store the same address get the same class rather than a private copy.
// The derived classes' own vftable dwords are DIR32 operands the build copies
// from retail; they are not evidence and nothing is asserted about them --
// what they force is only that all twelve derived classes differ.
//
// TWO ROWS ARE NOT THE PLAIN ARITY and both are informative:
//
//   0x005F2C60 (46 bytes) has only ONE surviving base store, at +0x14, so it
//   has one secondary base and no third.  It is byte-for-byte T1's
//   T1_FORWARDING_CTOR_2 shape against the same first base.
//
//   0x005FC8C0 (68 bytes) inserts `mov al,1 / mov [esi+0x1c],al /
//   mov [esi+0x1d],al` BETWEEN the surviving base stores and the derived
//   stamps.  Position is the whole argument: MSVC 7.1 emits a constructor as
//   base subobjects, then vptrs, then member initialisers, so anything that
//   lands BEFORE the vptr stamps cannot be a member of the derived class --
//   it is a further base subobject, one with no vptr and two bytes set true,
//   sitting at 0x1C directly after the bare vptr at 0x18.  Its sibling row
//   0x005FC870 stores the same +0x14 and +0x18 addresses and does NOT write
//   0x1C, which is what says the two bytes belong to a fourth base rather than
//   to the third: the third base's own constructor would have written them in
//   both rows.
//
// IDENTITY IS NOT RECOVERED.  No string, no RTTI and no named callee reaches
// these bodies; the first base's constructor is itself unclaimed.  Every name
// is derived from an address -- the row's own for a derived class, the stored
// vftable's for a secondary base.

// The first base, spelled exactly as T1BaseForwardingCtors.cpp spells it so
// that the call resolves through the constructor pin already in
// targets/game/reverse/symbols.csv.  Declaration only: retail's `call` proves it is defined
// in another translation unit.
class T1A1_005DD290
{
public:
	T1A1_005DD290( void *a, void *b );
	virtual void s0();
	int m_pad[ 4 ];
};

// A secondary base is a bare vptr.  Named after the vftable address retail
// stores through it.
#define T4_SECOND_BASE( VT )                                                  \
	class T4A2_##VT { public: virtual void s0(); };

// The fourth base of 0x005FC8C0: no vptr, two bytes set true by its own
// inlined constructor.
class T4A4_Flags2
{
public:
	T4A4_Flags2() : m_a( true ), m_b( true ) {}
	bool m_a;
	bool m_b;
};

// three vptrs: first base at 0, bare vptr bases at 0x14 and 0x18
#define T4_FORWARDING_CTOR_3( ROW, VT1, VT2 )                                 \
	class T4Derived_##ROW                                                     \
		: public T1A1_005DD290, public T4A2_##VT1, public T4A2_##VT2          \
	{                                                                         \
	public:                                                                   \
		T4Derived_##ROW( void *a, void *b );                                  \
	};                                                                        \
	T4Derived_##ROW::T4Derived_##ROW( void *a, void *b )                      \
		: T1A1_005DD290( a, b )                                               \
	{                                                                         \
	}

// two vptrs: first base at 0, one bare vptr base at 0x14
#define T4_FORWARDING_CTOR_2( ROW, VT1 )                                      \
	class T4Derived_##ROW                                                     \
		: public T1A1_005DD290, public T4A2_##VT1                             \
	{                                                                         \
	public:                                                                   \
		T4Derived_##ROW( void *a, void *b );                                  \
	};                                                                        \
	T4Derived_##ROW::T4Derived_##ROW( void *a, void *b )                      \
		: T1A1_005DD290( a, b )                                               \
	{                                                                         \
	}

// three vptrs plus the flag base at 0x1C
#define T4_FORWARDING_CTOR_3F( ROW, VT1, VT2 )                                \
	class T4Derived_##ROW                                                     \
		: public T1A1_005DD290, public T4A2_##VT1, public T4A2_##VT2,         \
		  public T4A4_Flags2                                                  \
	{                                                                         \
	public:                                                                   \
		T4Derived_##ROW( void *a, void *b );                                  \
	};                                                                        \
	T4Derived_##ROW::T4Derived_##ROW( void *a, void *b )                      \
		: T1A1_005DD290( a, b )                                               \
	{                                                                         \
	}

T4_SECOND_BASE( 01110898 )
T4_SECOND_BASE( 0111081C )
T4_SECOND_BASE( 01110830 )
T4_SECOND_BASE( 0111082C )
T4_SECOND_BASE( 01110834 )
T4_SECOND_BASE( 0111089C )
T4_SECOND_BASE( 0110F97C )
T4_SECOND_BASE( 0110F978 )
T4_SECOND_BASE( 01073760 )
T4_SECOND_BASE( 0107375C )
T4_SECOND_BASE( 0110F9E4 )
T4_SECOND_BASE( 0110FA14 )
T4_SECOND_BASE( 0110F9E8 )

T4_FORWARDING_CTOR_3( 005EEA10, 01110898, 0110F978 )
T4_FORWARDING_CTOR_3( 005EEB70, 01110898, 0110F978 )
T4_FORWARDING_CTOR_3( 005EFCC0, 0111081C, 01073760 )
T4_FORWARDING_CTOR_3( 005EFD10, 0111081C, 01073760 )
T4_FORWARDING_CTOR_3( 005FC870, 01110830, 0107375C )
T4_FORWARDING_CTOR_3( 005FDDE0, 0111082C, 0110F9E4 )
T4_FORWARDING_CTOR_3( 005FDE30, 0111082C, 0110F9E4 )
T4_FORWARDING_CTOR_3( 005FEA00, 01110834, 0110FA14 )
T4_FORWARDING_CTOR_3( 005FFB60, 0111089C, 0110F9E8 )
T4_FORWARDING_CTOR_3( 005FFD60, 0111089C, 0110F9E8 )

T4_FORWARDING_CTOR_2( 005F2C60, 0110F97C )

T4_FORWARDING_CTOR_3F( 005FC8C0, 01110830, 0107375C )

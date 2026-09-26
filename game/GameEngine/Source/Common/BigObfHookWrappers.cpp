// cl: /DNDEBUG /MD
// Thirty-two 100-byte __cdecl wrappers, one shape.  Retail:
//
//     hook = G.m_hook;                       ; G is a global at a fixed base
//     if (hook) goto hot;
//     if (G.m_alt) { hot: ... }
//     return real(a, b);                     ; out-of-line tail block
//   hot:
//     pa = G.m_a; pb = G.m_b;                ; G+0x88 and G+0x8C
//     State o(&a, &b);                       ; 32-byte local, __thiscall ctor
//     return hook(pa, pb, (__int64)(int)&o); ; __cdecl, four pushed dwords
//
// WHAT THE BYTES SHOW.  `mov esi,[G]` once, kept in esi across the constructor
// call, and `call esi` at the end: the hook is read into a LOCAL, not re-read at
// the call -- re-reading it emits `call dword ptr [G]` instead.  The same holds
// for [G+0x88] and [G+0x8C]: a global load cannot be hoisted across an unknown
// call, so ebx/edi being loaded BEFORE the constructor call and used after it
// means the source copied them into locals first.  All four loads sit at
// offsets 0, 4, 0x88 and 0x8C from ONE base in every one of the thirty-two
// members, which is what makes them one object rather than four globals.
//
// `lea eax,<local>` then `cdq` then `push edx`/`push eax` pushes a SIGN-EXTENDED
// 64-bit value built from the local's address, so the hook's third parameter is
// 64-bit and the source casts the pointer through a signed 32-bit integer.
//
// THE BLOCK ORDER IS WHY THE `goto` IS HERE, and it is the only thing that
// decided this spelling.  `if (hook || G.m_alt) { hot } return real(a,b);` and
// every if/else, early-return and nested-if rewriting of it compiles the
// FALLBACK block first and the hot block last; retail falls through the second
// test straight into the hot block and parks the fallback after the hot block's
// `ret`.  Only the `goto` into the second test's body reproduces that layout.
// The two spellings are semantically identical, so the bytes -- not taste --
// are what picked this one.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The four
// global loads are DIR32 relocation sites (the byte gate takes them from the
// target); the constructor and the fallback are REL32 and are pinned per
// member in targets/game/reverse/symbols.csv.  Ten distinct global bases are shared among
// the thirty-two members, so ten slot objects are declared, not thirty-two.

typedef int (__cdecl *BigObfHook)( void *, void *, __int64 );

struct BigObfSlot
{
	BigObfHook  m_hook;
	BigObfHook  m_alt;
	char        m_pad[ 0x80 ];
	void       *m_a;
	void       *m_b;
};

#define BFME_OBF_SLOT( BASE )                                             \
	extern BigObfSlot g_Slot##BASE;

#define BFME_OBF_STATE( ADDR )                                            \
	class Obf##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		Obf##ADDR( int *a, int *b );                                      \
		unsigned int m_bits[ 8 ];                                         \
	};

struct BigObfSelectorRecord
{
	unsigned int m_key[ 5 ];
	unsigned int m_seed[ 5 ];
};

// The constructors use the same two-bit selector helpers already recovered in
// Q3SelectorRecordReaders.cpp and R3SelectorRecordReadersEbp.cpp.  VC7.1 has
// no intrinsic for rdtsc, and neither esp nor ebp can be read as a C++ value,
// so these one-instruction selectors are the only non-C++ part of the bodies.
// The xor chain is ordinary C++; its final two inputs are intentionally the
// pre-existing object words, as the retail anti-tamper code reads them before
// writing them.

#define BFME_OBF_RECORD( ADDR )                                           \
	extern BigObfSelectorRecord g_ObfRecord##ADDR;

#define BFME_OBF_CTOR_BODY( ADDR, RECORD, SELECTOR, C1, C2, C3 )          \
	Obf##ADDR::Obf##ADDR( int *a, int *b )                                \
	{                                                                     \
		unsigned int selector = 0;                                         \
		SELECTOR                                                           \
		unsigned int index = selector & 3;                                 \
		unsigned int key = RECORD.m_key[ index ];                          \
		m_bits[ 0 ] = RECORD.m_seed[ index ];                              \
		m_bits[ 1 ] = C1;                                                  \
		m_bits[ 2 ] = C2;                                                  \
		m_bits[ 3 ] = C3;                                                  \
		m_bits[ 4 ] = *a;                                                  \
		m_bits[ 5 ] = *b;                                                  \
		m_bits[ 1 ] ^= key * key;                                          \
		m_bits[ 2 ] ^= m_bits[ 1 ] * key;                                 \
		m_bits[ 3 ] ^= m_bits[ 2 ] * key;                                 \
		m_bits[ 4 ] ^= m_bits[ 3 ] * key;                                 \
		m_bits[ 5 ] ^= m_bits[ 4 ] * key;                                 \
		m_bits[ 6 ] ^= m_bits[ 5 ] * key;                                 \
		m_bits[ 7 ] ^= m_bits[ 6 ] * key;                                 \
	}

#define BFME_OBF_SELECT_STACK __asm { mov selector, esp }
#define BFME_OBF_SELECT_FRAME __asm { mov selector, ebp }
#define BFME_OBF_SELECT_TIMESTAMP __asm { rdtsc } __asm { mov selector, eax }

#define BFME_OBF_FALLBACK( ADDR )                                         \
	int __cdecl Gen##ADDR( int a, int b );

#define BFME_OBF_WRAPPER( NAME, SLOT, STATE, FALLBACK )                   \
	int __cdecl NAME( int a, int b )                                      \
	{                                                                     \
		BigObfHook hook = SLOT.m_hook;                                    \
		if ( hook )                                                       \
			goto hot;                                                     \
		if ( SLOT.m_alt )                                                 \
		{                                                                 \
	hot:                                                                  \
			void *pa = SLOT.m_a;                                          \
			void *pb = SLOT.m_b;                                          \
			STATE o( &a, &b );                                            \
			return hook( pa, pb, (__int64)(int)&o );                      \
		}                                                                 \
		return FALLBACK( a, b );                                          \
	}

BFME_OBF_SLOT( 012BC544 )
BFME_OBF_SLOT( 012BC6C8 )
BFME_OBF_SLOT( 012BC84C )
BFME_OBF_SLOT( 012BCB54 )
BFME_OBF_SLOT( 012BCFE0 )
BFME_OBF_SLOT( 012BD774 )
BFME_OBF_SLOT( 012BE394 )
BFME_OBF_SLOT( 012BEE30 )
BFME_OBF_SLOT( 012BF440 )
BFME_OBF_SLOT( 012C233C )

BFME_OBF_STATE( 00062D90 )
BFME_OBF_STATE( 00076550 )
BFME_OBF_STATE( 00076630 )
BFME_OBF_STATE( 00076710 )
BFME_OBF_STATE( 000767F0 )
BFME_OBF_STATE( 0009A430 )
BFME_OBF_STATE( 003881E0 )
BFME_OBF_STATE( 003882C0 )
BFME_OBF_STATE( 003C86C0 )
BFME_OBF_STATE( 003C87A0 )
BFME_OBF_STATE( 00526C80 )
BFME_OBF_STATE( 00526D60 )
BFME_OBF_STATE( 00526E40 )
BFME_OBF_STATE( 00526F20 )
BFME_OBF_STATE( 0054DBC0 )
BFME_OBF_STATE( 0054DCA0 )
BFME_OBF_STATE( 0054DD80 )
BFME_OBF_STATE( 0054DE60 )
BFME_OBF_STATE( 0054DF40 )
BFME_OBF_STATE( 0054E020 )
BFME_OBF_STATE( 0054E100 )
BFME_OBF_STATE( 0054E1E0 )
BFME_OBF_STATE( 0054E2C0 )
BFME_OBF_STATE( 0054E3A0 )
BFME_OBF_STATE( 0056D5E0 )
BFME_OBF_STATE( 0056D6C0 )
BFME_OBF_STATE( 0056D7A0 )
BFME_OBF_STATE( 0056D880 )
BFME_OBF_STATE( 00590A70 )
BFME_OBF_STATE( 00590B50 )
BFME_OBF_STATE( 00590C30 )
BFME_OBF_STATE( 00619E50 )

BFME_OBF_RECORD( 012A6FF4 )
BFME_OBF_RECORD( 012A72DC )
BFME_OBF_RECORD( 012A7304 )
BFME_OBF_RECORD( 012A732C )
BFME_OBF_RECORD( 012A7354 )
BFME_OBF_RECORD( 012A7D38 )
BFME_OBF_RECORD( 012B446C )
BFME_OBF_RECORD( 012B4494 )
BFME_OBF_RECORD( 012B4864 )
BFME_OBF_RECORD( 012B488C )
BFME_OBF_RECORD( 012B7710 )
BFME_OBF_RECORD( 012B7738 )
BFME_OBF_RECORD( 012B7760 )
BFME_OBF_RECORD( 012B7788 )
BFME_OBF_RECORD( 012B79A4 )
BFME_OBF_RECORD( 012B79CC )
BFME_OBF_RECORD( 012B79F4 )
BFME_OBF_RECORD( 012B7A1C )
BFME_OBF_RECORD( 012B7A44 )
BFME_OBF_RECORD( 012B7A6C )
BFME_OBF_RECORD( 012B7A94 )
BFME_OBF_RECORD( 012B7ABC )
BFME_OBF_RECORD( 012B7E70 )
BFME_OBF_RECORD( 012B7E98 )
BFME_OBF_RECORD( 012B7EC0 )
BFME_OBF_RECORD( 012B7EE8 )
BFME_OBF_RECORD( 012B829C )
BFME_OBF_RECORD( 012B82C4 )
BFME_OBF_RECORD( 012B82EC )
BFME_OBF_RECORD( 012B90B8 )

BFME_OBF_CTOR_BODY( 00062D90, g_ObfRecord012A6FF4, BFME_OBF_SELECT_TIMESTAMP, 0x548C1284, 0x548C1280, 0x548C1284 )
BFME_OBF_CTOR_BODY( 00076550, g_ObfRecord012A72DC, BFME_OBF_SELECT_FRAME, 0x008C0A84, 0x008C0A80, 0x1C0C404F )
BFME_OBF_CTOR_BODY( 00076630, g_ObfRecord012A7304, BFME_OBF_SELECT_STACK, 0x008C0A84, 0x008C0A80, 0x008C0A84 )
BFME_OBF_CTOR_BODY( 00076710, g_ObfRecord012A732C, BFME_OBF_SELECT_FRAME, 0x008C0A84, 0x008C0A80, 0x0C844203 )
BFME_OBF_CTOR_BODY( 000767F0, g_ObfRecord012A7354, BFME_OBF_SELECT_STACK, 0x008C0A84, 0x008C0A80, 0x502808C8 )
BFME_OBF_CTOR_BODY( 0009A430, g_ObfRecord012A7D38, BFME_OBF_SELECT_TIMESTAMP, 0x548C1284, 0x548C1280, 0x40801A08 )
BFME_OBF_CTOR_BODY( 003881E0, g_ObfRecord012B446C, BFME_OBF_SELECT_TIMESTAMP, 0x408C1281, 0x408C1285, 0x408C1281 )
BFME_OBF_CTOR_BODY( 003882C0, g_ObfRecord012B4494, BFME_OBF_SELECT_TIMESTAMP, 0x408C1281, 0x408C1285, 0x5C84428D )
BFME_OBF_CTOR_BODY( 003C86C0, g_ObfRecord012B4864, BFME_OBF_SELECT_STACK, 0x140C4A01, 0x140C4A05, 0x140C4A01 )
BFME_OBF_CTOR_BODY( 003C87A0, g_ObfRecord012B488C, BFME_OBF_SELECT_STACK, 0x140C4A01, 0x140C4A05, 0x54A008CD )
BFME_OBF_CTOR_BODY( 00526C80, g_ObfRecord012B7710, BFME_OBF_SELECT_FRAME, 0x10AC50C0, 0x14804842, 0x04241A4F )
BFME_OBF_CTOR_BODY( 00526D60, g_ObfRecord012B7738, BFME_OBF_SELECT_STACK, 0x10AC50C0, 0x14804842, 0x10AC50C0 )
BFME_OBF_CTOR_BODY( 00526E40, g_ObfRecord012B7760, BFME_OBF_SELECT_FRAME, 0x10AC50C0, 0x14804842, 0x14804843 )
BFME_OBF_CTOR_BODY( 00526F20, g_ObfRecord012B7788, BFME_OBF_SELECT_STACK, 0x10AC50C0, 0x14804842, 0x00001ACC )
BFME_OBF_CTOR_BODY( 0054DBC0, g_ObfRecord012B79A4, BFME_OBF_SELECT_STACK, 0x0C841840, 0x14AC1A82, 0x04044AD0 )
BFME_OBF_CTOR_BODY( 0054DCA0, g_ObfRecord012B79CC, BFME_OBF_SELECT_STACK, 0x18245AC1, 0x18245AC5, 0x0C24180A )
BFME_OBF_CTOR_BODY( 0054DD80, g_ObfRecord012B79F4, BFME_OBF_SELECT_TIMESTAMP, 0x0C840885, 0x0C840881, 0x48845055 )
BFME_OBF_CTOR_BODY( 0054DE60, g_ObfRecord012B79F4, BFME_OBF_SELECT_TIMESTAMP, 0x0C840885, 0x100C1887, 0x48845055 )
BFME_OBF_CTOR_BODY( 0054DF40, g_ObfRecord012B7A1C, BFME_OBF_SELECT_STACK, 0x0C841840, 0x14AC1A82, 0x0C841840 )
BFME_OBF_CTOR_BODY( 0054E020, g_ObfRecord012B7A44, BFME_OBF_SELECT_STACK, 0x18245AC1, 0x18245AC5, 0x488C00C6 )
BFME_OBF_CTOR_BODY( 0054E100, g_ObfRecord012B7A6C, BFME_OBF_SELECT_TIMESTAMP, 0x18245AC1, 0x18245AC5, 0x18245AC1 )
BFME_OBF_CTOR_BODY( 0054E1E0, g_ObfRecord012B7A94, BFME_OBF_SELECT_TIMESTAMP, 0x0C840885, 0x0C840881, 0x0C840885 )
BFME_OBF_CTOR_BODY( 0054E2C0, g_ObfRecord012B7A94, BFME_OBF_SELECT_TIMESTAMP, 0x0C840885, 0x100C1887, 0x0C840885 )
BFME_OBF_CTOR_BODY( 0054E3A0, g_ObfRecord012B7ABC, BFME_OBF_SELECT_TIMESTAMP, 0x18245AC1, 0x18245AC5, 0x5C80520D )
BFME_OBF_CTOR_BODY( 0056D5E0, g_ObfRecord012B7E70, BFME_OBF_SELECT_STACK, 0x0C281240, 0x48000A06, 0x14A8024B )
BFME_OBF_CTOR_BODY( 0056D6C0, g_ObfRecord012B7E98, BFME_OBF_SELECT_TIMESTAMP, 0x0C281240, 0x48000A06, 0x0C281240 )
BFME_OBF_CTOR_BODY( 0056D7A0, g_ObfRecord012B7EC0, BFME_OBF_SELECT_STACK, 0x0C281240, 0x48000A06, 0x48000A07 )
BFME_OBF_CTOR_BODY( 0056D880, g_ObfRecord012B7EE8, BFME_OBF_SELECT_TIMESTAMP, 0x0C281240, 0x48000A06, 0x1800024C )
BFME_OBF_CTOR_BODY( 00590A70, g_ObfRecord012B829C, BFME_OBF_SELECT_STACK, 0x04A85801, 0x04A85805, 0x5C881090 )
BFME_OBF_CTOR_BODY( 00590B50, g_ObfRecord012B82C4, BFME_OBF_SELECT_FRAME, 0x04A85801, 0x04A85805, 0x04A85801 )
BFME_OBF_CTOR_BODY( 00590C30, g_ObfRecord012B82EC, BFME_OBF_SELECT_FRAME, 0x04A85801, 0x04A85805, 0x0080028D )
BFME_OBF_CTOR_BODY( 00619E50, g_ObfRecord012B90B8, BFME_OBF_SELECT_TIMESTAMP, 0x140C4A01, 0x140C4A05, 0x14204A50 )

BFME_OBF_FALLBACK( 00061F00 )
BFME_OBF_FALLBACK( 0006EF90 )
BFME_OBF_FALLBACK( 0006F0D0 )
BFME_OBF_FALLBACK( 0006F200 )
BFME_OBF_FALLBACK( 0006F330 )
BFME_OBF_FALLBACK( 00098C80 )
BFME_OBF_FALLBACK( 003859B0 )
BFME_OBF_FALLBACK( 00385AE0 )
BFME_OBF_FALLBACK( 003C7780 )
BFME_OBF_FALLBACK( 003C78B0 )
BFME_OBF_FALLBACK( 00525450 )
BFME_OBF_FALLBACK( 00525590 )
BFME_OBF_FALLBACK( 005256D0 )
BFME_OBF_FALLBACK( 00525800 )
BFME_OBF_FALLBACK( 0054BCA0 )
BFME_OBF_FALLBACK( 0054BDD0 )
BFME_OBF_FALLBACK( 0054BF00 )
BFME_OBF_FALLBACK( 0054C030 )
BFME_OBF_FALLBACK( 0054C170 )
BFME_OBF_FALLBACK( 0054C2B0 )
BFME_OBF_FALLBACK( 0054C3E0 )
BFME_OBF_FALLBACK( 0054C510 )
BFME_OBF_FALLBACK( 0054C640 )
BFME_OBF_FALLBACK( 0054C780 )
BFME_OBF_FALLBACK( 0056C3F0 )
BFME_OBF_FALLBACK( 0056C530 )
BFME_OBF_FALLBACK( 0056C670 )
BFME_OBF_FALLBACK( 0056C7A0 )
BFME_OBF_FALLBACK( 0058C6C0 )
BFME_OBF_FALLBACK( 0058C7F0 )
BFME_OBF_FALLBACK( 0058C920 )
BFME_OBF_FALLBACK( 00619540 )

BFME_OBF_WRAPPER( Rva00062EF0, g_Slot012C233C, Obf00062D90, Gen00061F00 )
BFME_OBF_WRAPPER( Rva00077140, g_Slot012BC544, Obf00076550, Gen0006EF90 )
BFME_OBF_WRAPPER( Rva000771C0, g_Slot012BC544, Obf00076630, Gen0006F0D0 )
BFME_OBF_WRAPPER( Rva00077240, g_Slot012BC544, Obf00076710, Gen0006F200 )
BFME_OBF_WRAPPER( Rva000772C0, g_Slot012BC544, Obf000767F0, Gen0006F330 )
BFME_OBF_WRAPPER( Rva0009B4B0, g_Slot012C233C, Obf0009A430, Gen00098C80 )
BFME_OBF_WRAPPER( Rva003897C0, g_Slot012BC84C, Obf003881E0, Gen003859B0 )
BFME_OBF_WRAPPER( Rva00389840, g_Slot012BC84C, Obf003882C0, Gen00385AE0 )
BFME_OBF_WRAPPER( Rva003C9220, g_Slot012BE394, Obf003C86C0, Gen003C7780 )
BFME_OBF_WRAPPER( Rva003C92A0, g_Slot012BE394, Obf003C87A0, Gen003C78B0 )
BFME_OBF_WRAPPER( Rva00527730, g_Slot012BD774, Obf00526C80, Gen00525450 )
BFME_OBF_WRAPPER( Rva005277B0, g_Slot012BD774, Obf00526D60, Gen00525590 )
BFME_OBF_WRAPPER( Rva00527830, g_Slot012BD774, Obf00526E40, Gen005256D0 )
BFME_OBF_WRAPPER( Rva005278B0, g_Slot012BD774, Obf00526F20, Gen00525800 )
BFME_OBF_WRAPPER( Rva0054E560, g_Slot012BCB54, Obf0054DBC0, Gen0054BCA0 )
BFME_OBF_WRAPPER( Rva0054E5E0, g_Slot012BCFE0, Obf0054DCA0, Gen0054BDD0 )
BFME_OBF_WRAPPER( Rva0054E660, g_Slot012BEE30, Obf0054DD80, Gen0054BF00 )
BFME_OBF_WRAPPER( Rva0054E6E0, g_Slot012BEE30, Obf0054DE60, Gen0054C030 )
BFME_OBF_WRAPPER( Rva0054E760, g_Slot012BCB54, Obf0054DF40, Gen0054C170 )
BFME_OBF_WRAPPER( Rva0054E7E0, g_Slot012BCFE0, Obf0054E020, Gen0054C2B0 )
BFME_OBF_WRAPPER( Rva0054E860, g_Slot012BCFE0, Obf0054E100, Gen0054C3E0 )
BFME_OBF_WRAPPER( Rva0054E8E0, g_Slot012BEE30, Obf0054E1E0, Gen0054C510 )
BFME_OBF_WRAPPER( Rva0054E960, g_Slot012BEE30, Obf0054E2C0, Gen0054C640 )
BFME_OBF_WRAPPER( Rva0054E9E0, g_Slot012BCFE0, Obf0054E3A0, Gen0054C780 )
BFME_OBF_WRAPPER( Rva0056DE40, g_Slot012BF440, Obf0056D5E0, Gen0056C3F0 )
BFME_OBF_WRAPPER( Rva0056DEC0, g_Slot012BF440, Obf0056D6C0, Gen0056C530 )
BFME_OBF_WRAPPER( Rva0056DF40, g_Slot012BF440, Obf0056D7A0, Gen0056C670 )
BFME_OBF_WRAPPER( Rva0056DFC0, g_Slot012BF440, Obf0056D880, Gen0056C7A0 )
BFME_OBF_WRAPPER( Rva00592FE0, g_Slot012BC6C8, Obf00590A70, Gen0058C6C0 )
BFME_OBF_WRAPPER( Rva00593060, g_Slot012BC6C8, Obf00590B50, Gen0058C7F0 )
BFME_OBF_WRAPPER( Rva005930E0, g_Slot012BC6C8, Obf00590C30, Gen0058C920 )
BFME_OBF_WRAPPER( Rva0061A350, g_Slot012BE394, Obf00619E50, Gen00619540 )

// Forty-one very small bodies that the mnemonic-only grouper collected into
// three families (anchors 0x00061580, 0x000E9280 and 0x00061180) but which are
// NOT three shapes.  Grouping by mnemonic sequence alone discards operands,
// registers and instruction lengths, so "load / load / store / ret" gathers a
// stack-argument array read, a back-reference field copy and a member swap into
// one bucket.  Each block below is a SEPARATE shape, named for what the bytes
// show and nothing more.  Where a block holds several members they differ only
// in offsets and constants, and every one of them was compared byte for byte.
//
// IDENTITY IS NOT RECOVERED ANYWHERE IN THIS FILE.  Every class, member,
// function and extern name is derived from an address.  Absolute addresses are
// DIR32 sites the patcher fills from retail; the extern names carry no type
// information and are only there to make the site a relocation.

// ---------------------------------------------------------------------------
// (1) Free functions that index an array inside a pointed-to object:
//
//     mov eax,[esp+8] / mov ecx,[esp+4] / mov eax,[ecx+eax*4+<BASE>] / ret
//
// A bare `ret` with both arguments still on the stack is __cdecl.  The index is
// scaled by four and added to a fixed base, so the array element is four bytes
// wide; the result is that element.  The INDEX IS LOADED FIRST, which is the
// order the address computation needs and says nothing about the source.

#define R2_INDEXED_ELEMENT_READ( NAME, BASE )                             \
	class NAME##Owner                                                     \
	{                                                                     \
	public:                                                               \
		char m_leading[ BASE ];                                           \
		void *m_slot[ 1 ];                                                \
	};                                                                    \
	void *NAME( NAME##Owner *owner, int index )                           \
	{                                                                     \
		return owner->m_slot[ index ];                                    \
	}

R2_INDEXED_ELEMENT_READ( Rva0084DE00, 0x0C )
R2_INDEXED_ELEMENT_READ( Rva0084DE10, 0x3C )
R2_INDEXED_ELEMENT_READ( Rva0084DE20, 0x6C )

// ---------------------------------------------------------------------------
// (2) Free functions that store their second argument into a field of the
// first:
//
//     mov eax,[esp+8] / mov ecx,[esp+4] / mov [ecx+<FIELD>],eax / ret
//
// Same convention, no result.

#define R2_FIELD_WRITE( NAME, FIELD )                                     \
	class NAME##Owner                                                     \
	{                                                                     \
	public:                                                               \
		char m_leading[ FIELD ];                                          \
		int m_value;                                                      \
	};                                                                    \
	void NAME( NAME##Owner *owner, int value )                            \
	{                                                                     \
		owner->m_value = value;                                           \
	}

R2_FIELD_WRITE( Rva009A5E90, 0x6C )
R2_FIELD_WRITE( Rva009A5EA0, 0xC0 )
R2_FIELD_WRITE( Rva009A5EB0, 0xC4 )

// ---------------------------------------------------------------------------
// (3) Two __thiscall members that set two one-byte flags to true:
//
//     mov al,1 / mov [ecx+<A>],al / mov [ecx+<B>],al / ret
//
// `mov al,1` -- two bytes, not the five-byte `mov eax,1` -- and no use of eax
// afterwards: the constant is only there to be stored, so nothing is returned.
// 0x006F75F0 WRITES THE HIGHER OFFSET FIRST, which is source order, not
// scheduling; 0x002818F0 ascends.

#define R2_SET_TWO_FLAGS( NAME, FIRST, SECOND )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ FIRST < SECOND ? FIRST : SECOND ];                \
		bool m_low;                                                       \
		bool m_high;                                                      \
		void run();                                                       \
	};

R2_SET_TWO_FLAGS( Rva002818F0, 8, 9 )
void Rva002818F0::run() { m_low = true; m_high = true; }

R2_SET_TWO_FLAGS( Rva006F75F0, 0x29, 0x2A )
void Rva006F75F0::run() { m_high = true; m_low = true; }

// ---------------------------------------------------------------------------
// (4) Four parameterless functions that write one flag through a GLOBAL
// POINTER and return 1:
//
//     mov ecx,[0x012ED5C8] / mov eax,1 / mov [ecx+<FIELD>],al / ret
//
// Three set the flag and one clears it (0x000615A0, `mov byte [eax+0x8E],0`,
// with the `mov eax,1` moved after the store because zero is not in eax).  The
// five-byte `mov eax,1` where a two-byte `mov al,1` would serve is the same
// evidence as in R2GlobalOptionFlagSetters: eax is the RESULT and is four bytes
// wide, and al is reused for the store only because the value coincides.
// All four read the SAME global at 0x012ED5C8, so they share one pointee.

class R2Pointee012ED5C8
{
public:
	char m_leadingA[ 0x8E ];
	bool m_at8E;
	bool m_at8F;
	bool m_at90;
	char m_leadingB[ 0x1278 - 0x91 ];
	bool m_at1278;
};
extern R2Pointee012ED5C8 *R2Ptr012ED5C8;

int Rva00061580() { R2Ptr012ED5C8->m_at8F = true; return 1; }
int Rva000615A0() { R2Ptr012ED5C8->m_at8E = false; return 1; }
int Rva000615C0() { R2Ptr012ED5C8->m_at90 = true; return 1; }
int Rva000615F0() { R2Ptr012ED5C8->m_at1278 = true; return 1; }

// ---------------------------------------------------------------------------
// (5) Members that copy one field out of an object held in a global pointer:
//
//     mov eax,[0x012F0898] / mov edx,[eax+0x3C] / mov [ecx+<FIELD>],edx / ret
//
// The same global and the same source field at +0x3C in all four uses below
// (two here, two in block (11)), so one pointee serves them all.

class R2Pointee012F0898
{
public:
	char m_leading[ 0x3C ];
	int m_at3C;
};
extern R2Pointee012F0898 *R2Ptr012F0898;

#define R2_COPY_FROM_GLOBAL( NAME, FIELD )                                \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ FIELD ];                                          \
		int m_value;                                                      \
		void run();                                                       \
	};                                                                    \
	void NAME::run()                                                      \
	{                                                                     \
		m_value = R2Ptr012F0898->m_at3C;                                  \
	}

R2_COPY_FROM_GLOBAL( Rva0018C910, 0xA0 )
R2_COPY_FROM_GLOBAL( Rva00336D30, 0x170DC )

// ---------------------------------------------------------------------------
// (6) Two members that copy a field out of an object reached at a NEGATIVE
// displacement off `this`:
//
//     mov eax,[ecx-<BACK>] / mov edx,[eax+<SOURCE>] / mov [ecx+<DEST>],edx
//
// A negative displacement cannot be spelled as a member, so these are written
// the way BackPointerGuardedDispatch writes the same construct: a fixed byte
// offset back out of the object.  THE BYTES DECIDE THE OFFSET AND NOTHING ELSE.
// 0x002214C0 moves a BYTE (`mov dl,[eax+0x154]` / `mov [ecx+0x96],dl`).

class Rva00219CF0Pointee
{
public:
	char m_leading[ 0x168 ];
	int m_value;
};
class Rva00219CF0
{
public:
	char m_leading[ 0xA8 ];
	int m_value;
	void run();
};
void Rva00219CF0::run()
{
	m_value = ( *(Rva00219CF0Pointee **)( (char *)this - 0x30 ) )->m_value;
}

class Rva002214C0Pointee
{
public:
	char m_leading[ 0x154 ];
	char m_value;
};
class Rva002214C0
{
public:
	char m_leading[ 0x96 ];
	char m_value;
	void run();
};
void Rva002214C0::run()
{
	m_value = ( *(Rva002214C0Pointee **)( (char *)this - 0x1C ) )->m_value;
}

// ---------------------------------------------------------------------------
// (7) Small member assignments with no calls and no returned `this`.

class Rva0027F3F0
{
public:
	char m_leading[ 0x50 ];
	int m_at50;
	int m_at54;
	void run();
};
void Rva0027F3F0::run() { m_at54 = m_at50; m_at50 = 4; }

class Rva003BCAE0
{
public:
	char m_leadingA[ 0x78 ];
	bool m_at78;
	char m_leadingB[ 0xC8 - 0x79 ];
	bool m_atC8;
	char m_leadingC[ 3 ];
	int m_atCC;
	void run();
};
void Rva003BCAE0::run() { m_at78 = false; m_atC8 = true; m_atCC = 0x78; }

class Rva004223B0
{
public:
	float m_at00;
	float m_at04;
	char m_leading[ 0x14 - 8 ];
	bool m_at14;
	void run();
	bool isNonNegative() const;
};
void Rva004223B0::run() { m_at00 = -1.0f; m_at04 = -1.0f; m_at14 = false; }

bool Rva004223B0::isNonNegative() const
{
	return m_at04 >= 0.0f;
}

class Rva0045BFD0
{
public:
	char m_leading[ 0x8C ];
	int m_at8C;
	int m_at90;
	void run();
};
void Rva0045BFD0::run() { m_at8C = -1; m_at90 = -1; }

class Rva009A8C30Owner
{
public:
	char m_leading[ 0x1C0 ];
	int m_at1C0;
	int m_at1C4;
};
void Rva009A8C30( Rva009A8C30Owner *owner )
{
	owner->m_at1C0 = 8;
	owner->m_at1C4 = 8;
}

// ---------------------------------------------------------------------------
// (8) Constructors.  `mov eax,ecx` defining eax, never reading it again, and a
// bare `ret` is the __thiscall constructor tail returning `this`; every body in
// this block has it and no body outside this block does.

class Rva00299770
{
public:
	char m_leading[ 0x9C ];
	float m_at9C;
	bool m_atA0;
	Rva00299770();
};
Rva00299770::Rva00299770() { m_at9C = 20.0f; m_atA0 = false; }

extern int R2Data010CE518;
class Rva002D9B80
{
public:
	void *m_at00;
	bool m_at04;
	Rva002D9B80();
};
Rva002D9B80::Rva002D9B80() { m_at00 = &R2Data010CE518; m_at04 = false; }

class Rva003BC830
{
public:
	bool m_at00;
	bool m_at01;
	Rva003BC830();
};
Rva003BC830::Rva003BC830() { m_at00 = true; m_at01 = false; }

class Rva000E9280
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	Rva000E9280();
};
Rva000E9280::Rva000E9280() { m_at00 = 0; m_at04 = 0; m_at08 = 3; }

class Rva004224C0
{
public:
	float m_at00;
	int m_at04;
	int m_at08;
	Rva004224C0();
};
Rva004224C0::Rva004224C0() { m_at00 = 1000.0f; m_at04 = 15; m_at08 = 35; }

class Rva00422B50
{
public:
	float m_at00;
	float m_at04;
	char m_leading[ 0x14 - 8 ];
	bool m_at14;
	Rva00422B50();
};
Rva00422B50::Rva00422B50() { m_at00 = -1.0f; m_at04 = -1.0f; m_at14 = false; }

// ---------------------------------------------------------------------------
// (9) Three bodies that write through a pointer the object holds.

class Rva004C1280
{
public:
	int *m_target;
	void *m_result;
	void *run();
};
void *Rva004C1280::run() { *m_target = 0; return m_result; }

class Rva000CBA00Pointee
{
public:
	void *m_at00;
	char m_leading[ 8 ];
	void *m_at0C;
};
class Rva000CBA00
{
public:
	Rva000CBA00Pointee *m_pointee;
	void run();
};
void Rva000CBA00::run() { m_pointee->m_at0C = m_pointee->m_at00; }

class Rva0079D090Pointee
{
public:
	void *m_at00;
};
class Rva0079D090
{
public:
	Rva0079D090Pointee *m_pointee;
	void *m_value;
	void run();
};
void Rva0079D090::run() { m_pointee->m_at00 = m_value; }

// ---------------------------------------------------------------------------
// (10) Four parameterless functions that publish an address into one global,
// set another global to 1 and return 1:
//
//     mov eax,1 / mov dword ptr [<SLOT>],<ADDRESS> / mov [<FLAG>],eax / ret
//
// `mov eax,1` is hoisted ahead of the first store because the second store uses
// the short accumulator form; that is scheduling.  As in block (4), paying five
// bytes for the constant is what makes the result four bytes wide.  Both
// globals and the stored address are DIR32 sites.

#define R2_PUBLISH_AND_FLAG( NAME, SLOT, ADDRESS, FLAG )                  \
	int NAME()                                                            \
	{                                                                     \
		SLOT = &ADDRESS;                                                  \
		FLAG = 1;                                                         \
		return 1;                                                         \
	}

extern void *R2Glob012F9CB4;
extern void *R2Glob012F9C9C;
extern void *R2Glob012F9CC8;
extern void *R2Glob012F9CA0;
extern int R2Glob012F9C6C;
extern int R2Glob012F9C54;
extern int R2Glob012F9C80;
extern int R2Glob012F9C58;
extern int R2Data012BBF48;
extern int R2Data012BBF84;
extern int R2Data012BBF90;
extern int R2Data012BC080;

R2_PUBLISH_AND_FLAG( Rva007C3400, R2Glob012F9CB4, R2Data012BBF48, R2Glob012F9C6C )
R2_PUBLISH_AND_FLAG( Rva007C3F80, R2Glob012F9C9C, R2Data012BBF84, R2Glob012F9C54 )
R2_PUBLISH_AND_FLAG( Rva007C3FA0, R2Glob012F9CC8, R2Data012BBF90, R2Glob012F9C80 )
R2_PUBLISH_AND_FLAG( Rva007CC3D0, R2Glob012F9CA0, R2Data012BC080, R2Glob012F9C58 )

// ---------------------------------------------------------------------------
// (11) Two members that set one field and then copy the global's +0x3C into
// another -- block (5) with a leading store.

class Rva001BF100
{
public:
	char m_leading[ 0x3A8 ];
	bool m_flag;
	char m_padding[ 3 ];
	int m_value;
	void run();
};
void Rva001BF100::run() { m_flag = true; m_value = R2Ptr012F0898->m_at3C; }

class Rva001FC420
{
public:
	char m_leading[ 0x34 ];
	int m_at34;
	char m_padding[ 4 ];
	int m_at3C;
	void run();
};
void Rva001FC420::run() { m_at34 = 0; m_at3C = R2Ptr012F0898->m_at3C; }

// ---------------------------------------------------------------------------
// (12) Two member swaps:
//
//     mov eax,[ecx+<HIGH>] / mov edx,[ecx+<LOW>]
//     mov [ecx+<HIGH>],edx / mov [ecx+<LOW>],eax
//
// THE HIGH FIELD IS READ FIRST AND WRITTEN FIRST, so the temporary in the
// source holds the HIGH one: `t = high; high = low; low = t;`.  Writing it the
// other way round compiles to the same four instructions with the two offsets
// exchanged, and fails.

#define R2_SWAP_PAIR( NAME, LOW )                                         \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ LOW ];                                            \
		int m_low;                                                        \
		int m_high;                                                       \
		void run();                                                       \
	};                                                                    \
	void NAME::run()                                                      \
	{                                                                     \
		int held = m_high;                                                \
		m_high = m_low;                                                   \
		m_low = held;                                                     \
	}

R2_SWAP_PAIR( Rva001604F0, 4 )
R2_SWAP_PAIR( Rva001605E0, 0xC )

// ---------------------------------------------------------------------------
// (13) A two-field copy.  Both loads precede both stores, which is what two
// independent assignments produce; the compiler is free to schedule them.

class Rva0045B5D0
{
public:
	char m_leadingA[ 0x28 ];
	int m_at28;
	int m_at2C;
	char m_leadingB[ 0x48 - 0x30 ];
	int m_at48;
	int m_at4C;
	void run();
};
void Rva0045B5D0::run() { m_at28 = m_at48; m_at2C = m_at4C; }

// ---------------------------------------------------------------------------
// (14) Two members that publish an address into their own +0 and then copy
// their +4 through the pointer at their +8:
//
//     mov eax,[ecx+8] / mov [ecx],<ADDRESS> / mov ecx,[ecx+4] / mov [eax],ecx
//
// The load of +8 is hoisted ahead of the store to +0 because the store to +0
// would otherwise alias it; the source order is the store first.

#define R2_PUBLISH_AND_FORWARD( NAME, ADDRESS )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void *m_at00;                                                     \
		int m_at04;                                                       \
		int *m_at08;                                                      \
		void run();                                                       \
	};                                                                    \
	void NAME::run()                                                      \
	{                                                                     \
		m_at00 = &ADDRESS;                                                \
		*m_at08 = m_at04;                                                 \
	}

extern int R2Data010E75B0;
extern int R2Data010EE4EC;

R2_PUBLISH_AND_FORWARD( Rva00337750, R2Data010E75B0 )
R2_PUBLISH_AND_FORWARD( Rva003D67C0, R2Data010EE4EC )

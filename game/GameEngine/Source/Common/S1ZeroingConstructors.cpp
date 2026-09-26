// Nine __thiscall constructors whose whole body is "zero a fixed set of members
// and return this":
//
//     mov eax,ecx / xor ecx,ecx / mov [eax+<OFF>],ecx ... / ret
//
// WHAT THE BYTES SHOW.  Every one of the nine is fully concrete -- no
// relocation site anywhere -- so the offsets, the store widths and the store
// ORDER are all proven rather than copied.
//
//   * The leading `mov eax,ecx` defines eax and never reads it again: that is
//     the constructor's `this` return value, and its presence is what separates
//     these from a void resetter.
//   * The stores ASCEND through the object, so the source is a sequence of
//     separate `m_a = 0; m_b = 0;` statements, not a chained `m_a = m_b = 0`
//     -- a chain stores DESCENDING (verified by compiling both).
//   * The zero is materialised in a register (`xor ecx,ecx`, or `xor cl,cl`
//     when every store is byte-wide) instead of an immediate, which MSVC 7.1
//     only does once the member being written is far enough into the object
//     that the immediate form stops paying; a class whose FIRST member is at
//     offset 0 and has only two stores compiles to `mov dword ptr [eax],0`
//     instead, so the padding in front of these members is proven, not chosen.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; the char arrays are
// padding that reproduces a proven offset and make no claim about what else the
// object holds.  00351BC0 and 00351BD0 are byte-identical: the bytes cannot say
// whether that is one class constructed two ways or two classes alike.

// Two dword members zeroed, LEAD bytes of padding in front and GAP bytes
// between them.
#define BFME_ZERO_CTOR_2( NAME, LEAD, GAP )                               \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		char m_lead[ LEAD ];                                              \
		int m_a;                                                          \
		char m_gap[ GAP ];                                                \
		int m_b;                                                          \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_a = 0;                                                          \
		m_b = 0;                                                          \
	}

#define BFME_ZERO_CTOR_2_TIGHT( NAME, LEAD )                              \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		char m_lead[ LEAD ];                                              \
		int m_a;                                                          \
		int m_b;                                                          \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_a = 0;                                                          \
		m_b = 0;                                                          \
	}

BFME_ZERO_CTOR_2( Rva00351BC0, 8, 4 )
BFME_ZERO_CTOR_2( Rva00351BD0, 8, 4 )
BFME_ZERO_CTOR_2_TIGHT( Rva003A4300, 8 )
BFME_ZERO_CTOR_2_TIGHT( Rva003BEA20, 12 )
BFME_ZERO_CTOR_2_TIGHT( Rva003F6A60, 44 )

// Three dword members at 0, 4 and 12 -- no padding in front, so the first store
// is `mov [eax],ecx` with no displacement byte.
class Rva00339C20
{
public:
	Rva00339C20();
	int m_a;
	int m_b;
	char m_gap[ 4 ];
	int m_c;
};
Rva00339C20::Rva00339C20()
{
	m_a = 0;
	m_b = 0;
	m_c = 0;
}

// Three consecutive dword members starting at 8.
class Rva00739DE0
{
public:
	Rva00739DE0();
	char m_lead[ 8 ];
	int m_a;
	int m_b;
	int m_c;
};
Rva00739DE0::Rva00739DE0()
{
	m_a = 0;
	m_b = 0;
	m_c = 0;
}

// A dword at 0 followed by two bytes at 4 and 5: the store widths are read
// straight off the encodings (89 08 then 88 48 04 / 88 48 05).
class Rva003366B0
{
public:
	Rva003366B0();
	int m_a;
	unsigned char m_b;
	unsigned char m_c;
};
Rva003366B0::Rva003366B0()
{
	m_a = 0;
	m_b = 0;
	m_c = 0;
}

// Three byte members, two adjacent at 0 and 1 and one far out at 0x105.  Every
// store is byte-wide, so the register holding the zero is cleared with the
// 8-bit `xor cl,cl` rather than `xor ecx,ecx`.
class Rva007E3A20
{
public:
	Rva007E3A20();
	unsigned char m_a;
	unsigned char m_b;
	char m_gap[ 0x103 ];
	unsigned char m_c;
};
Rva007E3A20::Rva007E3A20()
{
	m_a = 0;
	m_b = 0;
	m_c = 0;
}

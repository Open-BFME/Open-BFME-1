// Five straight-line field initialisers grouped only by their MNEMONIC RUN --
// `mov base,this` then a wall of constant stores.  Four are __thiscall bodies
// that put `this` in eax and return it, which is what a CONSTRUCTOR does; one
// takes its object as a stack argument and is __cdecl.  The five have five
// different layouts and five different store orders, so this is one shape and
// five sources, not one source five times.
//
// WHAT THE BYTES SHOW, AND WHY THE ORDER IS EVIDENCE.  MSVC 7.1 does NOT
// reorder these stores -- a probe with the fields written in ascending order
// reproduced ascending order exactly.  So the emitted order IS the source
// order, and where retail's order is not the layout order, the source said so.
//
//   Rva006E18A0 is the sharpest case.  Its zeros come out descending in three
//   runs and its four 1.0f stores come out last, also descending, with the
//   constant materialised into the SAME register the zero used, after the last
//   zero.  Descending order out of ascending source is what a CHAINED
//   assignment does: `a = b = c = 0.0f` evaluates right to left, so the last
//   name written is stored first.  Two chained statements -- twelve
//   off-diagonal slots to 0.0f, then four diagonal slots to 1.0f, over a
//   sixteen-float block -- reproduce all 59 bytes with NO relocation site
//   anywhere in the body.
//
//   Rva003D54E0 writes [+0x2d] and [+0x2e] before [+0x2c]; Rva007049B0 writes
//   [+0x38..+0x40] in the middle of an otherwise ascending run; Rva0040AE50
//   writes [+0x20..+0x28] last.  Each of those is transcribed literally.
//
// Rva0040AE50 stores two ADDRESSES, at [+0] and [+0x30].  Both point into
// .rdata at a four-function block followed by a zero and an ASCII name, so they
// are descriptor-table addresses, and the two are DIFFERENT addresses and
// therefore two different objects.  They are NOT compiler-emitted vptrs: MSVC
// emits every vptr store before any body statement, and here a byte store to
// [+4] and six dword stores sit between them.  Both are DIR32 sites, so their
// four bytes are copied from retail and prove nothing beyond that; what the
// bytes do fix is that there are two of them and that they are not vptrs.
//
// IDENTITY IS NOT RECOVERED.  All five names are derived from addresses.  The
// bytes do not say what any field means; where a slot is only ever written zero
// its declared type is a guess constrained solely by its WIDTH -- byte stores
// are declared char, dword stores int, and the float spellings are used only
// where a non-zero float bit pattern (0x3F800000) forced the question.

// ---------------------------------------------------------------- 0x003D54E0

class Rva003D54E0
{
public:
	Rva003D54E0();
	int   m_00, m_04, m_08, m_0c;
	char  m_10, m_11;
	int   m_14, m_18, m_1c;
	char  m_20, m_21;
	int   m_24, m_28;
	char  m_2c, m_2d, m_2e;
	int   m_30;
};

Rva003D54E0::Rva003D54E0()
{
	m_00 = 0; m_04 = 0; m_08 = 0; m_0c = 0;
	m_10 = 0; m_11 = 0;
	m_14 = 0; m_18 = 0; m_1c = 0;
	m_20 = 0; m_21 = 0;
	m_24 = -1;
	m_28 = 0;
	m_2d = 0; m_2e = 0; m_2c = 0;
	m_30 = 0;
}

// ---------------------------------------------------------------- 0x0040AE50

extern const int GenDesc00CF05D8;
extern const int GenDesc00CF0540;

class Rva0040AE50
{
public:
	Rva0040AE50();
	const int *m_00;
	char m_04;
	int m_08, m_0c, m_10, m_14, m_18, m_1c;
	int m_20, m_24, m_28, m_2c;
	const int *m_30;
	int m_34, m_38, m_3c, m_40;
};

Rva0040AE50::Rva0040AE50()
{
	m_00 = &GenDesc00CF05D8;
	m_04 = 0;
	m_08 = 0; m_0c = 0; m_10 = 0; m_14 = 0; m_18 = 0; m_1c = 0;
	m_2c = 0;
	m_30 = &GenDesc00CF0540;
	m_34 = 0; m_38 = 0; m_3c = 0; m_40 = 0;
	m_20 = 0; m_24 = 0; m_28 = 0;
}

// ---------------------------------------------------------------- 0x006E18A0

class Rva006E18A0
{
public:
	float m_e[ 16 ];
};

void Rva006E18A0Init( Rva006E18A0 *m )
{
	m->m_e[  1 ] = m->m_e[  2 ] = m->m_e[  3 ] =
	m->m_e[  4 ] = m->m_e[  6 ] = m->m_e[  7 ] =
	m->m_e[  8 ] = m->m_e[  9 ] = m->m_e[ 11 ] =
	m->m_e[ 12 ] = m->m_e[ 13 ] = m->m_e[ 14 ] = 0.0f;
	m->m_e[  0 ] = m->m_e[  5 ] = m->m_e[ 10 ] = m->m_e[ 15 ] = 1.0f;
}

// ---------------------------------------------------------------- 0x007049B0

class Rva007049B0
{
public:
	Rva007049B0();
	int m_00, m_04, m_08, m_0c, m_10, m_14, m_18, m_1c;
	int m_20, m_24, m_28, m_2c, m_30, m_34, m_38, m_3c, m_40;
};

Rva007049B0::Rva007049B0()
{
	m_00 = 0; m_04 = 0; m_08 = 0; m_0c = 0; m_10 = 0; m_14 = 0;
	m_38 = 0; m_3c = 0; m_40 = 0;
	m_18 = 0; m_1c = 0; m_20 = 0; m_24 = 0; m_28 = 0; m_2c = 0; m_30 = 0; m_34 = 0;
}

// ---------------------------------------------------------------- 0x008D2B10

class Rva008D2B10
{
public:
	Rva008D2B10();
	float m_00, m_04, m_08, m_0c, m_10, m_14, m_18, m_1c;
	float m_20, m_24, m_28, m_2c, m_30, m_34;
	char  m_gap[ 0x3b8 - 0x38 ];
	float m_3b8, m_3bc;
};

Rva008D2B10::Rva008D2B10()
{
	m_00 = 1.0f; m_04 = 1.0f; m_08 = 1.0f; m_0c = 1.0f;
	m_10 = 0.0f; m_14 = 0.0f; m_18 = 0.0f; m_1c = 0.0f;
	m_20 = 1.0f; m_24 = 0.0f; m_28 = 0.0f; m_2c = 1.0f;
	m_30 = 0.0f; m_34 = 0.0f;
	m_3b8 = 0.0f; m_3bc = 0.0f;
}

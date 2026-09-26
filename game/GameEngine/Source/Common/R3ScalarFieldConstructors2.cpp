// Twenty-two more constructors of the shape proved in
// R3ScalarFieldConstructors.cpp: `mov eax,ecx` / a zero register / a run of
// immediate-to-member stores / `ret`.  Two mnemonic families land here (the
// seven-store group anchored at 0x000C33E0 and the eight-store group anchored
// at 0x00064390); they are one shape, split only by how many fields the body
// happens to assign.
//
// WHAT THE BYTES SHOW, beyond the first file:
//
//  * A SECOND CONSTANT REGISTER appears when one value is used by two stores
//    of different width or by two stores at all.  Rva00489210 loads `edx,1`
//    once and spends it as a dword at +4 and as `dl` at +9; Rva00064390 loads
//    `edx,0x3F000000` once and spends it at +0x10 and +0x14.  Nothing in the
//    source says "put this in a register" -- writing the same constant twice
//    is what produces it.
//
//  * A STORE THE BODY SKIPS is a field the constructor leaves alone, not a
//    field that does not exist.  Rva001F7810 and Rva00203440 never write +4;
//    Rva005CDED0 never writes +0xC or +0x10.  Those are declared and unwritten.
//
//  * WIDTH IS READ OFF THE STORE.  Rva006853A0 ends with `mov word ptr` -- a
//    16-bit field -- which no other member of either family has.
//
// IDENTITY IS NOT RECOVERED: class names are the constructor RVA, field names
// are the field offset, and each relocated immediate is spelled as the address
// of an extern named for that address.  build.py copies those four bytes from
// retail, so they are not evidence and say nothing about what lives there.
// Gen010E855C is also referenced from R3ScalarFieldConstructors.cpp: the same
// address, so the same extern, which is what verify_dir32_consistency wants.
//
// NOT DECIDED BY THE BYTES: whether 0x3F800000 is 1.0f or an integer, whether
// a zeroed dword is an int or a pointer, and where each object really ends.

extern int Gen01083E78;
extern int Gen01096518;
extern int Gen01096964;
extern int Gen010A31A0;
extern int Gen010C74D4;
extern int Gen010E855C;
extern int Gen010F95E8;
extern int Gen010A57B0;
extern int Gen010EBDD0;

// ------------------------------------------------ family anchored at 0x000C33E0

class Rva000C33E0
{
public:
	Rva000C33E0();
	int m_00, m_04, m_08;
	char m_0C;
	float m_10;
	char m_14;
	int m_18;
};
Rva000C33E0::Rva000C33E0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 1.0f;
	m_14 = 0;
	m_18 = 0;
}

class Rva000D1930
{
public:
	Rva000D1930();
	int *m_vtable;
	int m_04, m_08, m_0C, m_10, m_14, m_18;
};
Rva000D1930::Rva000D1930()
{
	m_vtable = &Gen01083E78;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}

// Same body as Rva002BBBB0 apart from the stored address.  Different address
// at the same site means a different type, so these stay two classes.
#define BFME_ADDR_THEN_OUT_OF_ORDER_ZEROS( NAME, GLOBAL )                 \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		int *m_vtable;                                                    \
		int m_04, m_08, m_0C, m_10, m_14, m_18;                           \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_vtable = &GLOBAL;                                               \
		m_04 = 0;                                                         \
		m_14 = 0;                                                         \
		m_18 = 0;                                                         \
		m_08 = 0;                                                         \
		m_0C = 0;                                                         \
		m_10 = 0;                                                         \
	}

BFME_ADDR_THEN_OUT_OF_ORDER_ZEROS( Rva0015EA80, Gen01096518 )
BFME_ADDR_THEN_OUT_OF_ORDER_ZEROS( Rva002BBBB0, Gen010C74D4 )

class Rva001611A0
{
public:
	Rva001611A0();
	int *m_vtable;
	int m_04, m_08, m_0C, m_10, m_14;
	char m_18, m_19;
};
Rva001611A0::Rva001611A0()
{
	m_vtable = &Gen01096964;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 1;
	m_19 = 0;
}

class Rva001C2E50
{
public:
	Rva001C2E50();
	int m_00, m_04, m_08, m_0C;
	char m_10;
	int m_14, m_18;
};
Rva001C2E50::Rva001C2E50()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}

// +4 is never stored.
class Rva001F7810
{
public:
	Rva001F7810();
	int *m_vtable;
	int m_04;
	int m_08, m_0C, m_10, m_14, m_18, m_1C;
};
Rva001F7810::Rva001F7810()
{
	m_vtable = &Gen010A31A0;
	m_08 = 0x258;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
}

class Rva00233C60
{
public:
	Rva00233C60();
	int m_00, m_04, m_08, m_0C;
	char m_10;
	int m_14, m_18;
};
Rva00233C60::Rva00233C60()
{
	m_00 = 0;
	m_10 = 1;
	m_14 = 0;
	m_18 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
}

class Rva00354B30
{
public:
	Rva00354B30();
	int m_00;
	int *m_vtable;
	int m_08, m_0C;
	char m_10, m_11, m_12;
};
Rva00354B30::Rva00354B30()
{
	m_00 = 0;
	m_08 = 0;
	m_0C = 0;
	m_vtable = &Gen010E855C;
	m_10 = 1;
	m_11 = 0;
	m_12 = 0;
}

// The literal 1 is written twice -- once as a dword, once as a byte -- which
// is what buys the `mov edx,1` ahead of the relocated store.
class Rva00489210
{
public:
	Rva00489210();
	int *m_vtable;
	int m_04;
	char m_08, m_09, m_0A;
	int m_0C;
};
Rva00489210::Rva00489210()
{
	m_vtable = &Gen010F95E8;
	m_04 = 1;
	m_08 = 0;
	m_09 = 1;
	m_0A = 0;
	m_0C = 0;
}

// +0xC and +0x10 are never stored.
#define BFME_ZERO_SKIP_TWO( NAME )                                        \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		int m_00, m_04, m_08;                                             \
		int m_0C, m_10;                                                   \
		int m_14, m_18, m_1C, m_20;                                       \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_00 = 0;                                                         \
		m_04 = 0;                                                         \
		m_08 = 0;                                                         \
		m_14 = 0;                                                         \
		m_18 = 0;                                                         \
		m_1C = 0;                                                         \
		m_20 = 0;                                                         \
	}

BFME_ZERO_SKIP_TWO( Rva005CDED0 )
BFME_ZERO_SKIP_TWO( Rva005CDF60 )

class Rva006853A0
{
public:
	Rva006853A0();
	int m_00, m_04, m_08, m_0C, m_10, m_14;
	short m_18;
};
Rva006853A0::Rva006853A0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}

// ------------------------------------------------ family anchored at 0x00064390

class Rva00064390
{
public:
	Rva00064390();
	int m_00, m_04, m_08, m_0C;
	float m_10, m_14;
	int m_18;
};
Rva00064390::Rva00064390()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0.5f;
	m_14 = 0.5f;
	m_18 = 0;
}

// +4 is never stored; +0x14 and +0x20 take the zero register while the four
// non-zero constants each get their own immediate store.
class Rva00203440
{
public:
	Rva00203440();
	int *m_vtable;
	int m_04;
	float m_08;
	int m_0C;
	float m_10, m_14;
	int m_18;
	float m_1C;
	int m_20;
};
Rva00203440::Rva00203440()
{
	m_vtable = &Gen010A57B0;
	m_18 = 0;
	m_08 = 200.0f;
	m_0C = 15;
	m_10 = 0.01f;
	m_1C = 0.02f;
	m_14 = 0.0f;
	m_20 = 0;
}

class Rva00396AD0
{
public:
	Rva00396AD0();
	char m_00;
	int m_04, m_08, m_0C, m_10, m_14, m_18, m_1C;
};
Rva00396AD0::Rva00396AD0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_1C = 0;
	m_18 = 0;
	m_14 = 0;
	m_10 = 0;
}

class Rva0039C3D0
{
public:
	Rva0039C3D0();
	int *m_vtable;
	int m_04;
	char m_08;
	int m_0C, m_10, m_14, m_18, m_1C;
};
Rva0039C3D0::Rva0039C3D0()
{
	m_04 = 0;
	m_08 = 0;
	m_vtable = &Gen010EBDD0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
}

class Rva00459D20
{
public:
	Rva00459D20();
	int m_00, m_04, m_08, m_0C, m_10;
	float m_14;
	int m_18;
	char m_1C;
};
Rva00459D20::Rva00459D20()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 1.0f;
	m_18 = 0;
	m_1C = 0;
}

// +0x10 and +0x14 are never stored.
#define BFME_ZERO_SKIP_TWO_WIDE( NAME )                                   \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		int m_00, m_04, m_08, m_0C;                                       \
		int m_10, m_14;                                                   \
		int m_18, m_1C, m_20, m_24;                                       \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_00 = 0;                                                         \
		m_04 = 0;                                                         \
		m_08 = 0;                                                         \
		m_0C = 0;                                                         \
		m_18 = 0;                                                         \
		m_1C = 0;                                                         \
		m_20 = 0;                                                         \
		m_24 = 0;                                                         \
	}

BFME_ZERO_SKIP_TWO_WIDE( Rva005CE7F0 )
BFME_ZERO_SKIP_TWO_WIDE( Rva005CE8F0 )

class Rva00651840
{
public:
	Rva00651840();
	int m_00, m_04, m_08, m_0C, m_10, m_14, m_18, m_1C;
};
Rva00651840::Rva00651840()
{
	m_10 = 0;
	m_00 = 0;
	m_14 = 0;
	m_04 = 0;
	m_18 = 0;
	m_08 = 0;
	m_1C = 0;
	m_0C = 0;
}

class Rva007BA110
{
public:
	Rva007BA110();
	int m_00, m_04, m_08, m_0C, m_10, m_14, m_18;
	char m_pad1C[0x44 - 0x1C];
	int m_44;
};
Rva007BA110::Rva007BA110()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_44 = 8;
}

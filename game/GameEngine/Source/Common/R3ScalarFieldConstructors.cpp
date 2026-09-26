// Seventeen tiny __thiscall constructors that set every field of a flat POD
// object from compile-time constants and then return.
//
//     mov eax,ecx / xor ecx,ecx / <stores> / ret
//
// WHAT THE BYTES SHOW.  The leading `mov eax,ecx` is not addressing
// convenience: a plain void member function that needs a zero register keeps
// `this` in ecx and zeroes eax (`xor eax,eax` / `mov [ecx+N],eax`), which is a
// different byte string.  Getting `this` COPIED INTO EAX and left there across
// the `ret` requires a function whose return value is `this` -- a constructor.
// That is the only thing the shape asserts about identity.
//
// The zero register is picked by width: dword zeros give `xor ecx,ecx`, an
// all-byte body gives `xor cl,cl` (Rva00421C30), and a body that also needs a
// non-zero constant in a register gets a second one -- none of that is spelled
// in source.
//
// STORE ORDER IS SOURCE ORDER.  MSVC does not schedule these stores, so the
// order of the offsets in the disassembly is the order of the assignments in
// the constructor body -- which is why several of these bodies write a later
// field before an earlier one.  Where the order is strictly ascending the
// bytes cannot distinguish a body of assignments from a member initialiser
// list; the assignment spelling is used throughout because it is the one that
// reproduces the non-ascending bodies too.
//
// FIELD WIDTH IS READ OFF THE STORE: `mov dword` / `mov word` / `mov byte`.
// Gaps between stored offsets are fields the constructor does not touch; they
// are declared as filler and no claim is made about their type.
//
// IDENTITY IS NOT RECOVERED.  Every class is named for the RVA of its
// constructor and every field for its offset.  A `mov dword ptr [eax], <imm>`
// whose immediate is a relocated address is spelled here as the address of an
// extern object named for that address; build.py fills a DIR32 site by copying
// the four retail bytes, so those four bytes are NOT evidence and the extern's
// identity -- data object, string, or vftable -- is NOT decided by this file.
// One extern per distinct address, so verify_dir32_consistency stays honest.
//
// WHAT THE BYTES DO NOT DECIDE: whether a stored 0x3F800000 is the float 1.0f
// or the integer 1065353216, whether a zeroed field is an int, a pointer or an
// enum, and whether the untouched fields exist at all.

extern int Gen01083D34;
extern int Gen01085DE8;
extern int Gen010E855C;
extern int Gen01116D68;
extern int Gen01136DDC;
extern int Gen01136DE8;
extern int Gen01136DF4;

// ---------------------------------------------------------------- singletons

class Rva000CBAF0
{
public:
	Rva000CBAF0();
	int *m_00;
	int m_04, m_08, m_0C, m_10, m_14;
};
Rva000CBAF0::Rva000CBAF0()
{
	m_00 = &Gen01083D34;
	m_04 = 100;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
}

class Rva000ED460
{
public:
	Rva000ED460();
	int *m_00;
	int m_04;
	char m_08;
	int m_0C, m_10, m_14;
};
Rva000ED460::Rva000ED460()
{
	m_00 = &Gen01085DE8;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
}

// Offset 0 is never stored: the body assigns six of the seven fields.
class Rva001976D0
{
public:
	Rva001976D0();
	int m_00;
	int m_04, m_08, m_0C, m_10, m_14, m_18;
};
Rva001976D0::Rva001976D0()
{
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}

class Rva001A31B0
{
public:
	Rva001A31B0();
	int m_00, m_04, m_08, m_0C;
	float m_10;
	int m_14;
};
Rva001A31B0::Rva001A31B0()
{
	m_0C = 0;
	m_10 = 10000000.0f;
	m_14 = 0;
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
}

class Rva001E11D0
{
public:
	Rva001E11D0();
	int m_00, m_04, m_08, m_0C, m_10;
	float m_14;
};
Rva001E11D0::Rva001E11D0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 3.402823466e+38F;
}

class Rva00324540
{
public:
	Rva00324540();
	int m_00, m_04, m_08, m_0C, m_10, m_14;
};
Rva00324540::Rva00324540()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0x7FFFFFFE;
}

class Rva00352900
{
public:
	Rva00352900();
	int *m_00;
	int m_04, m_08;
	char m_0C, m_0D, m_0E;
};
Rva00352900::Rva00352900()
{
	m_04 = 0;
	m_08 = 0;
	m_00 = &Gen010E855C;
	m_0C = 1;
	m_0D = 0;
	m_0E = 0;
}

class Rva00421C30
{
public:
	Rva00421C30();
	char m_00;
	char m_pad01[3];
	int m_04;
	float m_08;
	int m_0C;
	char m_pad10[0x20 - 0x10];
	char m_20, m_21;
};
Rva00421C30::Rva00421C30()
{
	m_00 = 0;
	m_04 = 0x11;
	m_08 = 1.0f;
	m_0C = 0x100;
	m_20 = 0;
	m_21 = 0;
}

class Rva00489BC0
{
public:
	Rva00489BC0();
	int m_00, m_04, m_08, m_0C, m_10, m_14;
};
Rva00489BC0::Rva00489BC0()
{
	m_00 = 0;
	m_04 = 0;
	m_14 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
}

class Rva00618630
{
public:
	Rva00618630();
	int *m_00;
	int m_04;
	char m_08;
	char m_pad09[3];
	int m_0C, m_10;
	float m_14;
};
Rva00618630::Rva00618630()
{
	m_04 = 0;
	m_08 = 0;
	m_00 = &Gen01116D68;
	m_0C = 4;
	m_10 = 0;
	m_14 = 1.0f;
}

// ------------------------------------------------------- repeated body shapes

// Five dword zeros at 0..0x10 then a byte zero at 0x14.  Two independent
// classes: byte-identical bodies with no relocation site, so the bytes cannot
// tell whether retail had one inline definition or two -- two is the reading
// that asserts nothing about a shared base.
#define BFME_ZERO5_BYTE1( NAME )                                          \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		int m_00, m_04, m_08, m_0C, m_10;                                 \
		char m_14;                                                        \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_00 = 0;                                                         \
		m_04 = 0;                                                         \
		m_08 = 0;                                                         \
		m_0C = 0;                                                         \
		m_10 = 0;                                                         \
		m_14 = 0;                                                         \
	}

BFME_ZERO5_BYTE1( Rva0022FF40 )
BFME_ZERO5_BYTE1( Rva00761CD0 )

// Zeros at 0, 4 and then 0x10..0x1C -- 8 and 0xC are skipped by the body.
#define BFME_ZERO_SPLIT( NAME )                                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		int m_00, m_04;                                                   \
		int m_08, m_0C;                                                   \
		int m_10, m_14, m_18, m_1C;                                       \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_00 = 0;                                                         \
		m_04 = 0;                                                         \
		m_10 = 0;                                                         \
		m_14 = 0;                                                         \
		m_18 = 0;                                                         \
		m_1C = 0;                                                         \
	}

BFME_ZERO_SPLIT( Rva005CD9F0 )
BFME_ZERO_SPLIT( Rva005CDA80 )

// -1 at 4, zeros, a byte zero at 0x14, and the relocated address stored LAST.
// A compiler-emitted vptr store is always the FIRST store in a constructor, so
// a relocated store this late is a source assignment, not a vptr.
#define BFME_MINUS1_THEN_ADDRESS( NAME, GLOBAL )                          \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		int *m_00;                                                        \
		int m_04, m_08, m_0C, m_10;                                       \
		char m_14;                                                        \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_04 = -1;                                                        \
		m_08 = 0;                                                         \
		m_0C = 0;                                                         \
		m_10 = 0;                                                         \
		m_14 = 0;                                                         \
		m_00 = &GLOBAL;                                                   \
	}

BFME_MINUS1_THEN_ADDRESS( Rva008BD2D0, Gen01136DDC )
BFME_MINUS1_THEN_ADDRESS( Rva008BD2F0, Gen01136DE8 )
BFME_MINUS1_THEN_ADDRESS( Rva008BD310, Gen01136DF4 )

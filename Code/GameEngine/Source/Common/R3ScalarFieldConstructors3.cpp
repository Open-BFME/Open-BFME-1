// Sixteen more bodies from the same shape as R3ScalarFieldConstructors.cpp --
// fifteen constant-field constructors plus one setter that writes through a
// global pointer.  Two mnemonic families land here: the ten-store group
// anchored at 0x0013A8B0 and the eleven-store group anchored at 0x00299DE0.
//
// THE TWO ODD BODIES, AND WHAT THEY COST.
//
// Rva0023E250 stores +0x14 and +0x18, then +0 and a byte at +0x1C, then
// stores +0x14 and +0x18 AGAIN.  Rva00299DE0 zeroes +0..+0x10 and then RELOADS
// +0xC into edx to store it at +0x18.  Written as plain members, MSVC deletes
// the first pair and forwards the zero -- the shorter body is what a plain
// spelling produces, and it is not what retail has.  Marking only the fields
// involved `volatile` keeps the accesses but HOISTS them out of source order,
// which is also wrong.  Declaring EVERY field of those two classes volatile is
// the one spelling found that reproduces the retail byte string exactly.
//
// That is a byte-level fact, not an identity claim: this file does NOT assert
// that retail wrote `volatile`.  What the bytes establish is only that in those
// two bodies the stores were neither eliminable nor reorderable.  A different
// cause -- a differently configured translation unit, an intervening construct
// this reconstruction has not found -- would be equally consistent.  Every
// other body here compiles from plain members.
//
// Rva006E1B30 is not a constructor.  It never touches `this` until the last
// instruction, reads a global pointer FOUR SEPARATE TIMES, and writes five
// fields of the pointee.  The reloads are the evidence: a store through the
// pointer may alias the pointer variable itself, so the compiler cannot keep it
// in a register across them.  ecx survives untouched to the final
// `mov [ecx+0xA8],3`, which makes this a __thiscall member returning void.
// `mov al,1` serves both byte stores, and eax is reloaded afterwards because
// that write destroyed the cached pointer.
//
// The FIRST TWO writes share one load and the last three do not, so they are
// not spelled the same way in source.  Five plain `g->field = ...` statements
// reload before every store (63 bytes).  Binding a reference to the pointee
// once and using it for the first two, then naming the global directly for the
// rest, is what produces retail's four loads in 56 bytes.  Which of the two
// halves the original author wrote "differently" is decided by the bytes; what
// the construct meant to them is not.
//
// IDENTITY IS NOT RECOVERED: names are addresses and offsets, relocated
// immediates are the addresses of externs named for those addresses, and
// build.py fills those four bytes from retail, so they carry no evidence.

extern int Gen01128BD0;
extern int Gen0111E188;
extern int Gen01128BAC;
extern int Gen012D6E2C;

// ------------------------------------------------ family anchored at 0x0013A8B0

class Rva0013A8B0
{
public:
	Rva0013A8B0();
	int m_00, m_04, m_08, m_0C, m_10;
	char m_pad14[8];
	int m_1C, m_20;
	char m_pad24[4];
	int m_28;
	char m_pad2C[0x3C - 0x2C];
	int m_3C;
	char m_pad40[4];
	int m_44;
};
Rva0013A8B0::Rva0013A8B0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_1C = 0;
	m_20 = 0;
	m_28 = 0;
	m_3C = 0;
	m_44 = 0;
}

// See the header note: every field volatile is what keeps the repeated
// +0x14 / +0x18 stores alive AND in source order.
class Rva0023E250
{
public:
	Rva0023E250();
	volatile int m_00, m_04, m_08, m_0C, m_10, m_14, m_18;
	volatile char m_1C;
};
Rva0023E250::Rva0023E250()
{
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_00 = 0;
	m_1C = 0;
	m_14 = 0;
	m_18 = 0;
}

class Rva003FD790
{
public:
	Rva003FD790();
	int m_00, m_04, m_08;
	char m_0C, m_0D;
	int m_10, m_14, m_18, m_1C, m_20;
};
Rva003FD790::Rva003FD790()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_0D = 0;
	m_10 = 0;
	m_20 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
}

#define BFME_ZERO_TEN_DWORDS( NAME )                                      \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		int m_00, m_04, m_08, m_0C, m_10;                                 \
		int m_14, m_18, m_1C, m_20, m_24;                                 \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_00 = 0;                                                         \
		m_04 = 0;                                                         \
		m_08 = 0;                                                         \
		m_0C = 0;                                                         \
		m_10 = 0;                                                         \
		m_14 = 0;                                                         \
		m_18 = 0;                                                         \
		m_1C = 0;                                                         \
		m_20 = 0;                                                         \
		m_24 = 0;                                                         \
	}

BFME_ZERO_TEN_DWORDS( Rva005CDCA0 )
BFME_ZERO_TEN_DWORDS( Rva005CE060 )

// The pointee of the global.  Only the five written fields are named.
class Gen012F8048Target
{
public:
	char m_pad00[0x38];
	float m_38;
	int m_3C, m_40;
	char m_pad44[0x69 - 0x44];
	char m_69, m_6A;
};
extern Gen012F8048Target *Gen012F8048;

class Rva006E1AE0
{
public:
	void invoke();
	char m_pad00[0xA8];
	int m_A8;
};
void Rva006E1AE0::invoke()
{
	Gen012F8048->m_38 = 0.0f;
	Gen012F8048Target &target = *Gen012F8048;
	target.m_40 = 0;
	target.m_3C = 0;
	Gen012F8048->m_69 = 1;
	Gen012F8048->m_6A = 0;
	m_A8 = 1;
}

class Rva006E1B30
{
public:
	void invoke();
	char m_pad00[0xA8];
	int m_A8;
};
void Rva006E1B30::invoke()
{
	Gen012F8048Target &target = *Gen012F8048;
	target.m_40 = 0;
	target.m_3C = 0;
	Gen012F8048->m_69 = 1;
	Gen012F8048->m_6A = 1;
	Gen012F8048->m_38 = 1.0f;
	m_A8 = 3;
}

class Rva0074AC80
{
public:
	Rva0074AC80();
	int m_00, m_04, m_08, m_0C, m_10;
	int m_14, m_18, m_1C, m_20, m_24;
};
Rva0074AC80::Rva0074AC80()
{
	m_00 = -1;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
}

class Rva007D8880
{
public:
	Rva007D8880();
	int *m_00;
	int m_04, m_08;
	char m_0C, m_0D, m_0E, m_0F;
	int m_10, m_14, m_18;
};
Rva007D8880::Rva007D8880()
{
	m_00 = &Gen01128BD0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_0D = 0;
	m_0E = 0;
	m_0F = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}

// ------------------------------------------------ family anchored at 0x00299DE0

// See the header note: every field volatile is what forces the RELOAD of
// +0xC for the store at +0x18 instead of forwarding the zero.
class Rva00299DE0
{
public:
	Rva00299DE0();
	volatile int m_00, m_04, m_08, m_0C, m_10;
	char m_pad14[4];
	volatile int m_18, m_1C, m_20, m_24, m_28;
};
Rva00299DE0::Rva00299DE0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_18 = m_0C;
	m_28 = 0;
	m_24 = 0;
	m_20 = 0;
	m_1C = 0;
}

class Rva0040B7F0
{
public:
	Rva0040B7F0();
	int m_00, m_04, m_08;
	char m_pad0C[8];
	int m_14;
	char m_pad18[0x54 - 0x18];
	int m_54, m_58, m_5C;
	char m_pad60[4];
	int m_64, m_68, m_6C;
	char m_pad70[0x88 - 0x70];
	int m_88;
};
Rva0040B7F0::Rva0040B7F0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_14 = 0;
	m_54 = 0;
	m_58 = 0;
	m_5C = 0;
	m_64 = 0;
	m_68 = 0;
	m_6C = 0;
	m_88 = 0;
}

class Rva0040C1F0
{
public:
	Rva0040C1F0();
	int m_00, m_04, m_08;
	char m_0C, m_0D;
	int m_10, m_14, m_18, m_1C, m_20, m_24;
};
Rva0040C1F0::Rva0040C1F0()
{
	m_00 = 4;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_0D = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
}

class Rva006DF550
{
public:
	Rva006DF550();
	int *m_00;
	int m_04, m_08;
	float m_0C;
	int m_10;
	float m_14;
	char m_18;
	char m_pad19[3];
	int m_1C, m_20, m_24, m_28;
};
Rva006DF550::Rva006DF550()
{
	m_00 = &Gen0111E188;
	m_04 = 0;
	m_08 = 0;
	m_0C = 37.5f;
	m_10 = 0;
	m_14 = 1.0f;
	m_18 = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_1C = 0;
}

class Rva00704980
{
public:
	Rva00704980();
	int m_00, m_04, m_08, m_0C, m_10, m_14, m_18;
	char m_1C, m_1D, m_1E, m_1F;
};
Rva00704980::Rva00704980()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_1D = 0;
	m_1E = 0;
	m_1F = 0;
}

class Rva00728220
{
public:
	Rva00728220();
	int m_00, m_04, m_08, m_0C, m_10, m_14, m_18, m_1C;
	char m_20, m_21;
	short m_22;
};
Rva00728220::Rva00728220()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_21 = 0;
	m_22 = 0;
}

class Rva007D85C0
{
public:
	Rva007D85C0();
	int *m_00;
	int m_04, m_08;
	char m_0C;
	int m_10, m_14, m_18, m_1C, m_20, m_24, m_28;
};
Rva007D85C0::Rva007D85C0()
{
	m_00 = &Gen01128BAC;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
}

// One dword is copied out of a global into +4; the repeated 0x3F800000 buys a
// second constant register.
class Rva00974F80
{
public:
	Rva00974F80();
	int m_00, m_04, m_08;
	float m_0C, m_10, m_14, m_18, m_1C;
	char m_20;
};
Rva00974F80::Rva00974F80()
{
	m_00 = 0;
	m_04 = Gen012D6E2C;
	m_08 = 0;
	m_0C = 1.0f;
	m_10 = 1.0f;
	m_14 = 1.0f;
	m_18 = 1.0f;
	m_1C = 1.0f;
	m_20 = 0;
}

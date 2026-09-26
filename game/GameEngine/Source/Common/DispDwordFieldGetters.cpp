// 86 seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / ret
//
// One dword is read at a fixed displacement from `this` and returned.  Every
// displacement in this family is a multiple of four, which is what lets the
// accessed member be spelled as an `int` sitting immediately after the lead
// array rather than needing explicit padding.  The bytes cannot distinguish
// `int` from `unsigned int`, a pointer, or anything else four bytes wide moved
// with a plain load.
//
// WHAT THE BYTES SHOW AND WHAT THEY DO NOT.  The displacement is a disp32 in
// every member -- MSVC 7.1 uses disp8 whenever the offset fits in a signed
// byte, so every offset here is at least 0x80, and the encoding itself is why
// this family is separable from the far larger disp8 one.  The operand size and
// the displacement are read straight off the instruction stream; nothing else
// about these functions is asserted.  Members before the accessed one are
// spelled as a lead array because their types are not witnessed here, only
// their total size.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_DISP_DWORD_GETTER( NAME, DISP )                                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		int get() const;                                                      \
                                                                              \
		char m_lead[ DISP ];                                                  \
		int  m_value;                                                         \
	};                                                                        \
	int NAME::get() const                                                     \
	{                                                                         \
		return m_value;                                                       \
	}

#define BFME_DISP_REAL_GETTER( NAME, DISP )                                  \
	class NAME                                                               \
	{                                                                        \
	public:                                                                  \
		float get() const;                                                   \
                                                                            \
		char  m_lead[ DISP ];                                               \
		float m_value;                                                       \
	};                                                                       \
	float NAME::get() const                                                   \
	{                                                                        \
		return m_value;                                                      \
	}

class Rva00412F40DwordField
{
public:
	int get() const;
	int m_value;
};

// ?get@Rva00412F40DwordField@@QBEHXZ
int Rva00412F40DwordField::get() const
{
	return m_value;
}

class Rva00427A90DwordField
{
public:
	int get() const;
	int m_value;
};

// ?get@Rva00427A90DwordField@@QBEHXZ
int Rva00427A90DwordField::get() const
{
	return m_value;
}

BFME_DISP_DWORD_GETTER( Rva000C7C20DwordField, 0x4B4 )
BFME_DISP_DWORD_GETTER( Rva000C88E0DwordField, 0x370 )
BFME_DISP_DWORD_GETTER( Rva00133C10DwordField, 0x38C )
BFME_DISP_DWORD_GETTER( Rva00148710DwordField, 0x3F8 )
BFME_DISP_DWORD_GETTER( Rva00150200DwordField, 0x43C )
BFME_DISP_DWORD_GETTER( Rva001B2B70DwordField, 0x4C4 )
BFME_DISP_DWORD_GETTER( Rva001B2B80DwordField, 0x4C8 )
BFME_DISP_DWORD_GETTER( Rva001B2B90DwordField, 0x4CC )
BFME_DISP_DWORD_GETTER( Rva001BD430DwordField, 0x3A0 )
BFME_DISP_DWORD_GETTER( Rva001BD440DwordField, 0x35C )
BFME_DISP_DWORD_GETTER( Rva001BDA50DwordField, 0x424 )
BFME_DISP_DWORD_GETTER( Rva001BDAA0DwordField, 0x428 )
BFME_DISP_DWORD_GETTER( Rva001BDAB0DwordField, 0x44C )
BFME_DISP_DWORD_GETTER( Rva001BDAC0DwordField, 0x450 )
BFME_DISP_DWORD_GETTER( Rva001BDAD0DwordField, 0x454 )
BFME_DISP_DWORD_GETTER( Rva001BDB00DwordField, 0x448 )
BFME_DISP_DWORD_GETTER( Rva001BDB80DwordField, 0x4A0 )
BFME_DISP_DWORD_GETTER( Rva001BDB90DwordField, 0x4A4 )
BFME_DISP_DWORD_GETTER( Rva001BDD30DwordField, 0x4AC )
BFME_DISP_DWORD_GETTER( Rva001E0D20DwordField, 0x4A8 )
BFME_DISP_DWORD_GETTER( Rva001E0D30DwordField, 0x4D0 )
BFME_DISP_DWORD_GETTER( Rva001E1730DwordField, 0x504 )
BFME_DISP_DWORD_GETTER( Rva001EABA0DwordField, 0x4D4 )
BFME_DISP_DWORD_GETTER( Rva00216AC0DwordField, 0x2BC )
BFME_DISP_DWORD_GETTER( Rva002307A0DwordField, 0xE8 )
BFME_DISP_DWORD_GETTER( Rva0025E7B0DwordField, 0x258 )
BFME_DISP_DWORD_GETTER( Rva00264AB0DwordField, 0x258 )
BFME_DISP_DWORD_GETTER( Rva002675E0DwordField, 0x3B8 )
BFME_DISP_DWORD_GETTER( Rva0026E7C0DwordField, 0x42C )
BFME_DISP_DWORD_GETTER( Rva002DB1A0DwordField, 0x4D8 )
BFME_DISP_DWORD_GETTER( Rva002E2750DwordField, 0x2B4 )
BFME_DISP_DWORD_GETTER( Rva00321F40DwordField, 0x18F0 )
BFME_DISP_DWORD_GETTER( Rva00321F60DwordField, 0x13C )
BFME_DISP_DWORD_GETTER( Rva00382740DwordField, 0x168 )
BFME_DISP_DWORD_GETTER( Rva003827A0DwordField, 0x138 )
BFME_DISP_DWORD_GETTER( Rva00382810DwordField, 0x2A0 )
BFME_DISP_DWORD_GETTER( Rva00382820DwordField, 0x2A4 )
BFME_DISP_DWORD_GETTER( Rva00382840DwordField, 0x2AC )
BFME_DISP_DWORD_GETTER( Rva003BC890DwordField, 0x8 )
BFME_DISP_DWORD_GETTER( Rva003BC840DwordField, 0x110 )
BFME_DISP_DWORD_GETTER( Rva003D5060DwordField, 0x318 )
BFME_DISP_DWORD_GETTER( Rva003D5A60DwordField, 0x444 )
BFME_DISP_DWORD_GETTER( Rva004107B0DwordField, 0x438 )
BFME_DISP_DWORD_GETTER( Rva004107D0DwordField, 0x458 )
// ?get@Rva00410740DwordField@@QBEHXZ
BFME_DISP_DWORD_GETTER( Rva00410740DwordField, 0x28 )
BFME_DISP_DWORD_GETTER( Rva00410800DwordField, 0x430 )
// ?get@Rva00410820DwordField@@QBEHXZ
BFME_DISP_DWORD_GETTER( Rva00410820DwordField, 0x0C )
BFME_DISP_DWORD_GETTER( Rva00410830DwordField, 0x7C8 )
BFME_DISP_DWORD_GETTER( Rva00410850DwordField, 0x7D0 )
BFME_DISP_DWORD_GETTER( Rva00410870DwordField, 0x24 )
// ?get@Rva00410880DwordField@@QBEHXZ
BFME_DISP_DWORD_GETTER( Rva00410880DwordField, 0x28 )
// ?get@Rva00410900DwordField@@QBEHXZ
BFME_DISP_DWORD_GETTER( Rva00410900DwordField, 0x38 )
// ?get@Rva00410910DwordField@@QBEHXZ
BFME_DISP_DWORD_GETTER( Rva00410910DwordField, 0x3C )
// Rva00412F40DwordField is defined above because MSVC rejects a zero-sized lead array.
// ?get@Rva00410430DwordField@@QBEHXZ
BFME_DISP_DWORD_GETTER( Rva00410430DwordField, 0x14 )
// ?get@Rva00422720DwordField@@QBEHXZ
BFME_DISP_DWORD_GETTER( Rva00422720DwordField, 0x04 )
// Rva00427A90DwordField is defined above because MSVC rejects a zero-sized lead array.
BFME_DISP_DWORD_GETTER( Rva0043B130DwordField, 0x534 )
BFME_DISP_DWORD_GETTER( Rva0043B140DwordField, 0x538 )
BFME_DISP_DWORD_GETTER( Rva0043B4E0DwordField, 0x564 )
BFME_DISP_DWORD_GETTER( Rva0044B340DwordField, 0x554 )
BFME_DISP_DWORD_GETTER( Rva0044B360DwordField, 0x55C )
BFME_DISP_DWORD_GETTER( Rva0044B370DwordField, 0x13A4 )
BFME_DISP_DWORD_GETTER( Rva0048CF00DwordField, 0x3024 )
BFME_DISP_DWORD_GETTER( Rva0048D170DwordField, 0x303C )
BFME_DISP_DWORD_GETTER( Rva0048D180DwordField, 0x3038 )
BFME_DISP_DWORD_GETTER( Rva0048D190DwordField, 0x3034 )
BFME_DISP_DWORD_GETTER( Rva0049AB60DwordField, 0x36C )
BFME_DISP_DWORD_GETTER( Rva004AEC70DwordField, 0x2EC )
BFME_DISP_DWORD_GETTER( Rva004B2230DwordField, 0x470 )
BFME_DISP_DWORD_GETTER( Rva004B2240DwordField, 0x474 )
BFME_DISP_DWORD_GETTER( Rva004C4FF0DwordField, 0x12A8 )
BFME_DISP_DWORD_GETTER( Rva005052D0DwordField, 0x294 )
BFME_DISP_DWORD_GETTER( Rva005374E0DwordField, 0x454 )
BFME_DISP_DWORD_GETTER( Rva005374F0DwordField, 0x458 )
BFME_DISP_DWORD_GETTER( Rva00537500DwordField, 0x44C )
BFME_DISP_DWORD_GETTER( Rva0055DB70DwordField, 0x1708 )
BFME_DISP_DWORD_GETTER( Rva005707D0DwordField, 0x4D0 )
BFME_DISP_DWORD_GETTER( Rva0059B7E0DwordField, 0x2BC )
BFME_DISP_DWORD_GETTER( Rva005BD2C0DwordField, 0x16E4 )
BFME_DISP_DWORD_GETTER( Rva005BD2D0DwordField, 0x16E8 )
BFME_DISP_DWORD_GETTER( Rva005D1DC0DwordField, 0x4 )
BFME_DISP_DWORD_GETTER( Rva00642A50DwordField, 0x138 )
BFME_DISP_DWORD_GETTER( Rva00642B80DwordField, 0x3C4 )
BFME_DISP_DWORD_GETTER( Rva00642B90DwordField, 0x320 )
BFME_DISP_DWORD_GETTER( Rva00642BF0DwordField, 0x3E0 )
BFME_DISP_DWORD_GETTER( Rva00662970DwordField, 0x34C )
BFME_DISP_DWORD_GETTER( Rva00694C70DwordField, 0x16CC )
BFME_DISP_DWORD_GETTER( Rva00695E70DwordField, 0x958 )
BFME_DISP_DWORD_GETTER( Rva00695F10DwordField, 0x618 )
BFME_DISP_DWORD_GETTER( Rva006C0830DwordField, 0x30B8 )
BFME_DISP_DWORD_GETTER( Rva006C0840DwordField, 0x30BC )
BFME_DISP_REAL_GETTER( Rva006C0850RealField, 0x10 )
// ?get@Rva00410920RealField@@QBEMXZ
BFME_DISP_REAL_GETTER( Rva00410920RealField, 0x48 )
BFME_DISP_DWORD_GETTER( Rva006E7AF0DwordField, 0x30C4 )
BFME_DISP_DWORD_GETTER( Rva0073A660DwordField, 0x858 )
BFME_DISP_DWORD_GETTER( Rva0073A760DwordField, 0x868 )
BFME_DISP_DWORD_GETTER( Rva00746000DwordField, 0x23C4 )
BFME_DISP_DWORD_GETTER( Rva00746040DwordField, 0x110 )
BFME_DISP_DWORD_GETTER( Rva00751AD0DwordField, 0x2F0 )
BFME_DISP_DWORD_GETTER( Rva007B8160DwordField, 0x2094 )
BFME_DISP_DWORD_GETTER( Rva007F6250DwordField, 0x2D8 )
BFME_DISP_DWORD_GETTER( Rva0014FD80DwordField, 0x31C )

// Ten further members whose displacement is outside the 0x80..0x8000 window the
// block above covers.  The largest, 0x2A7CB0, is far too big to be an ordinary
// member offset; the bytes say only that a dword is read at that displacement
// from ecx, and the lead array spells exactly that and nothing more.

BFME_DISP_DWORD_GETTER( Rva00090420DwordField, 0x17620 )
BFME_DISP_DWORD_GETTER( Rva002ED520DwordField, 0x170D8 )
BFME_DISP_DWORD_GETTER( Rva00322020DwordField, 0x170DC )
BFME_DISP_DWORD_GETTER( Rva00410810DwordField, 0x170B4 )
BFME_DISP_DWORD_GETTER( Rva006629F0DwordField, 0x1205C )
BFME_DISP_DWORD_GETTER( Rva006C5680DwordField, 0x2A7CB0 )
BFME_DISP_DWORD_GETTER( Rva006C56F0DwordField, 0x120E0 )
BFME_DISP_DWORD_GETTER( Rva006C5700DwordField, 0x120E4 )
BFME_DISP_DWORD_GETTER( Rva006C5710DwordField, 0x120E8 )
BFME_DISP_DWORD_GETTER( Rva006C5720DwordField, 0x120EC )

// Five address-qualified field initialisers preserve retail's store order.
// Rva0040AE50 stores BuffEntry and BuffEntryTail vftables at +0 and +0x30.
// The remaining class and field meanings are unproved.

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

extern "C" const int __identifier("??_7BuffEntry@@6B@");
extern "C" const int __identifier("??_7BuffEntryTail@@6B@");
#define GenDesc00CF05D8 __identifier("??_7BuffEntry@@6B@")
#define GenDesc00CF0540 __identifier("??_7BuffEntryTail@@6B@")

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

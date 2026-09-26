// Constructor at 0x00421D30: sets a block of float defaults and three
// three-float vectors to one half. Owner identity is unproven (no caller,
// vtable, string or layout witness), so the class keeps its address token.
// The trailing 0x4C/0x50/0x54 stores follow the vector copies in source,
// which keeps 1.0f live across the copies and gives retail's EBX/ESI/EDI.

class Rva00421D30Vec
{
public:
	float m_00;
	float m_04;
	float m_08;
};

class Rva00421D30
{
public:
	Rva00421D30();

	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
	float m_20;
	float m_24;
	Rva00421D30Vec m_28;
	Rva00421D30Vec m_34;
	Rva00421D30Vec m_40;
	float m_4C;
	float m_50;
	float m_54;
};

Rva00421D30::Rva00421D30()
{
	m_00 = 4.0f;
	m_04 = 0.7f;
	m_08 = 1.0f;
	m_0C = 1.0f;
	m_10 = 1.0f;
	m_14 = 1.0f;
	m_18 = 1.0f;
	m_1C = 1.0f;
	m_24 = 1.0f;
	m_20 = 1.0f;
	m_34.m_00 = 0.5f;
	m_34.m_04 = 0.5f;
	m_34.m_08 = 0.5f;
	m_40 = m_34;
	m_28 = m_34;
	m_4C = 1.0f;
	m_50 = 1.0f;
	m_54 = 5.0f;
}

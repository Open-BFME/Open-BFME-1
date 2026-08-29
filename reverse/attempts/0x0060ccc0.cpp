// ?d_0060ccc0@@YAXXZ
// partial score=0.97 date=2026-08-29
// ---------------------------------------------------------------------------
// 0x0060CCC0 -- constructor with three repeated float constants.
//
// 0x44f14000 is 1930.0f, 0x43520000 is 210.0f and 0x42480000 is 50.0f.  The
// 210.0 is materialised into a register because it is stored three times,
// which is also why the store at +0x28 is emitted after the one at +0x2c: the
// register is set up between them.

class Rva0060CCC0
{
public:
	Rva0060CCC0();

	virtual void slot00();

	int m_at04;
	int m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
	int m_at1c;
	int m_at20;
	float m_at24;
	float m_at28;
	float m_at2c;
	int m_at30;
	int m_at34;
	int m_at38;
	int m_at3c;
	int m_at40;
	int m_at44;
	int m_at48;
	int m_at4c;
	int m_at50;
	float m_at54;
	float m_at58;
	float m_at5c;
	float m_at60;
	int m_at64;
	int m_at68;
	int m_at6c;
	int m_at70;
};

// @??0Rva0060CCC0@@QAE@XZ 0x0060CCC0
Rva0060CCC0::Rva0060CCC0()
{
	m_at04 = 0;
	m_at08 = 0;
	m_at0c = 0;
	m_at10 = 0;
	m_at14 = 0;
	m_at18 = 0;
	m_at1c = 0;
	m_at20 = 0;
	m_at24 = 1930.0f;
	m_at2c = 50.0f;
	m_at28 = 210.0f;
	m_at30 = 0;
	m_at34 = 0;
	m_at38 = 0;
	m_at3c = 0;
	m_at40 = 0;
	m_at44 = 0;
	m_at48 = 1;
	m_at4c = 0;
	m_at50 = 0;
	m_at54 = 1930.0f;
	m_at58 = 210.0f;
	m_at5c = 1930.0f;
	m_at60 = 210.0f;
	m_at64 = 0;
	m_at68 = 0;
	m_at6c = 0;
	m_at70 = 0;
}

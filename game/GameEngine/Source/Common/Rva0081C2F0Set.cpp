// cl: /O2 /Ob0

// Retail vftable 0x00D2162C: ??_7BfmeBaseCC@@6B@, the base vftable the base
// destructor at 0x0073A4E0 restores (targets/game/reverse/symbols.csv).
// The declaration carries no C++ name: __identifier spells the retail symbol
// exactly, so the store below references the defining name.
extern "C" const char __identifier("??_7BfmeBaseCC@@6B@")[];

class Rva0081C2F0
{
	void *m_vt;
	int m_04, m_08, m_0C, m_10, m_14, m_18, m_1C;
	float m_20;
	int m_24;
	char m_28;

public:
	Rva0081C2F0 &set(int n);
};

Rva0081C2F0 &Rva0081C2F0::set(int n)
{
	m_20 = 1.0f;
	m_vt = (void *)__identifier("??_7BfmeBaseCC@@6B@");
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_24 = n;
	m_28 = 0;
	if (n >= 6 || n < 0)
		m_24 = 0;
	return *this;
}

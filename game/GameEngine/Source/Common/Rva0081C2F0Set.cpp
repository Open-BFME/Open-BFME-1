// cl: /O2 /Ob0

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
	m_vt = (void *)0x0112162C;
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

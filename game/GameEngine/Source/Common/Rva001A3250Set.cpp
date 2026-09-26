// cl: /O2 /Ob0

class Rva001A3250
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;

public:
	Rva001A3250 &set(int a);
};

Rva001A3250 &Rva001A3250::set(int a)
{
	m_0C = 0;
	m_10 = 0x4B189680;
	m_14 = 0;
	m_18 = a;
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	return *this;
}

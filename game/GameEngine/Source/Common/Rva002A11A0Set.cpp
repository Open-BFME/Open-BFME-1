// cl: /O2 /Ob0

class Rva002A11A0
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_10;

public:
	Rva002A11A0 &set(int a);
};

Rva002A11A0 &Rva002A11A0::set(int a)
{
	m_00 = a;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0x3F800000;
	m_10 = 0;
	return *this;
}

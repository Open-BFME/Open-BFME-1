// cl: /O2 /Ob0

class Rva00588730
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	char m_14;
	char m_15;

public:
	Rva00588730 &set(int a);
};

Rva00588730 &Rva00588730::set(int a)
{
	m_00 = a;
	m_04 = 0;
	m_08 = -1;
	m_0C = -1;
	m_10 = -1;
	m_14 = 0;
	m_15 = 0;
	return *this;
}

// cl: /O2 /Ob0

class Rva00588F50
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;

public:
	Rva00588F50 &set(int a, int b);
};

Rva00588F50 &Rva00588F50::set(int a, int b)
{
	m_00 = 0x96;
	m_04 = a;
	m_08 = b;
	m_0C = 0;
	return *this;
}

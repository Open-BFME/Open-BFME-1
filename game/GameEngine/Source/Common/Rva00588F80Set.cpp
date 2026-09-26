// cl: /O2 /Ob0

class Rva00588F80
{
	int m_00;
	int m_04;
	int m_08;

public:
	Rva00588F80 &set(int a);
};

Rva00588F80 &Rva00588F80::set(int a)
{
	m_00 = 0xB4;
	m_04 = 0x38;
	m_08 = a;
	return *this;
}

// cl: /O2 /Ob0

class Rva003D4DB0
{
	int m_00;
	char m_04;
	char m_05;
	int m_08;

public:
	Rva003D4DB0 &set(int a);
};

Rva003D4DB0 &Rva003D4DB0::set(int a)
{
	m_00 = a;
	m_04 = 0;
	m_05 = 0;
	m_08 = -1;
	return *this;
}

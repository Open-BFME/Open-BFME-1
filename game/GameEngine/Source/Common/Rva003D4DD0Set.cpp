// cl: /O2 /Ob0

class Rva003D4DD0
{
	int m_00;
	char m_04;
	char m_05;
	int m_08;

public:
	Rva003D4DD0 &set(int a, char b, int c, char d);
};

Rva003D4DD0 &Rva003D4DD0::set(int a, char b, int c, char d)
{
	m_00 = a;
	m_04 = b;
	m_05 = d;
	m_08 = c;
	return *this;
}

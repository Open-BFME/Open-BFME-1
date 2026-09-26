// cl: /O2 /Ob0

class Rva00201EE0
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_10;

public:
	Rva00201EE0 &set(int a, int b, char c);
};

Rva00201EE0 &Rva00201EE0::set(int a, int b, char c)
{
	m_08 = a;
	m_04 = 0;
	m_00 = (void *)0x010A5158;
	m_0C = b;
	m_10 = c;
	return *this;
}

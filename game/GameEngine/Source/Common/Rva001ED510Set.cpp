// cl: /O2 /Ob0

class Rva001ED510
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_10;
	int m_14;

public:
	Rva001ED510 &set(int a, int b, char c, int d);
};

Rva001ED510 &Rva001ED510::set(int a, int b, char c, int d)
{
	m_08 = a;
	m_0C = b;
	m_04 = 0;
	m_00 = (void *)0x010A1A5C;
	m_10 = c;
	m_14 = d;
	return *this;
}

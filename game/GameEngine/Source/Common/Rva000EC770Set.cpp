// cl: /O2 /Ob0

class Rva000EC770
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_10;

public:
	Rva000EC770 &set(int a, int b, char c);
};

Rva000EC770 &Rva000EC770::set(int a, int b, char c)
{
	m_08 = a;
	m_04 = 0;
	m_00 = (void *)0x01085DC0;
	m_0C = b;
	m_10 = c;
	return *this;
}

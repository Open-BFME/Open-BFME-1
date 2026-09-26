// cl: /O2 /Ob0

class Rva00149E60
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;

public:
	Rva00149E60 &set(int a, int b, int c);
};

Rva00149E60 &Rva00149E60::set(int a, int b, int c)
{
	m_08 = b;
	m_04 = 0;
	m_00 = (void *)0x010956C4;
	m_0C = c;
	m_10 = a;
	return *this;
}

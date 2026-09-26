// cl: /O2 /Ob0

class Rva00160CE0
{
	void *m_00;
	int m_04;
	int m_08;
	char m_0C;
	int m_10;

public:
	Rva00160CE0 &set(int a, int b, char c);
};

Rva00160CE0 &Rva00160CE0::set(int a, int b, char c)
{
	m_08 = a;
	m_04 = 0;
	m_00 = (void *)0x0109689C;
	m_0C = c;
	m_10 = b;
	return *this;
}

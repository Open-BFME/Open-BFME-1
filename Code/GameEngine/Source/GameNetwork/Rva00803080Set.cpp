// cl: /O2 /Ob0

class Rva00803080
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;

public:
	Rva00803080 &set(int a);
};

Rva00803080 &Rva00803080::set(int a)
{
	m_04 = a;
	m_00 = (void *)0x0112C6F4;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	return *this;
}

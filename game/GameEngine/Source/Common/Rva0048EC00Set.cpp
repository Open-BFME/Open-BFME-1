// cl: /O2 /Ob0

class Rva0048EC00
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;

public:
	Rva0048EC00 &set(int a, int b, int c, int d);
};

Rva0048EC00 &Rva0048EC00::set(int a, int b, int c, int d)
{
	m_00 = a;
	m_04 = b;
	m_08 = c;
	m_0C = d;
	m_10 = 0;
	m_14 = 0;
	return *this;
}

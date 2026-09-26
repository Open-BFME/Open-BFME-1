// cl: /O2 /Ob0

class Rva00570400
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;

public:
	Rva00570400 &set(int a, int b);
};

Rva00570400 &Rva00570400::set(int a, int b)
{
	m_00 = a;
	m_04 = b;
	m_08 = 0;
	m_0C = 0;
	return *this;
}

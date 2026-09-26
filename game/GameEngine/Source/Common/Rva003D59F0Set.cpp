// cl: /O2 /Ob0

struct Rva003D59F0Pair { int a, b; };

class Rva003D59F0
{
	int m_00, m_04;
	char pad[8];
	int m_10, m_14, m_18, m_1C, m_20, m_24;

public:
	Rva003D59F0 &set(int a, int b, int c, int d, const Rva003D59F0Pair *p, int f, int g, int h);
};

Rva003D59F0 &Rva003D59F0::set(int a, int b, int c, int d, const Rva003D59F0Pair *p, int f, int g, int)
{
	m_00 = a;
	m_04 = b;
	m_10 = c;
	m_14 = d;
	m_18 = p->a;
	m_1C = p->b;
	m_20 = f;
	m_24 = g;
	return *this;
}

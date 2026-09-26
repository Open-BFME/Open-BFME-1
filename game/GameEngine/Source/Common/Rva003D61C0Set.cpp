// cl: /O2 /Ob0

struct Rva003D61C0Vec
{
	int a;
	int b;
	int c;
};

class Rva003D61C0
{
	int m_00;
	int m_04;
	Rva003D61C0Vec m_08;

public:
	Rva003D61C0 &set(int a, int b, const Rva003D61C0Vec *p);
};

Rva003D61C0 &Rva003D61C0::set(int a, int b, const Rva003D61C0Vec *p)
{
	m_00 = a;
	m_04 = b;
	m_08.a = p->a;
	m_08.b = p->b;
	m_08.c = p->c;
	return *this;
}

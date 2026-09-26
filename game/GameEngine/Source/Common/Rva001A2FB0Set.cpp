// cl: /O2 /Ob0

struct Rva001A2FB0Triple { int a, b, c; };

class Rva001A2FB0
{
	int m_00, m_04, m_08, m_0C, m_10, m_14;
	char m_18;
	char pad[0xF];
	int m_28;
	char m_2C, m_2D;
	short m_2E;

public:
	Rva001A2FB0 &set(const Rva001A2FB0Triple *p, int a, int b, int c, short s, int e, char f, char g);
};

Rva001A2FB0 &Rva001A2FB0::set(const Rva001A2FB0Triple *p, int a, int b, int c, short s, int e, char f, char g)
{
	m_00 = p->a;
	m_04 = p->b;
	m_08 = p->c;
	m_0C = a;
	m_10 = b;
	m_14 = c;
	m_28 = e;
	m_2C = f;
	m_18 = 0;
	m_2D = g;
	m_2E = s;
	return *this;
}

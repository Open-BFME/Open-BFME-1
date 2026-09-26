// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00537870Range
{
	unsigned m_0;
	unsigned m_4;
	unsigned m_8;
};

class Rva00537870
{
	unsigned char m_pad[4];
	Rva00537870Range *m_4;

public:
	void apply(unsigned a, unsigned b, unsigned c);
};

void Rva00537870::apply(unsigned a, unsigned b, unsigned c)
{
	Rva00537870Range *p = m_4;
	p->m_8 = a;
	p->m_0 = b;
	p->m_4 = c - b;
}

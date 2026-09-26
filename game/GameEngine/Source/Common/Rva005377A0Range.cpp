// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva005377A0Range
{
	unsigned m_0;
	unsigned m_4;
	unsigned m_8;
};

void rva005377A0(Rva005377A0Range *p, unsigned a, unsigned b, unsigned c)
{
	p->m_8 = a;
	p->m_0 = b;
	p->m_4 = c - b;
}

// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva005378E0Range
{
	unsigned m_0;
	unsigned m_4;
	unsigned m_8;
};

class Rva005378E0
{
	unsigned char m_pad[8];
	Rva005378E0Range *m_8;

public:
	void apply(unsigned a, unsigned b);
};

void Rva005378E0::apply(unsigned a, unsigned b)
{
	Rva005378E0Range *p = m_8;
	p->m_8 = a;
	p->m_0 = a;
	p->m_4 = b - a;
}

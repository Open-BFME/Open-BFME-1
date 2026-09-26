// cl: /O2 /Ob0

class Rva00477E60
{
	char pad[0x1F8];
	Rva00477E60 *m_1F8;
	char pad2[4];
	Rva00477E60 *m_200;
	Rva00477E60 *m_204;

public:
	Rva00477E60 *walk();
};

Rva00477E60 *Rva00477E60::walk()
{
	Rva00477E60 *p = this;
	while (p->m_200)
		p = p->m_200;
	while (p->m_204)
	{
		p = p->m_204;
		while (p->m_1F8)
			p = p->m_1F8;
	}
	return p;
}

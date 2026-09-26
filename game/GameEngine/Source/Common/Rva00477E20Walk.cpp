// cl: /O2 /Ob0

class Rva00477E20
{
	char pad[0x200];
	Rva00477E20 *m_200;
	Rva00477E20 *m_204;

public:
	Rva00477E20 *walk();
};

Rva00477E20 *Rva00477E20::walk()
{
	Rva00477E20 *p = this;
	while (p->m_200)
		p = p->m_200;
	while (p->m_204)
		p = p->m_204;
	return p;
}

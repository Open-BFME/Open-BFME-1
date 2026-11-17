// cl: /O2 /Ob0

class Rva00477E60
{
	char pad[0x1F8];
	Rva00477E60 *m_next;
	char pad2[4];
	Rva00477E60 *m_parent;
	Rva00477E60 *m_child;

public:
	Rva00477E60 *walk();
};

Rva00477E60 *Rva00477E60::walk()
{
	Rva00477E60 *p = this;
	while (p->m_parent)
		p = p->m_parent;
	while (p->m_child)
	{
		p = p->m_child;
		while (p->m_next)
			p = p->m_next;
	}
	return p;
}

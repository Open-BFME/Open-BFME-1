// cl: /O2 /Ob0

struct Rva00160830Node
{
	char pad[4];
	Rva00160830Node *m_04;
	Rva00160830Node *m_08;
};

class Rva00160830
{
	char pad[4];
	Rva00160830Node *m_04;

public:
	void flip();
};

void Rva00160830::flip()
{
	Rva00160830Node *p = m_04;
	Rva00160830Node *last = 0;
	if (p)
	{
		do
		{
			Rva00160830Node *a = p->m_04;
			Rva00160830Node *b = p->m_08;
			p->m_08 = a;
			p->m_04 = b;
			last = p;
			p = b;
		} while (p);
	}
	m_04 = last;
}

// cl: /O2 /Ob0

struct Rva001DB130Node
{
	char pad[0x0C];
	int m_0C;
	Rva001DB130Node *m_10;
};

class Rva001DB130
{
	Rva001DB130Node *m_00;
	Rva001DB130Node *m_04;

public:
	Rva001DB130Node *find(int v);
};

Rva001DB130Node *Rva001DB130::find(int v)
{
	Rva001DB130Node *p = m_04;
	m_00 = p;
	if (!p)
		return 0;
	do
	{
		if (p->m_0C == v)
			return p;
		p = p->m_10;
	} while (p);
	return 0;
}

// cl: /O2 /Ob0

struct Rva0029C060Node
{
	char pad[0x30];
	int m_30;
	char pad2[8];
	Rva0029C060Node *m_3C;
};

class Rva0029C060
{
	char pad[8];
	Rva0029C060Node *m_08;

public:
	int count(int v);
};

int Rva0029C060::count(int v)
{
	int n = 0;
	for (Rva0029C060Node *p = m_08; p; p = p->m_3C)
	{
		if (v == p->m_30)
			n++;
	}
	return n;
}

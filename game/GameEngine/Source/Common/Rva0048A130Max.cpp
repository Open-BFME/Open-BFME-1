// cl: /O2 /Ob0

struct Rva0048A130Extra
{
	char pad[4];
	int m_04;
};

struct Rva0048A130Item
{
	char pad[4];
	int m_04;
	char pad2[8];
	Rva0048A130Extra *ex;
};

struct Rva0048A130Node
{
	Rva0048A130Node *next;
	char pad[4];
	Rva0048A130Item *item;
};

class Rva0048A130
{
	char pad[4];
	Rva0048A130Node *m_04;

public:
	int maxv();
};

int Rva0048A130::maxv()
{
	Rva0048A130Node *head = m_04;
	Rva0048A130Node *n = head->next;
	int best = 0;
	while (n != head)
	{
		Rva0048A130Item *it = n->item;
		int v;
		if (it->ex)
			v = it->ex->m_04 + it->m_04;
		else
			v = it->m_04;
		if (v > best)
			best = v;
		n = n->next;
	}
	return best;
}

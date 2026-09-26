// cl: /O2 /Ob0

struct Rva00685200Node
{
	char pad[0x398];
	Rva00685200Node *m_398;
};

class Rva00685200
{
	char pad[0x0C];
	Rva00685200Node *m_0C;

public:
	bool has(Rva00685200Node *p);
};

bool Rva00685200::has(Rva00685200Node *p)
{
	if (!p)
		return false;
	for (Rva00685200Node *q = m_0C; q; q = q->m_398)
	{
		if (q == p)
			return true;
	}
	return false;
}

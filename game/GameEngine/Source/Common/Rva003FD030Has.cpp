// cl: /O2 /Ob0

struct Rva003FD030Node
{
	Rva003FD030Node *next;
	char pad[0x1C];
	int m_20;
};

class Rva003FD030
{
	char pad[4];
	Rva003FD030Node *m_04;

public:
	bool has();
};

bool Rva003FD030::has()
{
	for (Rva003FD030Node *p = m_04; p; p = p->next)
	{
		if (p->m_20 != 0x7FFFFFFF)
			return true;
	}
	return false;
}

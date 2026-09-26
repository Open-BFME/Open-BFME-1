// cl: /O2 /Ob0

class Node0010AB00
{
public:
	char pad[0x108];
	Node0010AB00 *m_108;
	Node0010AB00 *m_10C;
};

class Rva0010AB00
{
	char pad[8];
	Node0010AB00 *m_08;

public:
	void insert(Node0010AB00 *n);
};

void Rva0010AB00::insert(Node0010AB00 *n)
{
	if (!n)
		return;
	n->m_10C = 0;
	n->m_108 = m_08;
	if (m_08)
		m_08->m_10C = n;
	m_08 = n;
}

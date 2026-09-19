// ?forEachInState@Rva0042E660Owner@@QAEXP6AXPAURva0042E660Node@@PAX@Z1@Z
struct Rva0042E660Node
{
	char m_pad[0x104];
	Rva0042E660Node *m_next;
	char m_pad2[0x2e8 - 0x108];
	int m_state;
};

struct Rva0042E660Owner
{
	char m_pad[0x10];
	Rva0042E660Node *m_head;
	void forEachInState(void (__cdecl *fn)(Rva0042E660Node *, void *), void *arg);
};

void Rva0042E660Owner::forEachInState(void (__cdecl *fn)(Rva0042E660Node *, void *), void *arg)
{
	Rva0042E660Node *n = m_head;
	while (n)
	{
		int state = n->m_state;
		Rva0042E660Node *next = n->m_next;
		if (state < 1 || state > 4)
			fn(n, arg);
		n = next;
	}
}

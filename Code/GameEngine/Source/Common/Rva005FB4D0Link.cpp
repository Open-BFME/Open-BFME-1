// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x005FB4D0. Pushes a node onto the head of the list the host at
// this+4 keeps at +0x9C, and fixes the back link or the tail. No caller,
// vtable slot or table names the owner, so the classes are address-derived.

class Rva005FB4D0Node;

class Rva005FB4D0Host
{
public:
	unsigned char m_bfmePad000[0x98];
	Rva005FB4D0Node *m_tail;
	Rva005FB4D0Node *m_head;
};

class Rva005FB4D0Node
{
public:
	Rva005FB4D0Host *m_host;
	Rva005FB4D0Node *m_next;
	Rva005FB4D0Node *m_prev;
};

class Rva005FB4D0Owner
{
public:
	void link(Rva005FB4D0Node *node);

	int m_bfmePad000;
	Rva005FB4D0Host *m_host;
};

void Rva005FB4D0Owner::link(Rva005FB4D0Node *node)
{
	volatile int guard = 0;
	Rva005FB4D0Host *host = m_host;

	node->m_host = host;

	if (host != 0)
	{
		node->m_next = host->m_head;
		node->m_prev = 0;
		host->m_head = node;

		if (node->m_next != 0)
			node->m_next->m_prev = node;
		else
			node->m_host->m_tail = node;

		return;
	}

	node->m_prev = 0;
	node->m_next = 0;
}

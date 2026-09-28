// Open-BFME5: convert the retail duplicate-safe linked-list insertion at 0x0018EDB0.

struct Rva0018EDB0Node
{
	void *m_owner;
	Rva0018EDB0Node *m_next;
};

struct Rva0018EDB0Table
{
	Rva0018EDB0Node *m_head;
};

extern Rva0018EDB0Table *g_rva0018EDB0Table;
extern unsigned int g_rva0018EDB0Flags;

void rva0018EDB0Insert(Rva0018EDB0Node *node)
{
	Rva0018EDB0Node *current = g_rva0018EDB0Table->m_head;
	while (current != 0)
	{
		if (current == node)
			return;
		current = current->m_next;
	}
	node->m_next = g_rva0018EDB0Table->m_head;
	g_rva0018EDB0Table->m_head = node;
	g_rva0018EDB0Flags |= 1;
}

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

extern int *g_rva0018EC80;		// retail 0x012ACB50, defined in Rva0018EC80Get.cpp
extern unsigned int g_rva0018EDB0Flags;

void rva0018EDB0Insert(Rva0018EDB0Node *node)
{
	Rva0018EDB0Node *current = ((Rva0018EDB0Table*)g_rva0018EC80)->m_head;
	while (current != 0)
	{
		if (current == node)
			return;
		current = current->m_next;
	}
	node->m_next = ((Rva0018EDB0Table*)g_rva0018EC80)->m_head;
	((Rva0018EDB0Table*)g_rva0018EC80)->m_head = node;
	g_rva0018EDB0Flags |= 1;
}

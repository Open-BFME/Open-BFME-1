// Retail 0x0034F9D0, 25 bytes.  Insert a node after the requested position
// or at the head of the singly linked list when the position is null.

struct Rva0034F9D0Node
{
	Rva0034F9D0Node *m_next;
};

struct Rva0034F9D0Head
{
	Rva0034F9D0Node *m_first;
};

void __stdcall rva0034f9d0Insert(
	Rva0034F9D0Head *head,
	Rva0034F9D0Node *node,
	Rva0034F9D0Node *after)
{
	if (after != 0)
	{
		node->m_next = after->m_next;
		after->m_next = node;
	}
	else
	{
		node->m_next = head->m_first;
		head->m_first = node;
	}
}

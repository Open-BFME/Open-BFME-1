// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: walk a singly-linked list at [this], freeing each node through
// a cdecl deallocator. next lives at +4.

extern void (__cdecl *g_bfmeFreeDWF)(void *ptr);

class Rva00893960List
{
	struct Node
	{
		void *pad;
		Node *next;
	};

	Node *head;

public:
	void clear();
};

// ?clear@Rva00893960List@@QAEXXZ
void Rva00893960List::clear()
{
	while (head)
	{
		Node *node = head;
		if (node)
		{
			Node *next = node->next;
			g_bfmeFreeDWF(node);
			head = next;
		}
	}
}

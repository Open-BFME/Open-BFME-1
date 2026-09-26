// ?rva00155AF0Walk@Rva00155AF0Owner@@QAEXPAX0@Z
// Address-derived: walk an intrusive circular list rooted at this->m_sentinel
// (m_sentinel->m_next chain, empty when the walk returns to the sentinel).
// Each node's item (node->m_item) has its 0x31c field cleared; if the item's
// 0x204 pointer is non-null, call the already-named thunk 0x0002169D on the
// sub-object at (that pointer + 0x20) with (arg1, arg2).
class Rva00155AF0Thunk
{
public:
	void call(void *a, void *b);
};

extern void j_0002169d();

struct Rva00155AF0Item
{
	unsigned char m_pad0[0x204];
	char *m_204;
	unsigned char m_pad1[0x31c - 0x208];
	int m_31c;
};

struct Rva00155AF0Node
{
	Rva00155AF0Node *m_next;
	int m_unused4;
	Rva00155AF0Item *m_item;
};

class Rva00155AF0Owner
{
public:
	unsigned char m_pad0[4];
	Rva00155AF0Node *m_sentinel;

	void rva00155AF0Walk(void *a, void *b);
};

void Rva00155AF0Owner::rva00155AF0Walk(void *a, void *b)
{
	typedef void (Rva00155AF0Thunk::*Fn)(void *, void *);
	union { void (*raw)(); Fn member; } fn;
	fn.raw = j_0002169d;

	Rva00155AF0Node *node = m_sentinel->m_next;
	if (node == m_sentinel)
		return;

	do
	{
		Rva00155AF0Item *item = node->m_item;
		item->m_31c = 0;
		if (item->m_204 != 0)
		{
			Rva00155AF0Thunk *obj = (Rva00155AF0Thunk *)(item->m_204 + 0x20);
			(obj->*fn.member)(a, b);
		}
		node = node->m_next;
	} while (node != m_sentinel);
}

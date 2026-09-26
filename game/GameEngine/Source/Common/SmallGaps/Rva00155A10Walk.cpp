// ?rva00155A10Walk@Rva00155A10Owner@@QAEXPAX0@Z
// Address-derived: walk an intrusive circular list rooted at this->m_sentinel
// (m_sentinel->m_next chain, empty when the walk returns to the sentinel).
// Each node's item (node->m_item) has its 0x31c field cleared; if the item's
// 0x204 pointer is non-null, call the already-named thunk 0x00003BF2 on the
// sub-object at (that pointer + 0x20) with (arg1, arg2).
class Rva00155A10Thunk
{
public:
	void call(void *a, void *b);
};

extern void j_00003bf2();

struct Rva00155A10Item
{
	unsigned char m_pad0[0x204];
	char *m_204;
	unsigned char m_pad1[0x31c - 0x208];
	int m_31c;
};

struct Rva00155A10Node
{
	Rva00155A10Node *m_next;
	int m_unused4;
	Rva00155A10Item *m_item;
};

class Rva00155A10Owner
{
public:
	unsigned char m_pad0[4];
	Rva00155A10Node *m_sentinel;

	void rva00155A10Walk(void *a, void *b);
};

void Rva00155A10Owner::rva00155A10Walk(void *a, void *b)
{
	typedef void (Rva00155A10Thunk::*Fn)(void *, void *);
	union { void (*raw)(); Fn member; } fn;
	fn.raw = j_00003bf2;

	Rva00155A10Node *node = m_sentinel->m_next;
	if (node == m_sentinel)
		return;

	do
	{
		Rva00155A10Item *item = node->m_item;
		item->m_31c = 0;
		if (item->m_204 != 0)
		{
			Rva00155A10Thunk *obj = (Rva00155A10Thunk *)(item->m_204 + 0x20);
			(obj->*fn.member)(a, b);
		}
		node = node->m_next;
	} while (node != m_sentinel);
}

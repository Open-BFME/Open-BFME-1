// cl: /DNDEBUG /MD /EHsc
// address-derived identity: retail RVA 0x005C6730 (84 bytes), exact.
// Intrusive circular-list erase-by-id: walk from the sentinel, unlink the
// matching node, release its value through the shared 0x00013994 handle
// thunk, then free the node through STLport __node_alloc<true,0>.

namespace _STL
{
	template <bool threads, int inst>
	class __node_alloc
	{
	public:
		static void _M_deallocate(void *address, unsigned size);
	};
}

struct Rva005C6730Value
{
	void release();

	int m_id;
	unsigned char m_pad[8];
};

struct Rva005C6730Node
{
	Rva005C6730Node *m_next;
	Rva005C6730Node *m_prev;
	Rva005C6730Value m_value;
};

struct Rva005C6730Key
{
	int m_id;
};

class Rva005C6730List
{
public:
	void erase(Rva005C6730Key *key);

	unsigned char m_head[0x80];
	Rva005C6730Node *m_sentinel;
	unsigned char m_mid[8];
	int m_count;
};

void Rva005C6730List::erase(Rva005C6730Key *key)
{
	Rva005C6730Node *sentinel = m_sentinel;
	Rva005C6730Node *node = sentinel->m_next;

	while (node != sentinel)
	{
		if (node->m_value.m_id == key->m_id)
			break;

		node = node->m_next;
	}

	if (node == m_sentinel)
		return;

	Rva005C6730Node *next = node->m_next;
	Rva005C6730Node *prev = node->m_prev;
	prev->m_next = next;
	next->m_prev = prev;

	node->m_value.release();

	_STL::__node_alloc<true, 0>::_M_deallocate(node, 0x14);

	m_count--;
}

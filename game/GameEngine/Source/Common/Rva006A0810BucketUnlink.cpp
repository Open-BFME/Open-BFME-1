// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// The hash bucket unlink at retail 0x006A0810.
//
// The argument points at a node pointer.  The body hashes that node's key,
// finds its bucket, unlinks the node from the chain, hands the eight bytes
// back to the STLport node allocator and drops the element count at +0x10.
// A node whose key pointer is null hashes on that null pointer itself.
//
// No caller, vtable slot or string names the owner or the method, so the
// table, the node and the key all keep this body's address.

class Rva006A0810Table;

namespace _STL
{

// The retail callee is the private static member, so the friend declaration is
// what keeps the mangled name ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z.
template <bool __threads, int __inst>
class __node_alloc
{
	friend class ::Rva006A0810Table;
	static void _M_deallocate(void *p, unsigned int n);
};

}

struct Rva006A0810Key
{
	unsigned char m_pad0[8];
	unsigned int m_hash;
};

struct Rva006A0810Node
{
	Rva006A0810Node *m_next;
	Rva006A0810Key *m_key;
};

struct Rva006A0810Buckets
{
	Rva006A0810Node **m_start;
	Rva006A0810Node **m_finish;

	unsigned int size(void) const { return (unsigned int)(m_finish - m_start); }
	Rva006A0810Node *&operator[](unsigned int slot) { return m_start[slot]; }
};

class Rva006A0810Table
{
public:
	void erase(Rva006A0810Node **it);

	unsigned char m_pad0[4];
	Rva006A0810Buckets m_buckets;
	unsigned char m_gap[4];
	int m_count;
};

void Rva006A0810Table::erase(Rva006A0810Node **it)
{
	Rva006A0810Node *n = *it;

	if (n == 0)
		return;

	Rva006A0810Key *key = n->m_key;
	unsigned int h = (unsigned int)key;

	if (key != 0)
		h = key->m_hash;

	unsigned int idx = h % m_buckets.size();
	Rva006A0810Node *cur = m_buckets[idx];

	if (cur == n)
	{
		m_buckets[idx] = cur->m_next;
		_STL::__node_alloc<true, 0>::_M_deallocate(cur, 8);
		--m_count;
		return;
	}

	Rva006A0810Node *nx = cur->m_next;
	while (nx != 0)
	{
		if (nx == n)
		{
			cur->m_next = nx->m_next;
			_STL::__node_alloc<true, 0>::_M_deallocate(nx, 8);
			--m_count;
			return;
		}

		cur = nx;
		nx = cur->m_next;
	}
}

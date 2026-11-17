// cl: /DNDEBUG /MD /EHsc
// experiment: retail 0x005C8400 (69 bytes)
namespace _STL
{
	// STLport's node allocator entry point is the private
	// _STL::__node_alloc<true, 0>::_M_allocate (retail 0x0082E540); this
	// TU-local helper reaches it under its real name.
	static void *nodePoolAllocate(unsigned int bytes);
	template <bool __threads, int __inst>
	class __node_alloc
	{
		friend void *nodePoolAllocate(unsigned int);
		static void *__cdecl _M_allocate(unsigned int __n);
	};
	static inline void *nodePoolAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }

	// Retail reaches _Construct<Rva005C6730Value> through ILT 0x00030549 only.
	template <typename T>
	void _Construct(T *p, const T &val);
}

extern void j_00030549();

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

class Rva005C6730List
{
public:
	void pushBack(const Rva005C6730Value &value);

	unsigned char m_head[0x80];
	Rva005C6730Node *m_sentinel;
	unsigned char m_mid[8];
	int m_count;
};

// retail's _Construct<Rva005C6730Value> is only reachable as ILT thunk 0x00030549
static __forceinline void constructValueCopy(Rva005C6730Value *p, const Rva005C6730Value &v)
{
	((void(__cdecl *)(Rva005C6730Value *, const Rva005C6730Value &))j_00030549)(p, v);
}

void Rva005C6730List::pushBack(const Rva005C6730Value &value)
{
	Rva005C6730Node *sentinel = m_sentinel;
	Rva005C6730Node *node = (Rva005C6730Node *)_STL::nodePoolAllocate(0x14);
	constructValueCopy(&node->m_value, value);

	Rva005C6730Node *last = sentinel->m_prev;
	node->m_next = sentinel;
	node->m_prev = last;
	last->m_next = node;
	sentinel->m_prev = node;

	m_count++;
}

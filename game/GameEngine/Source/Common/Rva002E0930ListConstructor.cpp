// cl: /DNDEBUG /MD /EHsc-

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL
{

// Retail 0x0082E540 is the matched node pool refill/mutex body.
static __forceinline void *vectorSmallAllocate(unsigned int bytes);
template <bool Threads, int Instance>
class __node_alloc
{
	static void *__cdecl _M_allocate(unsigned int bytes);
	friend void *vectorSmallAllocate(unsigned int bytes);
};
static __forceinline void *vectorSmallAllocate(unsigned int bytes)
{
	return __node_alloc<true, 0>::_M_allocate(bytes);
}

}

class Rva002E0930Node
{
public:
	Rva002E0930Node *m_next;
	Rva002E0930Node *m_previous;
	void *m_value;
};

class Rva002E0930List
{
public:
	Rva002E0930List(void *first, void *second);

private:
	void *volatile m_first;
	void *volatile m_second;
	Rva002E0930Node *m_node;
};

Rva002E0930List::Rva002E0930List(void *first, void *second)
{
	m_first = first;
	m_second = second;
	_ReadWriteBarrier();
	m_node = 0;

	Rva002E0930Node *node = (Rva002E0930Node *)_STL::vectorSmallAllocate(0xc);

	node->m_next = node;
	node->m_previous = node;
	m_node = node;
}

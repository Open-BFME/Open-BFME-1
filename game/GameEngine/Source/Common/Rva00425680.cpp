// Retail constructor at RVA 0x00425680. The public class identity is unknown.

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

struct Rva00425680Node
{
	char m_char;
	unsigned char m_pad[3];
	int m_size;
	Rva00425680Node *m_next;
	Rva00425680Node *m_prev;
	int m_tail;
	int m_tail2;
};

class Rva00425680Object
{
public:
	Rva00425680Object();

	volatile int m_a;
	volatile int m_b;
	volatile int m_c;
	volatile int m_d;
	Rva00425680Node *m_node;
	volatile int m_e;
};

// ?dup_00425680@@YAXXZ
Rva00425680Object::Rva00425680Object()
{
	m_node = 0;
	m_a = 0x4e20;
	m_b = 0x5dc;
	m_c = 0;
	m_d = 5;

	m_node = (Rva00425680Node *)_STL::vectorSmallAllocate(0x18);

	m_e = 0;

	m_node->m_char = 0;
	m_node->m_size = 0;
	m_node->m_next = m_node;
	m_node->m_prev = m_node;
}

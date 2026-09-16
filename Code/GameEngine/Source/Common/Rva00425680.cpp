// Retail constructor at RVA 0x00425680. The public class identity is unknown.

namespace _STL
{
	struct __new_alloc
	{
		static void *allocate(unsigned int n);
	};
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

	m_node = (Rva00425680Node *)_STL::__new_alloc::allocate(0x18);

	m_e = 0;

	m_node->m_char = 0;
	m_node->m_size = 0;
	m_node->m_next = m_node;
	m_node->m_prev = m_node;
}

// cl: /DNDEBUG /MD /EHsc-

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};

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

	Rva002E0930Node *node = (Rva002E0930Node *)_STL::__new_alloc::allocate(0xc);

	node->m_next = node;
	node->m_previous = node;
	m_node = node;
}

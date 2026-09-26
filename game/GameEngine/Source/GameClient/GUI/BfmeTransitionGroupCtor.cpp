// Construct the transition-group state and its 12-byte circular-list
// sentinel.  The retail allocator call returns the sentinel address.

// The sentinel comes from STLport's node pool, not ::operator new: retail
// calls __node_alloc<true,0>::_M_allocate (0x0082E540), which buckets by
// (n-1)>>3 into the free-list array at 0x0130B1C0.  Shape copied from
// inputs/vendor/stlport/stl/_alloc.h, including the ternary in allocate() -- the node
// size is a compile-time constant under _MAX_BYTES, so it folds and leaves
// retail's single direct call.
void *__cdecl operator new(unsigned int);

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc
{
	enum { _MAX_BYTES = 128 };
	static void *__cdecl _M_allocate(unsigned int __n);

public:
	static void *__cdecl allocate(unsigned int __n)
	{ return (__n > (unsigned int)_MAX_BYTES) ? ::operator new(__n) : _M_allocate(__n); }
};

typedef __node_alloc<true, 0> _Node_alloc;
}

struct BFMETransitionGroupNode
{
	BFMETransitionGroupNode *m_next;
	BFMETransitionGroupNode *m_previous;
	void *m_value;
};

class BFMETransitionList
{
public:
	BFMETransitionList(void)
	{
		m_head = 0;
		BFMETransitionGroupNode *node = static_cast<BFMETransitionGroupNode *>(
			_STL::_Node_alloc::allocate(sizeof(BFMETransitionGroupNode)));
		node->m_next = node;
		node->m_previous = node;
		m_head = node;
	}

private:
	void *m_head;
};

class BFMETransitionZero
{
public:
	BFMETransitionZero(void) : m_value(0) {}

	int m_value;
};

class BFMETransitionGroup
{
public:
	BFMETransitionGroup(void);

private:
	unsigned char m_bfmeFlag;				// +0x00
	char m_bfmePadding[3];
	BFMETransitionList m_bfmeList;			// +0x04
	int m_bfmeState;					// +0x08
	int m_bfmeCount;					// +0x0C
	BFMETransitionZero m_bfmeReserved;			// +0x10
};

// ??0BFMETransitionGroup@@QAE@XZ
BFMETransitionGroup::BFMETransitionGroup(void)
{
	m_bfmeState = 1;
	m_bfmeCount = 0;
	m_bfmeFlag = 0;
}

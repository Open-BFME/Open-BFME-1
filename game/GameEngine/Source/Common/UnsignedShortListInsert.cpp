#include <new>

// Retail takes this node from STLport's node pool, not ::operator new: the
// call at this site is __node_alloc<true,0>::_M_allocate (0x0082E540), which
// buckets by (n-1)>>3 into the free-list array at 0x0130B1C0.  Shape copied
// from inputs/vendor/stlport/stl/_alloc.h, including the ternary in allocate() --
// the node size here is a compile-time constant under _MAX_BYTES, so it folds
// and leaves retail's single direct call.
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

struct BFMEUnsignedShortListNode
{
	BFMEUnsignedShortListNode *next;
	BFMEUnsignedShortListNode *previous;
	unsigned short value;
};

struct BFMEUnsignedShortListIterator
{
	BFMEUnsignedShortListNode *node;
};

class BFMEUnsignedShortListABI
{
public:
	BFMEUnsignedShortListIterator insert(BFMEUnsignedShortListIterator position,
		const unsigned short &value);
};

// ?d_000cf200@@YAXXZ
BFMEUnsignedShortListIterator BFMEUnsignedShortListABI::insert(
	BFMEUnsignedShortListIterator position, const unsigned short &value)
{
	BFMEUnsignedShortListNode *node =
		static_cast<BFMEUnsignedShortListNode *>(
			_STL::_Node_alloc::allocate(sizeof(BFMEUnsignedShortListNode)));
	new (&node->value) unsigned short(value);
	BFMEUnsignedShortListNode *previous = position.node->previous;
	node->next = position.node;
	node->previous = previous;
	previous->next = node;
	position.node->previous = node;

	BFMEUnsignedShortListIterator result = { node };
	return result;
}

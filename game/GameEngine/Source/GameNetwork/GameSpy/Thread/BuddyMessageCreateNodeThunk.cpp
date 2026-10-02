// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: list<BuddyMessage>::_M_create_node
// Retail: operator new(0x20); construct value at +8; return node.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class BuddyMessage
{
};

void *__cdecl operator new(unsigned int);

namespace _STL
{
template <class Type, class Ref>
void __cdecl _Construct(Type *dest, Ref const &src);

// Retail takes this node from STLport's node pool, not ::operator new: the
// call at this site is __node_alloc<true,0>::_M_allocate (0x0082E540), which
// buckets by (n-1)>>3 into the free-list array at 0x0130B1C0.  Shape copied
// from inputs/vendor/stlport/stl/_alloc.h, including the ternary in allocate() --
// every node size here is a compile-time constant under _MAX_BYTES, so it
// folds and leaves retail's single direct call.
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

template <class Type>
class allocator
{
};

template <class Type>
struct _List_node
{
	void *next;
	void *prev;
	// Type value at +8 (BuddyMessage sized so total node is 0x20)
	char value_space[0x18];
};

template <class Type, class Allocator>
class list
{
protected:
	_List_node<Type> *_M_create_node(Type const &);
};

template <class Type, class Allocator>
_List_node<Type> *list<Type, Allocator>::_M_create_node(Type const &x)
{
	_List_node<Type> *node =
		(_List_node<Type> *)_Node_alloc::allocate(0x20);
	_Construct((BuddyMessage *)((char *)node + 8), x);
	return node;
}

template _List_node<BuddyMessage> *list<BuddyMessage, allocator<BuddyMessage> >::_M_create_node(BuddyMessage const &);
}

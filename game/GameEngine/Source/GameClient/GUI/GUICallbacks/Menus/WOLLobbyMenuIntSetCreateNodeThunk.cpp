// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: _Rb_tree<int,int,_Identity<int>,less<int>,allocator<int>>::_M_create_node
// (std::set<int>::_M_create_node, as instantiated from WOLLobbyMenu.cpp)
// Retail: operator new(0x14); construct int value at +0x10; return node.

void *__cdecl operator new(unsigned int);
inline void *__cdecl operator new(unsigned int, void *p) { return p; }

namespace _STL
{
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
struct _Identity
{
};

template <class Type>
struct less
{
};

template <class Type>
struct _Rb_tree_node
{
	int color;
	void *parent;
	void *left;
	void *right;
	Type value;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
class _Rb_tree
{
protected:
	_Rb_tree_node<Value> *_M_create_node(Value const &);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_M_create_node(Value const &x)
{
	_Rb_tree_node<Value> *node =
		(_Rb_tree_node<Value> *)_Node_alloc::allocate(sizeof(_Rb_tree_node<Value>));
	::new (&node->value) Value(x);
	return node;
}

template _Rb_tree_node<int> *_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_M_create_node(int const &);
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: the out-of-line body of _STL::_Rb_tree<...>::_M_erase, retail
// 0x007612D0, 53 bytes. The name sat on the 5-byte incremental-link thunk at
// 0x00042FDC and the body it jumps to carried only a machine byte-dump row.
//
// The body recurses through that same thunk, which is what ties the two
// together: the call at 0x007612E6 targets 0x00042FDC, the ILT the name was
// claiming. So the thunk row retires and the name moves onto the body it always
// jumped to.
//
// STLport's node header is colour, parent, left, right, so the right child the
// recursion walks is at +0x0C and the left child it descends to is at +0x08.
// The node handed back to the allocator is 0x48 bytes, which puts the value at
// 0x38 -- larger than this instantiation's key and mapped type, so the payload
// is modelled by size rather than by field. The whole group of _M_erase bodies
// with this node size folds to one function and the ledger's spelling is the
// one that reached it.

namespace _STL
{
void __cdecl nodeDeallocate(void *block, unsigned int bytes);

struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	unsigned char _M_value_field[0x38];
};

template <class First, class Second>
struct pair
{
};

template <class Type>
struct _Select1st
{
};

template <class Type>
struct less
{
};

template <class Type>
class allocator
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
private:
	void _M_erase(_Rb_tree_node<Value> *node);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_erase(_Rb_tree_node<Value> *node)
{
	while (node != 0)
	{
		_M_erase((_Rb_tree_node<Value> *)node->_M_right);
		_Rb_tree_node_base *left = node->_M_left;
		nodeDeallocate(node, sizeof(_Rb_tree_node<Value>));
		node = (_Rb_tree_node<Value> *)left;
	}
}

typedef pair<const unsigned short, unsigned char> BfmeShortByteValue;

template class _Rb_tree<unsigned short, BfmeShortByteValue,
	_Select1st<BfmeShortByteValue>, less<unsigned short>,
	allocator<BfmeShortByteValue> >;
}

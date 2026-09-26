// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: the out-of-line body of _STL::_Rb_tree<...>::_M_copy, retail
// 0x0076AB10, 171 bytes. The name sat on the 5-byte incremental-link thunk at
// 0x0002F095 and the body it jumps to carried only a machine byte-dump row.
//
// As with the sibling _M_erase, the body recurses through its own ILT: both
// inner calls target 0x0002F095, the address the name was claiming, and
// symbols.csv already pins the name there.
//
// The node is 0x48 bytes with the STLport header -- colour, parent, left, right
// -- so the value starts at +0x10 and runs 0x38 bytes. That is larger than this
// spelling's key and mapped type together, so the payload is modelled by size
// rather than by field; the group folds and this spelling is the one whose
// thunk reaches it. Cloning a node is inlined here: allocate 0x48, construct the
// value out of line, then copy the colour byte and null both children before the
// caller writes the parent.

namespace _STL
{
void *__cdecl nodeAllocate(unsigned int bytes);

struct _Rb_tree_node_base
{
	unsigned char _M_color;
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

void __cdecl BfmeNodeValueConstruct00761A60(void *destination, const void *value);

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
private:
	_Rb_tree_node<Value> *_M_copy(_Rb_tree_node<Value> *x, _Rb_tree_node<Value> *p);

	_Rb_tree_node<Value> *_M_clone_node(_Rb_tree_node<Value> *x)
	{
		_Rb_tree_node<Value> *clone =
			(_Rb_tree_node<Value> *)nodeAllocate(sizeof(_Rb_tree_node<Value>));
		BfmeNodeValueConstruct00761A60(clone->_M_value_field, x->_M_value_field);
		clone->_M_color = x->_M_color;
		clone->_M_left = 0;
		clone->_M_right = 0;
		return clone;
	}
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_copy(
	_Rb_tree_node<Value> *x, _Rb_tree_node<Value> *p)
{
	_Rb_tree_node<Value> *top = _M_clone_node(x);
	top->_M_parent = p;

	if (x->_M_right)
		top->_M_right = _M_copy((_Rb_tree_node<Value> *)x->_M_right, top);

	p = top;
	x = (_Rb_tree_node<Value> *)x->_M_left;

	while (x != 0)
	{
		_Rb_tree_node<Value> *clone = _M_clone_node(x);
		p->_M_left = clone;
		clone->_M_parent = p;

		if (x->_M_right)
			clone->_M_right = _M_copy((_Rb_tree_node<Value> *)x->_M_right, clone);

		p = clone;
		x = (_Rb_tree_node<Value> *)x->_M_left;
	}

	return top;
}

typedef pair<const unsigned short, unsigned char> BfmeShortByteValue;

template class _Rb_tree<unsigned short, BfmeShortByteValue,
	_Select1st<BfmeShortByteValue>, less<unsigned short>,
	allocator<BfmeShortByteValue> >;
}

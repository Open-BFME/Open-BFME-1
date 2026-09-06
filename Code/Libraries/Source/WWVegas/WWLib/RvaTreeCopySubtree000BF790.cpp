// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
//
// Near-twin of _STL::_Rb_tree<...>::_M_copy (twin 0x0076AB10,
// Code/Libraries/Source/WWVegas/WWLib/RbTreeCopySubtreeBody.cpp): the same
// out-of-line node-clone recursion, but the node is 0x14 bytes here (a
// 4-byte value after the 0x10-byte STLport header) instead of 0x48.  The
// value type is a 4-byte stand-in already named by the ledger's own
// _Construct pin for this address (reverse/symbols.csv:
// ??$_Construct@URva000BF790Key@@U1@@_STL@@...), so this file reuses that
// name; the matching _M_copy callee gets its own new pin at the same ICF
// address the twin's does.

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
	unsigned char _M_value_field[4];
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

void __cdecl BfmeNodeValueConstruct000BF790(void *destination, const void *value);

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
private:
	_Rb_tree_node<Value> *_M_copy(_Rb_tree_node<Value> *x, _Rb_tree_node<Value> *p);

	_Rb_tree_node<Value> *_M_clone_node(_Rb_tree_node<Value> *x)
	{
		_Rb_tree_node<Value> *clone =
			(_Rb_tree_node<Value> *)nodeAllocate(sizeof(_Rb_tree_node<Value>));
		BfmeNodeValueConstruct000BF790(clone->_M_value_field, x->_M_value_field);
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

}

struct Rva000BF790Key
{
	unsigned char m_bytes[4];
};

namespace _STL
{
template class _Rb_tree<Rva000BF790Key, Rva000BF790Key,
	_Select1st<Rva000BF790Key>, less<Rva000BF790Key>,
	allocator<Rva000BF790Key> >;
}

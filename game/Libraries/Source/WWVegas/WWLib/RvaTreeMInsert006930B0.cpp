// cl: /DNDEBUG /MD /EHsc

// Open-BFME: STLport _Rb_tree<Rva006930B0Key, pair<const Rva006930B0Key, V> >::
// _M_insert, the four-argument form, at retail 0x006930B0.  Near-twin of
// RvaTreeMInsertRva00198190.cpp: node = 16-byte base + 8-byte pair (4-byte
// key, 4-byte mapped body).  Both the compare and construct callees are
// fresh pins here since no existing symbols.csv row named either retail
// address.

struct BfmeRbTreeInsert006930B0AnchorHelper;

namespace _STL
{

void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

inline void *BfmeNodeAllocate(unsigned int bytes)
{
	if (bytes > 128)
		return vectorLargeAllocate(bytes);
	return vectorSmallAllocate(bytes);
}

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class T1, class T2>
struct pair
{
	typedef T1 first_type;

	T1 first;
	T2 second;
};

template <class T>
struct _Select1st
{
	const typename T::first_type &operator()(const T &x) const { return x.first; }
};

template <class T>
struct less
{
	bool operator()(const T &a, const T &b) const;
};

template <class T>
struct _Nonconst_traits {};

template <class T>
class allocator {};

struct _Rb_tree_node_base
{
	int _M_color;						// +0x00
	_Rb_tree_node_base *_M_parent;				// +0x04
	_Rb_tree_node_base *_M_left;				// +0x08
	_Rb_tree_node_base *_M_right;				// +0x0C
};

template <class V>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	V _M_value_field;					// +0x10
};

template <class V, class Traits>
struct _Rb_tree_iterator
{
	_Rb_tree_iterator(_Rb_tree_node_base *node) : _M_node(node) {}

	_Rb_tree_node_base *_M_node;
};

template <class Threads>
struct _Rb_global
{
	static void __cdecl _Rebalance(_Rb_tree_node_base *x,
		_Rb_tree_node_base *&root);			// retail 0x0082C9D0
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;					// +0x00
};

template <class T, class Alloc>
struct _Rb_tree_base
{
	typedef _Rb_tree_node<T> _Node;

	_STLP_alloc_proxy<_Node *, _Node, allocator<_Node> > _M_header;	// +0x00
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree : public _Rb_tree_base<Value, Alloc>
{
public:
	typedef unsigned int size_type;
	typedef _Rb_tree_node<Value> _Node;
	typedef _Node *_Link_type;
	typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;

private:
	iterator _M_insert(_Rb_tree_node_base *x_, _Rb_tree_node_base *y_,
		const Value &v, _Rb_tree_node_base *w_);

	_Link_type _M_create_node(const Value &v)
	{
		_Link_type tmp = (_Link_type)BfmeNodeAllocate(sizeof(_Node));
		_Construct(&tmp->_M_value_field, v);
		return tmp;
	}

	static const Key &_S_key(_Rb_tree_node_base *node)
	{
		return KeyOfValue()(((_Link_type)node)->_M_value_field);
	}

	_Rb_tree_node_base *&_M_root(void) const
	{
		return this->_M_header._M_data->_M_parent;
	}

	_Rb_tree_node_base *&_M_leftmost(void) const
	{
		return this->_M_header._M_data->_M_left;
	}

	_Rb_tree_node_base *&_M_rightmost(void) const
	{
		return this->_M_header._M_data->_M_right;
	}

	size_type _M_node_count;				// +0x04
	Compare _M_key_compare;					// +0x08

	friend struct ::BfmeRbTreeInsert006930B0AnchorHelper;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_insert(
	_Rb_tree_node_base *x_, _Rb_tree_node_base *y_, const Value &v,
	_Rb_tree_node_base *w_)
{
	_Link_type w = (_Link_type)w_;
	_Link_type x = (_Link_type)x_;
	_Link_type y = (_Link_type)y_;
	_Link_type z;

	if (y == this->_M_header._M_data
		|| (w == 0 && (x != 0 || _M_key_compare(KeyOfValue()(v), _S_key(y)))))
	{
		z = _M_create_node(v);
		y->_M_left = z;
		if (y == this->_M_header._M_data)
		{
			_M_root() = z;
			_M_rightmost() = z;
		}
		else if (y == _M_leftmost())
		{
			_M_leftmost() = z;
		}
	}
	else
	{
		z = _M_create_node(v);
		y->_M_right = z;
		if (y == _M_rightmost())
			_M_rightmost() = z;
	}

	z->_M_parent = y;
	z->_M_left = 0;
	z->_M_right = 0;
	_Rb_global<bool>::_Rebalance(z, this->_M_header._M_data->_M_parent);
	++_M_node_count;
	return iterator(z);
}

}

struct BfmeRbTreeInsert006930B0AnchorHelper
{
	template <class Tree, class Value>
	static typename Tree::iterator run( Tree *tree, _STL::_Rb_tree_node_base *x,
		_STL::_Rb_tree_node_base *y, const Value &v, _STL::_Rb_tree_node_base *w )
	{
		return tree->_M_insert( x, y, v, w );
	}
};

// fresh out-of-line comparator, pinned to the retail callee at 0x0001BB85
// (an already-landed jump-thunk row, thunks_013.cpp).
struct Rva006930B0Key
{
	unsigned char m_data[4];
};

// fresh mapped body, pinned via its _Construct call to the retail callee at
// 0x000102B2 (an already-landed jump-thunk row, thunks_007.cpp).
struct Rva006930B0Value
{
	unsigned char m_data[4];
};

typedef _STL::pair<const Rva006930B0Key, Rva006930B0Value> Rva006930B0Pair;

typedef _STL::_Rb_tree<Rva006930B0Key, Rva006930B0Pair,
	_STL::_Select1st<Rva006930B0Pair>, _STL::less<Rva006930B0Key>,
	_STL::allocator<Rva006930B0Pair> > Rva006930B0Tree;

// retail 0x006930B0
Rva006930B0Tree::iterator BfmeRbTreeInsert006930B0( Rva006930B0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva006930B0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsert006930B0AnchorHelper::run( tree, x, y, v, w );
}

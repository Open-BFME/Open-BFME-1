// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport _Rb_tree<K, V>::_M_insert, the four-argument form, over a
// 16-bit key -- 4 bodies of 178 bytes.  All four carried only a machine
// byte-dump row.
//
// These are the 176-byte shape of RvaTreeMInsertPair.cpp plus exactly two
// bytes, and the two bytes are operand-size prefixes: the comparison loads the
// incoming key with `mov ax, word ptr [ebp]` and tests it against `word ptr
// [ebx+0x10]`.  A 16-bit key compared with `jb` is an unsigned short.
//
// One of the four allocates a 20-byte node: sixteen bytes of node base plus
// four bytes of value storage.  Its constructor proves a two-byte key plus a
// one-byte mapped payload.  The other three allocate 24-byte nodes, leaving
// six bytes for mapped storage whose contents are not exposed by this body.

struct BfmeRbTreeInsertAnchorHelper;

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
struct _Identity
{
	const T &operator()(const T &x) const { return x; }
};

template <class T>
struct less
{
	bool operator()(const T &a, const T &b) const { return a < b; }
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

	friend struct ::BfmeRbTreeInsertAnchorHelper;
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

struct BfmeRbTreeInsertAnchorHelper
{
	template <class Tree, class Value>
	static typename Tree::iterator run( Tree *tree, _STL::_Rb_tree_node_base *x,
		_STL::_Rb_tree_node_base *y, const Value &v, _STL::_Rb_tree_node_base *w )
	{
		return tree->_M_insert( x, y, v, w );
	}
};

struct Rva00667D40Value
{
	char m_body[ 6 ];
};

typedef _STL::pair<const unsigned short, Rva00667D40Value> Rva00667D40Pair;

typedef _STL::_Rb_tree<unsigned short, Rva00667D40Pair, _STL::_Select1st<Rva00667D40Pair>,
	_STL::less<unsigned short>, _STL::allocator<Rva00667D40Pair> > Rva00667D40Tree;

// retail 0x00667D40, a 24-byte node
Rva00667D40Tree::iterator BfmeRbTreeInsertAnchor00667D40( Rva00667D40Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00667D40Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00668730Value
{
	char m_body[ 6 ];
};

typedef _STL::pair<const unsigned short, Rva00668730Value> Rva00668730Pair;

typedef _STL::_Rb_tree<unsigned short, Rva00668730Pair, _STL::_Select1st<Rva00668730Pair>,
	_STL::less<unsigned short>, _STL::allocator<Rva00668730Pair> > Rva00668730Tree;

// retail 0x00668730, a 24-byte node
Rva00668730Tree::iterator BfmeRbTreeInsertAnchor00668730( Rva00668730Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00668730Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0093FD80Value
{
	char m_body[ 6 ];
};

typedef _STL::pair<const unsigned short, Rva0093FD80Value> Rva0093FD80Pair;

typedef _STL::_Rb_tree<unsigned short, Rva0093FD80Pair, _STL::_Select1st<Rva0093FD80Pair>,
	_STL::less<unsigned short>, _STL::allocator<Rva0093FD80Pair> > Rva0093FD80Tree;

// retail 0x0093FD80, a 24-byte node
Rva0093FD80Tree::iterator BfmeRbTreeInsertAnchor0093FD80( Rva0093FD80Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0093FD80Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

typedef _STL::pair<const unsigned short, unsigned char> Rva00667BA0Pair;

typedef _STL::_Rb_tree<unsigned short, Rva00667BA0Pair,
	_STL::_Select1st<Rva00667BA0Pair>, _STL::less<unsigned short>,
	_STL::allocator<Rva00667BA0Pair> > Rva00667BA0Tree;

// retail 0x00667BA0, a 20-byte node with a byte payload
Rva00667BA0Tree::iterator BfmeRbTreeInsertAnchor00667BA0( Rva00667BA0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00667BA0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

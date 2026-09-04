// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport _Rb_tree<K, pair<const K, V> >::_M_insert, the
// four-argument form, 49 bodies -- 48 of 176 bytes and one of 182.  Every one
// of them carried
// only a machine byte-dump row.  Most are the callee of an insert_unique
// converted in RvaTreeInsertUniqueSigned.cpp or RvaTreeInsertUniqueUnsigned.cpp
// -- that call is how those addresses were found and how their trees were
// named.  The last four were found by their shape instead: nothing that is
// itself converted calls them, so only the bytes speak for them -- and one of
// those four is not a pair at all: it reads its key at value+0x18, so its
// extractor reaches past 24 bytes rather than taking the first member.
//
// The __w_ and __x_ arguments let a caller that has already compared skip the
// comparison, and both short-circuits are visible: __w_ non-null goes straight
// to the right-hand arm, __x_ non-null straight to the left-hand one, and only
// with both null does the body compare the incoming key against the parent's.
//
// The node is _Rb_tree_node_base -- colour, parent, left, right -- and then the
// value at +0x10, so the byte pushed to the allocator is 16 plus the width of
// the pair.  That immediate is the one thing in these 176 bytes that names the
// mapped type, and it is all that names it: the value is copied by a call to
// _Construct, so its width is known and its contents are not.  Each mapped type
// is therefore a byte array of the width the allocation proves, named for the
// address of the body.
//
// One node is 472 bytes and so goes to the large allocator rather than the
// small one; that swaps a push of a byte for a push of a dword twice over and
// is the whole of the six-byte difference.
//
// The key is a signed or unsigned 32-bit scalar as the comparison spells it,
// matching the insert_unique that calls in.  _Construct is left undefined: it
// is a call here, not an inlined copy.

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

struct Rva00076F80Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva00076F80Value> Rva00076F80Pair;

typedef _STL::_Rb_tree<unsigned int, Rva00076F80Pair, _STL::_Select1st<Rva00076F80Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva00076F80Pair> > Rva00076F80Tree;

// retail 0x000768D0, called by the insert_unique at 0x00076F80
Rva00076F80Tree::iterator BfmeRbTreeInsertAnchor00076F80( Rva00076F80Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00076F80Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00077040Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva00077040Value> Rva00077040Pair;

typedef _STL::_Rb_tree<unsigned int, Rva00077040Pair, _STL::_Select1st<Rva00077040Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva00077040Pair> > Rva00077040Tree;

// retail 0x000769B0, called by the insert_unique at 0x00077040
Rva00077040Tree::iterator BfmeRbTreeInsertAnchor00077040( Rva00077040Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00077040Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0008EAA0Value
{
	char m_body[ 36 ];
};

typedef _STL::pair<const int, Rva0008EAA0Value> Rva0008EAA0Pair;

typedef _STL::_Rb_tree<int, Rva0008EAA0Pair, _STL::_Select1st<Rva0008EAA0Pair>,
	_STL::less<int>, _STL::allocator<Rva0008EAA0Pair> > Rva0008EAA0Tree;

// retail 0x0008E9C0, called by the insert_unique at 0x0008EAA0
Rva0008EAA0Tree::iterator BfmeRbTreeInsertAnchor0008EAA0( Rva0008EAA0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0008EAA0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva000A3F30Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva000A3F30Value> Rva000A3F30Pair;

typedef _STL::_Rb_tree<int, Rva000A3F30Pair, _STL::_Select1st<Rva000A3F30Pair>,
	_STL::less<int>, _STL::allocator<Rva000A3F30Pair> > Rva000A3F30Tree;

// retail 0x000A3D70, called by the insert_unique at 0x000A3F30
Rva000A3F30Tree::iterator BfmeRbTreeInsertAnchor000A3F30( Rva000A3F30Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva000A3F30Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva000E1970Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva000E1970Value> Rva000E1970Pair;

typedef _STL::_Rb_tree<int, Rva000E1970Pair, _STL::_Select1st<Rva000E1970Pair>,
	_STL::less<int>, _STL::allocator<Rva000E1970Pair> > Rva000E1970Tree;

// retail 0x000E1890, called by the insert_unique at 0x000E1970
Rva000E1970Tree::iterator BfmeRbTreeInsertAnchor000E1970( Rva000E1970Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva000E1970Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva000E1B10Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva000E1B10Value> Rva000E1B10Pair;

typedef _STL::_Rb_tree<int, Rva000E1B10Pair, _STL::_Select1st<Rva000E1B10Pair>,
	_STL::less<int>, _STL::allocator<Rva000E1B10Pair> > Rva000E1B10Tree;

// retail 0x000E1A30, called by the insert_unique at 0x000E1B10
Rva000E1B10Tree::iterator BfmeRbTreeInsertAnchor000E1B10( Rva000E1B10Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva000E1B10Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva000E7930Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva000E7930Value> Rva000E7930Pair;

typedef _STL::_Rb_tree<int, Rva000E7930Pair, _STL::_Select1st<Rva000E7930Pair>,
	_STL::less<int>, _STL::allocator<Rva000E7930Pair> > Rva000E7930Tree;

// retail 0x000E7640, called by the insert_unique at 0x000E7930
Rva000E7930Tree::iterator BfmeRbTreeInsertAnchor000E7930( Rva000E7930Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva000E7930Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva000E9850Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva000E9850Value> Rva000E9850Pair;

typedef _STL::_Rb_tree<unsigned int, Rva000E9850Pair, _STL::_Select1st<Rva000E9850Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva000E9850Pair> > Rva000E9850Tree;

// retail 0x000E9770, called by the insert_unique at 0x000E9850
Rva000E9850Tree::iterator BfmeRbTreeInsertAnchor000E9850( Rva000E9850Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva000E9850Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00127850Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const int, Rva00127850Value> Rva00127850Pair;

typedef _STL::_Rb_tree<int, Rva00127850Pair, _STL::_Select1st<Rva00127850Pair>,
	_STL::less<int>, _STL::allocator<Rva00127850Pair> > Rva00127850Tree;

// retail 0x00127770, called by the insert_unique at 0x00127850
Rva00127850Tree::iterator BfmeRbTreeInsertAnchor00127850( Rva00127850Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00127850Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00140DE0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00140DE0Value> Rva00140DE0Pair;

typedef _STL::_Rb_tree<int, Rva00140DE0Pair, _STL::_Select1st<Rva00140DE0Pair>,
	_STL::less<int>, _STL::allocator<Rva00140DE0Pair> > Rva00140DE0Tree;

// retail 0x00140D00, called by the insert_unique at 0x00140DE0
Rva00140DE0Tree::iterator BfmeRbTreeInsertAnchor00140DE0( Rva00140DE0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00140DE0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00145360Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva00145360Value> Rva00145360Pair;

typedef _STL::_Rb_tree<int, Rva00145360Pair, _STL::_Select1st<Rva00145360Pair>,
	_STL::less<int>, _STL::allocator<Rva00145360Pair> > Rva00145360Tree;

// retail 0x00145280, called by the insert_unique at 0x00145360
Rva00145360Tree::iterator BfmeRbTreeInsertAnchor00145360( Rva00145360Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00145360Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0019BD50Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva0019BD50Value> Rva0019BD50Pair;

typedef _STL::_Rb_tree<int, Rva0019BD50Pair, _STL::_Select1st<Rva0019BD50Pair>,
	_STL::less<int>, _STL::allocator<Rva0019BD50Pair> > Rva0019BD50Tree;

// retail 0x0019ADC0, called by the insert_unique at 0x0019BD50
Rva0019BD50Tree::iterator BfmeRbTreeInsertAnchor0019BD50( Rva0019BD50Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0019BD50Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0019E470Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva0019E470Value> Rva0019E470Pair;

typedef _STL::_Rb_tree<int, Rva0019E470Pair, _STL::_Select1st<Rva0019E470Pair>,
	_STL::less<int>, _STL::allocator<Rva0019E470Pair> > Rva0019E470Tree;

// retail 0x0019E350, called by the insert_unique at 0x0019E470
Rva0019E470Tree::iterator BfmeRbTreeInsertAnchor0019E470( Rva0019E470Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0019E470Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva001B6DA0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva001B6DA0Value> Rva001B6DA0Pair;

typedef _STL::_Rb_tree<int, Rva001B6DA0Pair, _STL::_Select1st<Rva001B6DA0Pair>,
	_STL::less<int>, _STL::allocator<Rva001B6DA0Pair> > Rva001B6DA0Tree;

// retail 0x001B6CC0, called by the insert_unique at 0x001B6DA0
Rva001B6DA0Tree::iterator BfmeRbTreeInsertAnchor001B6DA0( Rva001B6DA0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva001B6DA0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva001D8660Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva001D8660Value> Rva001D8660Pair;

typedef _STL::_Rb_tree<int, Rva001D8660Pair, _STL::_Select1st<Rva001D8660Pair>,
	_STL::less<int>, _STL::allocator<Rva001D8660Pair> > Rva001D8660Tree;

// retail 0x001D8580, called by the insert_unique at 0x001D8660
Rva001D8660Tree::iterator BfmeRbTreeInsertAnchor001D8660( Rva001D8660Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva001D8660Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0021BE20Value
{
	char m_body[ 8 ];
};

typedef _STL::pair<const unsigned int, Rva0021BE20Value> Rva0021BE20Pair;

typedef _STL::_Rb_tree<unsigned int, Rva0021BE20Pair, _STL::_Select1st<Rva0021BE20Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva0021BE20Pair> > Rva0021BE20Tree;

// retail 0x0021B600, called by the insert_unique at 0x0021BE20
Rva0021BE20Tree::iterator BfmeRbTreeInsertAnchor0021BE20( Rva0021BE20Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0021BE20Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00223E00Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00223E00Value> Rva00223E00Pair;

typedef _STL::_Rb_tree<int, Rva00223E00Pair, _STL::_Select1st<Rva00223E00Pair>,
	_STL::less<int>, _STL::allocator<Rva00223E00Pair> > Rva00223E00Tree;

// retail 0x00223D20, called by the insert_unique at 0x00223E00
Rva00223E00Tree::iterator BfmeRbTreeInsertAnchor00223E00( Rva00223E00Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00223E00Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00223FA0Value
{
	char m_body[ 40 ];
};

typedef _STL::pair<const unsigned int, Rva00223FA0Value> Rva00223FA0Pair;

typedef _STL::_Rb_tree<unsigned int, Rva00223FA0Pair, _STL::_Select1st<Rva00223FA0Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva00223FA0Pair> > Rva00223FA0Tree;

// retail 0x00223EC0, called by the insert_unique at 0x00223FA0
Rva00223FA0Tree::iterator BfmeRbTreeInsertAnchor00223FA0( Rva00223FA0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00223FA0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00224140Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00224140Value> Rva00224140Pair;

typedef _STL::_Rb_tree<int, Rva00224140Pair, _STL::_Select1st<Rva00224140Pair>,
	_STL::less<int>, _STL::allocator<Rva00224140Pair> > Rva00224140Tree;

// retail 0x00224060, called by the insert_unique at 0x00224140
Rva00224140Tree::iterator BfmeRbTreeInsertAnchor00224140( Rva00224140Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00224140Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva002253A0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva002253A0Value> Rva002253A0Pair;

typedef _STL::_Rb_tree<int, Rva002253A0Pair, _STL::_Select1st<Rva002253A0Pair>,
	_STL::less<int>, _STL::allocator<Rva002253A0Pair> > Rva002253A0Tree;

// retail 0x00224200, called by the insert_unique at 0x002253A0
Rva002253A0Tree::iterator BfmeRbTreeInsertAnchor002253A0( Rva002253A0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva002253A0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00225540Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00225540Value> Rva00225540Pair;

typedef _STL::_Rb_tree<int, Rva00225540Pair, _STL::_Select1st<Rva00225540Pair>,
	_STL::less<int>, _STL::allocator<Rva00225540Pair> > Rva00225540Tree;

// retail 0x00225460, called by the insert_unique at 0x00225540
Rva00225540Tree::iterator BfmeRbTreeInsertAnchor00225540( Rva00225540Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00225540Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0023B5B0Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const int, Rva0023B5B0Value> Rva0023B5B0Pair;

typedef _STL::_Rb_tree<int, Rva0023B5B0Pair, _STL::_Select1st<Rva0023B5B0Pair>,
	_STL::less<int>, _STL::allocator<Rva0023B5B0Pair> > Rva0023B5B0Tree;

// retail 0x0023B4D0, called by the insert_unique at 0x0023B5B0
Rva0023B5B0Tree::iterator BfmeRbTreeInsertAnchor0023B5B0( Rva0023B5B0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0023B5B0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00372570Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva00372570Value> Rva00372570Pair;

typedef _STL::_Rb_tree<int, Rva00372570Pair, _STL::_Select1st<Rva00372570Pair>,
	_STL::less<int>, _STL::allocator<Rva00372570Pair> > Rva00372570Tree;

// retail 0x00370BF0, called by the insert_unique at 0x00372570
Rva00372570Tree::iterator BfmeRbTreeInsertAnchor00372570( Rva00372570Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00372570Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00375F30Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const int, Rva00375F30Value> Rva00375F30Pair;

typedef _STL::_Rb_tree<int, Rva00375F30Pair, _STL::_Select1st<Rva00375F30Pair>,
	_STL::less<int>, _STL::allocator<Rva00375F30Pair> > Rva00375F30Tree;

// retail 0x003754B0, called by the insert_unique at 0x00375F30
Rva00375F30Tree::iterator BfmeRbTreeInsertAnchor00375F30( Rva00375F30Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00375F30Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva003DBF80Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva003DBF80Value> Rva003DBF80Pair;

typedef _STL::_Rb_tree<unsigned int, Rva003DBF80Pair, _STL::_Select1st<Rva003DBF80Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva003DBF80Pair> > Rva003DBF80Tree;

// retail 0x003DBEA0, called by the insert_unique at 0x003DBF80
Rva003DBF80Tree::iterator BfmeRbTreeInsertAnchor003DBF80( Rva003DBF80Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva003DBF80Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva003FF8D0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva003FF8D0Value> Rva003FF8D0Pair;

typedef _STL::_Rb_tree<unsigned int, Rva003FF8D0Pair, _STL::_Select1st<Rva003FF8D0Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva003FF8D0Pair> > Rva003FF8D0Tree;

// retail 0x003FF7F0, called by the insert_unique at 0x003FF8D0
Rva003FF8D0Tree::iterator BfmeRbTreeInsertAnchor003FF8D0( Rva003FF8D0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva003FF8D0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva003FFA70Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva003FFA70Value> Rva003FFA70Pair;

typedef _STL::_Rb_tree<int, Rva003FFA70Pair, _STL::_Select1st<Rva003FFA70Pair>,
	_STL::less<int>, _STL::allocator<Rva003FFA70Pair> > Rva003FFA70Tree;

// retail 0x003FF990, called by the insert_unique at 0x003FFA70
Rva003FFA70Tree::iterator BfmeRbTreeInsertAnchor003FFA70( Rva003FFA70Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva003FFA70Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00405DB0Value
{
	char m_body[ 32 ];
};

typedef _STL::pair<const unsigned int, Rva00405DB0Value> Rva00405DB0Pair;

typedef _STL::_Rb_tree<unsigned int, Rva00405DB0Pair, _STL::_Select1st<Rva00405DB0Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva00405DB0Pair> > Rva00405DB0Tree;

// retail 0x00405CD0, called by the insert_unique at 0x00405DB0
Rva00405DB0Tree::iterator BfmeRbTreeInsertAnchor00405DB0( Rva00405DB0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00405DB0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0040AAD0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva0040AAD0Value> Rva0040AAD0Pair;

typedef _STL::_Rb_tree<unsigned int, Rva0040AAD0Pair, _STL::_Select1st<Rva0040AAD0Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva0040AAD0Pair> > Rva0040AAD0Tree;

// retail 0x0040A920, called by the insert_unique at 0x0040AAD0
Rva0040AAD0Tree::iterator BfmeRbTreeInsertAnchor0040AAD0( Rva0040AAD0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0040AAD0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva004746D0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva004746D0Value> Rva004746D0Pair;

typedef _STL::_Rb_tree<int, Rva004746D0Pair, _STL::_Select1st<Rva004746D0Pair>,
	_STL::less<int>, _STL::allocator<Rva004746D0Pair> > Rva004746D0Tree;

// retail 0x004745F0, called by the insert_unique at 0x004746D0
Rva004746D0Tree::iterator BfmeRbTreeInsertAnchor004746D0( Rva004746D0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva004746D0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva004A6D40Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva004A6D40Value> Rva004A6D40Pair;

typedef _STL::_Rb_tree<int, Rva004A6D40Pair, _STL::_Select1st<Rva004A6D40Pair>,
	_STL::less<int>, _STL::allocator<Rva004A6D40Pair> > Rva004A6D40Tree;

// retail 0x004A6C00, called by the insert_unique at 0x004A6D40
Rva004A6D40Tree::iterator BfmeRbTreeInsertAnchor004A6D40( Rva004A6D40Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva004A6D40Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva004B0C80Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva004B0C80Value> Rva004B0C80Pair;

typedef _STL::_Rb_tree<unsigned int, Rva004B0C80Pair, _STL::_Select1st<Rva004B0C80Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva004B0C80Pair> > Rva004B0C80Tree;

// retail 0x004B0BA0, called by the insert_unique at 0x004B0C80
Rva004B0C80Tree::iterator BfmeRbTreeInsertAnchor004B0C80( Rva004B0C80Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva004B0C80Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva004E4F60Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva004E4F60Value> Rva004E4F60Pair;

typedef _STL::_Rb_tree<int, Rva004E4F60Pair, _STL::_Select1st<Rva004E4F60Pair>,
	_STL::less<int>, _STL::allocator<Rva004E4F60Pair> > Rva004E4F60Tree;

// retail 0x004E4E80, called by the insert_unique at 0x004E4F60
Rva004E4F60Tree::iterator BfmeRbTreeInsertAnchor004E4F60( Rva004E4F60Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva004E4F60Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00586710Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva00586710Value> Rva00586710Pair;

typedef _STL::_Rb_tree<unsigned int, Rva00586710Pair, _STL::_Select1st<Rva00586710Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva00586710Pair> > Rva00586710Tree;

// retail 0x00586630, called by the insert_unique at 0x00586710
Rva00586710Tree::iterator BfmeRbTreeInsertAnchor00586710( Rva00586710Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00586710Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00587A60Value
{
	char m_body[ 60 ];
};

typedef _STL::pair<const int, Rva00587A60Value> Rva00587A60Pair;

typedef _STL::_Rb_tree<int, Rva00587A60Pair, _STL::_Select1st<Rva00587A60Pair>,
	_STL::less<int>, _STL::allocator<Rva00587A60Pair> > Rva00587A60Tree;

// retail 0x005877F0, called by the insert_unique at 0x00587A60
Rva00587A60Tree::iterator BfmeRbTreeInsertAnchor00587A60( Rva00587A60Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00587A60Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00593160Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00593160Value> Rva00593160Pair;

typedef _STL::_Rb_tree<int, Rva00593160Pair, _STL::_Select1st<Rva00593160Pair>,
	_STL::less<int>, _STL::allocator<Rva00593160Pair> > Rva00593160Tree;

// retail 0x00591400, called by the insert_unique at 0x00593160
Rva00593160Tree::iterator BfmeRbTreeInsertAnchor00593160( Rva00593160Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00593160Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva005D2B10Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva005D2B10Value> Rva005D2B10Pair;

typedef _STL::_Rb_tree<unsigned int, Rva005D2B10Pair, _STL::_Select1st<Rva005D2B10Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva005D2B10Pair> > Rva005D2B10Tree;

// retail 0x005D2A30, called by the insert_unique at 0x005D2B10
Rva005D2B10Tree::iterator BfmeRbTreeInsertAnchor005D2B10( Rva005D2B10Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva005D2B10Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00611F60Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00611F60Value> Rva00611F60Pair;

typedef _STL::_Rb_tree<int, Rva00611F60Pair, _STL::_Select1st<Rva00611F60Pair>,
	_STL::less<int>, _STL::allocator<Rva00611F60Pair> > Rva00611F60Tree;

// retail 0x00611E80, called by the insert_unique at 0x00611F60
Rva00611F60Tree::iterator BfmeRbTreeInsertAnchor00611F60( Rva00611F60Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00611F60Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva006325D0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva006325D0Value> Rva006325D0Pair;

typedef _STL::_Rb_tree<int, Rva006325D0Pair, _STL::_Select1st<Rva006325D0Pair>,
	_STL::less<int>, _STL::allocator<Rva006325D0Pair> > Rva006325D0Tree;

// retail 0x006324F0, called by the insert_unique at 0x006325D0
Rva006325D0Tree::iterator BfmeRbTreeInsertAnchor006325D0( Rva006325D0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva006325D0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00645EC0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00645EC0Value> Rva00645EC0Pair;

typedef _STL::_Rb_tree<int, Rva00645EC0Pair, _STL::_Select1st<Rva00645EC0Pair>,
	_STL::less<int>, _STL::allocator<Rva00645EC0Pair> > Rva00645EC0Tree;

// retail 0x00645DE0, called by the insert_unique at 0x00645EC0
Rva00645EC0Tree::iterator BfmeRbTreeInsertAnchor00645EC0( Rva00645EC0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00645EC0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00653E70Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const int, Rva00653E70Value> Rva00653E70Pair;

typedef _STL::_Rb_tree<int, Rva00653E70Pair, _STL::_Select1st<Rva00653E70Pair>,
	_STL::less<int>, _STL::allocator<Rva00653E70Pair> > Rva00653E70Tree;

// retail 0x00653D90, called by the insert_unique at 0x00653E70
Rva00653E70Tree::iterator BfmeRbTreeInsertAnchor00653E70( Rva00653E70Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00653E70Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva006A4630Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva006A4630Value> Rva006A4630Pair;

typedef _STL::_Rb_tree<unsigned int, Rva006A4630Pair, _STL::_Select1st<Rva006A4630Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva006A4630Pair> > Rva006A4630Tree;

// retail 0x006A12D0, called by the insert_unique at 0x006A4630
Rva006A4630Tree::iterator BfmeRbTreeInsertAnchor006A4630( Rva006A4630Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva006A4630Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva008FFE90Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const unsigned int, Rva008FFE90Value> Rva008FFE90Pair;

typedef _STL::_Rb_tree<unsigned int, Rva008FFE90Pair, _STL::_Select1st<Rva008FFE90Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva008FFE90Pair> > Rva008FFE90Tree;

// retail 0x008FFDE0, called by the insert_unique at 0x008FFE90
Rva008FFE90Tree::iterator BfmeRbTreeInsertAnchor008FFE90( Rva008FFE90Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva008FFE90Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0094CCF0Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const unsigned int, Rva0094CCF0Value> Rva0094CCF0Pair;

typedef _STL::_Rb_tree<unsigned int, Rva0094CCF0Pair, _STL::_Select1st<Rva0094CCF0Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva0094CCF0Pair> > Rva0094CCF0Tree;

// retail 0x0094C9E0, called by the insert_unique at 0x0094CCF0
Rva0094CCF0Tree::iterator BfmeRbTreeInsertAnchor0094CCF0( Rva0094CCF0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0094CCF0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0065DC00Value
{
	char m_body[ 452 ];
};

typedef _STL::pair<const int, Rva0065DC00Value> Rva0065DC00Pair;

typedef _STL::_Rb_tree<int, Rva0065DC00Pair, _STL::_Select1st<Rva0065DC00Pair>,
	_STL::less<int>, _STL::allocator<Rva0065DC00Pair> > Rva0065DC00Tree;

// retail 0x0065DB10, called by the insert_unique at 0x0065DC00
Rva0065DC00Tree::iterator BfmeRbTreeInsertAnchor0065DC00( Rva0065DC00Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0065DC00Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00064A30Value
{
	char m_lead[ 24 ];
	unsigned int m_key;
};

// Not _Select1st: this body reads the key at value+0x18 and at node+0x28, so
// the extractor reaches past 24 bytes of the value to get it.
struct Rva00064A30KeyOfValue
{
	const unsigned int &operator()( const Rva00064A30Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<unsigned int, Rva00064A30Value, Rva00064A30KeyOfValue,
	_STL::less<unsigned int>, _STL::allocator<Rva00064A30Value> > Rva00064A30Tree;

// retail 0x00064A30, a 44-byte node
Rva00064A30Tree::iterator BfmeRbTreeInsertAnchor00064A30( Rva00064A30Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00064A30Value &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva000A1040Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva000A1040Value> Rva000A1040Pair;

typedef _STL::_Rb_tree<unsigned int, Rva000A1040Pair, _STL::_Select1st<Rva000A1040Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva000A1040Pair> > Rva000A1040Tree;

// retail 0x000A1040, a 24-byte node
Rva000A1040Tree::iterator BfmeRbTreeInsertAnchor000A1040( Rva000A1040Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva000A1040Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0094CA90Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva0094CA90Value> Rva0094CA90Pair;

typedef _STL::_Rb_tree<unsigned int, Rva0094CA90Pair, _STL::_Select1st<Rva0094CA90Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva0094CA90Pair> > Rva0094CA90Tree;

// retail 0x0094CA90, a 24-byte node
Rva0094CA90Tree::iterator BfmeRbTreeInsertAnchor0094CA90( Rva0094CA90Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0094CA90Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva009EDBE0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const unsigned int, Rva009EDBE0Value> Rva009EDBE0Pair;

typedef _STL::_Rb_tree<unsigned int, Rva009EDBE0Pair, _STL::_Select1st<Rva009EDBE0Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva009EDBE0Pair> > Rva009EDBE0Tree;

// retail 0x009EDBE0, a 24-byte node
Rva009EDBE0Tree::iterator BfmeRbTreeInsertAnchor009EDBE0( Rva009EDBE0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva009EDBE0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva002A1E90Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const unsigned int, Rva002A1E90Value> Rva002A1E90Pair;

typedef _STL::_Rb_tree<unsigned int, Rva002A1E90Pair,
	_STL::_Select1st<Rva002A1E90Pair>, _STL::less<unsigned int>,
	_STL::allocator<Rva002A1E90Pair> > Rva002A1E90Tree;

// retail 0x002A1C20
Rva002A1E90Tree::iterator BfmeRbTreeInsertAnchor002A1C20(
	Rva002A1E90Tree *tree, _STL::_Rb_tree_node_base *x,
	_STL::_Rb_tree_node_base *y, const Rva002A1E90Pair &v,
	_STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}


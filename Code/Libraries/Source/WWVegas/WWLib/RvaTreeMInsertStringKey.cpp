// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport _Rb_tree<K, V>::_M_insert, the four-argument form, over a
// string key -- 24 bodies, 183 bytes each but for two that allocate a node too
// large for the small allocator.  All of them carried only a machine byte-dump
// row.
//
// These are the four-argument _M_insert of RvaTreeMInsertPair.cpp with one
// extra call: where a scalar key compiles to a `cmp` and a conditional set,
// these load the incoming value into ecx, push the address of the parent's own
// value, call, and branch on the sign of the returned int.  That call is what
// names the key, and all three of its targets are already in the ledger:
//
//   0x0005FEB0  ?compare@AsciiString@@QBEHABV1@@Z              19 bodies
//   0x00090570  ?compareNoCase@?$StringBase@D@@QBEHABV1@@Z     3 bodies
//   0x0005FFA0  ?compare@?$StringBase@G@@QBEHABV1@@Z           2 bodies
//
// So the key is AsciiString in 19 of them and StringBase<unsigned short> in the
// other 2; and the 3 that reach compareNoCase are ordered case-insensitively,
// which is a different comparator over the same key and so a different tree.
// The comparator's retail name is not recovered -- only what it calls -- so it
// is declared here and spelled for what it does.
//
// The node size names the rest.  Sixteen bytes of _Rb_tree_node_base and four
// of value leaves no room for a pair, so the two trees with a 20-byte node are
// _Identity over the key; the rest are pairs whose mapped type is a byte array
// of what is left.  Two nodes run past 128 bytes and route to the large
// allocator rather than the small one, which is the whole six-byte difference
// between the 183-byte bodies and the 189-byte ones.
//
// An earlier revision of this file spelled every key as an opaque four-byte
// class with an out-of-line compare.  That was true and it was less than the
// bytes said: the compare's own address was sitting in the displacement.

template <class Character>
class StringBase
{
public:
	int compare( const StringBase &other ) const;
	int compareNoCase( const StringBase &other ) const;

protected:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	int compare( const AsciiString &other ) const;
};

typedef StringBase<unsigned short> BfmeWideString;

inline bool operator<( const AsciiString &left, const AsciiString &right )
{
	return left.compare( right ) < 0;
}

inline bool operator<( const BfmeWideString &left, const BfmeWideString &right )
{
	return left.compare( right ) < 0;
}

// The comparator retail used here is not named anywhere the bytes reach; what
// it calls is StringBase<char>::compareNoCase, so it is spelled for that.
struct BfmeStringNoCaseLess
{
	bool operator()( const AsciiString &left, const AsciiString &right ) const
	{
		return left.compareNoCase( right ) < 0;
	}
};

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

struct Rva0007D900Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva0007D900Value> Rva0007D900Pair;

typedef _STL::_Rb_tree<AsciiString, Rva0007D900Pair, _STL::_Select1st<Rva0007D900Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva0007D900Pair> > Rva0007D900Tree;

// retail 0x0007D900, a 24-byte node: four bytes of key and 4 of mapped type
Rva0007D900Tree::iterator BfmeRbTreeInsertAnchor0007D900( Rva0007D900Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0007D900Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00093670Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00093670Value> Rva00093670Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00093670Pair, _STL::_Select1st<Rva00093670Pair>,
	BfmeStringNoCaseLess, _STL::allocator<Rva00093670Pair> > Rva00093670Tree;

// retail 0x00093670, a 24-byte node: four bytes of key and 4 of mapped type
Rva00093670Tree::iterator BfmeRbTreeInsertAnchor00093670( Rva00093670Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00093670Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva000BFA40Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const AsciiString, Rva000BFA40Value> Rva000BFA40Pair;

typedef _STL::_Rb_tree<AsciiString, Rva000BFA40Pair, _STL::_Select1st<Rva000BFA40Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva000BFA40Pair> > Rva000BFA40Tree;

// retail 0x000BFA40, a 32-byte node: four bytes of key and 12 of mapped type
Rva000BFA40Tree::iterator BfmeRbTreeInsertAnchor000BFA40( Rva000BFA40Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva000BFA40Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	_STL::less<AsciiString>, _STL::allocator<AsciiString> > Rva000BFCC0Tree;

// retail 0x000BFCC0, a 20-byte node: the value is the key
Rva000BFCC0Tree::iterator BfmeRbTreeInsertAnchor000BFCC0( Rva000BFCC0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const AsciiString &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva000C1740Value
{
	char m_body[ 252 ];
};

typedef _STL::pair<const AsciiString, Rva000C1740Value> Rva000C1740Pair;

typedef _STL::_Rb_tree<AsciiString, Rva000C1740Pair, _STL::_Select1st<Rva000C1740Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva000C1740Pair> > Rva000C1740Tree;

// retail 0x000C1740, a 272-byte node: four bytes of key and 252 of mapped type
Rva000C1740Tree::iterator BfmeRbTreeInsertAnchor000C1740( Rva000C1740Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva000C1740Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00142DF0Value
{
	char m_body[ 112 ];
};

typedef _STL::pair<const AsciiString, Rva00142DF0Value> Rva00142DF0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00142DF0Pair, _STL::_Select1st<Rva00142DF0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00142DF0Pair> > Rva00142DF0Tree;

// retail 0x00142DF0, a 132-byte node: four bytes of key and 112 of mapped type
Rva00142DF0Tree::iterator BfmeRbTreeInsertAnchor00142DF0( Rva00142DF0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00142DF0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00142EE0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00142EE0Value> Rva00142EE0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00142EE0Pair, _STL::_Select1st<Rva00142EE0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00142EE0Pair> > Rva00142EE0Tree;

// retail 0x00142EE0, a 24-byte node: four bytes of key and 4 of mapped type
Rva00142EE0Tree::iterator BfmeRbTreeInsertAnchor00142EE0( Rva00142EE0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00142EE0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	BfmeStringNoCaseLess, _STL::allocator<AsciiString> > Rva00195D30Tree;

// retail 0x00195D30, a 20-byte node: the value is the key
Rva00195D30Tree::iterator BfmeRbTreeInsertAnchor00195D30( Rva00195D30Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const AsciiString &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0033F870Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva0033F870Value> Rva0033F870Pair;

typedef _STL::_Rb_tree<AsciiString, Rva0033F870Pair, _STL::_Select1st<Rva0033F870Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva0033F870Pair> > Rva0033F870Tree;

// retail 0x0033F870, a 24-byte node: four bytes of key and 4 of mapped type
Rva0033F870Tree::iterator BfmeRbTreeInsertAnchor0033F870( Rva0033F870Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0033F870Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0033F960Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva0033F960Value> Rva0033F960Pair;

typedef _STL::_Rb_tree<AsciiString, Rva0033F960Pair, _STL::_Select1st<Rva0033F960Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva0033F960Pair> > Rva0033F960Tree;

// retail 0x0033F960, a 24-byte node: four bytes of key and 4 of mapped type
Rva0033F960Tree::iterator BfmeRbTreeInsertAnchor0033F960( Rva0033F960Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0033F960Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva003B9B40Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva003B9B40Value> Rva003B9B40Pair;

typedef _STL::_Rb_tree<AsciiString, Rva003B9B40Pair, _STL::_Select1st<Rva003B9B40Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva003B9B40Pair> > Rva003B9B40Tree;

// retail 0x003B9B40, a 24-byte node: four bytes of key and 4 of mapped type
Rva003B9B40Tree::iterator BfmeRbTreeInsertAnchor003B9B40( Rva003B9B40Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva003B9B40Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva003D3F90Value
{
	char m_body[ 8 ];
};

typedef _STL::pair<const AsciiString, Rva003D3F90Value> Rva003D3F90Pair;

typedef _STL::_Rb_tree<AsciiString, Rva003D3F90Pair, _STL::_Select1st<Rva003D3F90Pair>,
	BfmeStringNoCaseLess, _STL::allocator<Rva003D3F90Pair> > Rva003D3F90Tree;

// retail 0x003D3F90, a 28-byte node: four bytes of key and 8 of mapped type
Rva003D3F90Tree::iterator BfmeRbTreeInsertAnchor003D3F90( Rva003D3F90Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva003D3F90Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00424520Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00424520Value> Rva00424520Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00424520Pair, _STL::_Select1st<Rva00424520Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00424520Pair> > Rva00424520Tree;

// retail 0x00424520, a 24-byte node: four bytes of key and 4 of mapped type
Rva00424520Tree::iterator BfmeRbTreeInsertAnchor00424520( Rva00424520Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00424520Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00448C60Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00448C60Value> Rva00448C60Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00448C60Pair, _STL::_Select1st<Rva00448C60Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00448C60Pair> > Rva00448C60Tree;

// retail 0x00448C60, a 24-byte node: four bytes of key and 4 of mapped type
Rva00448C60Tree::iterator BfmeRbTreeInsertAnchor00448C60( Rva00448C60Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00448C60Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00449BF0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00449BF0Value> Rva00449BF0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00449BF0Pair, _STL::_Select1st<Rva00449BF0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00449BF0Pair> > Rva00449BF0Tree;

// retail 0x00449BF0, a 24-byte node: four bytes of key and 4 of mapped type
Rva00449BF0Tree::iterator BfmeRbTreeInsertAnchor00449BF0( Rva00449BF0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00449BF0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00461630Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00461630Value> Rva00461630Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00461630Pair, _STL::_Select1st<Rva00461630Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00461630Pair> > Rva00461630Tree;

// retail 0x00461630, a 24-byte node: four bytes of key and 4 of mapped type
Rva00461630Tree::iterator BfmeRbTreeInsertAnchor00461630( Rva00461630Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00461630Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00475080Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00475080Value> Rva00475080Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00475080Pair, _STL::_Select1st<Rva00475080Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00475080Pair> > Rva00475080Tree;

// retail 0x00475080, a 24-byte node: four bytes of key and 4 of mapped type
Rva00475080Tree::iterator BfmeRbTreeInsertAnchor00475080( Rva00475080Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00475080Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva00475300Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00475300Value> Rva00475300Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00475300Pair, _STL::_Select1st<Rva00475300Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00475300Pair> > Rva00475300Tree;

// retail 0x00475300, a 24-byte node: four bytes of key and 4 of mapped type
Rva00475300Tree::iterator BfmeRbTreeInsertAnchor00475300( Rva00475300Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva00475300Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0054EF10Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const BfmeWideString, Rva0054EF10Value> Rva0054EF10Pair;

typedef _STL::_Rb_tree<BfmeWideString, Rva0054EF10Pair, _STL::_Select1st<Rva0054EF10Pair>,
	_STL::less<BfmeWideString>, _STL::allocator<Rva0054EF10Pair> > Rva0054EF10Tree;

// retail 0x0054EF10, a 24-byte node: four bytes of key and 4 of mapped type
Rva0054EF10Tree::iterator BfmeRbTreeInsertAnchor0054EF10( Rva0054EF10Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0054EF10Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva005C7490Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva005C7490Value> Rva005C7490Pair;

typedef _STL::_Rb_tree<AsciiString, Rva005C7490Pair, _STL::_Select1st<Rva005C7490Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva005C7490Pair> > Rva005C7490Tree;

// retail 0x005C7490, a 24-byte node: four bytes of key and 4 of mapped type
Rva005C7490Tree::iterator BfmeRbTreeInsertAnchor005C7490( Rva005C7490Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva005C7490Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva0068FAF0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const BfmeWideString, Rva0068FAF0Value> Rva0068FAF0Pair;

typedef _STL::_Rb_tree<BfmeWideString, Rva0068FAF0Pair, _STL::_Select1st<Rva0068FAF0Pair>,
	_STL::less<BfmeWideString>, _STL::allocator<Rva0068FAF0Pair> > Rva0068FAF0Tree;

// retail 0x0068FAF0, a 24-byte node: four bytes of key and 4 of mapped type
Rva0068FAF0Tree::iterator BfmeRbTreeInsertAnchor0068FAF0( Rva0068FAF0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva0068FAF0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva009C98A0Value
{
	char m_body[ 28 ];
};

typedef _STL::pair<const AsciiString, Rva009C98A0Value> Rva009C98A0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva009C98A0Pair, _STL::_Select1st<Rva009C98A0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva009C98A0Pair> > Rva009C98A0Tree;

// retail 0x009C98A0, a 48-byte node: four bytes of key and 28 of mapped type
Rva009C98A0Tree::iterator BfmeRbTreeInsertAnchor009C98A0( Rva009C98A0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva009C98A0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva009CF5A0Value
{
	char m_body[ 28 ];
};

typedef _STL::pair<const AsciiString, Rva009CF5A0Value> Rva009CF5A0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva009CF5A0Pair, _STL::_Select1st<Rva009CF5A0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva009CF5A0Pair> > Rva009CF5A0Tree;

// retail 0x009CF5A0, a 48-byte node: four bytes of key and 28 of mapped type
Rva009CF5A0Tree::iterator BfmeRbTreeInsertAnchor009CF5A0( Rva009CF5A0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva009CF5A0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Rva009CF7A0Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const AsciiString, Rva009CF7A0Value> Rva009CF7A0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva009CF7A0Pair, _STL::_Select1st<Rva009CF7A0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva009CF7A0Pair> > Rva009CF7A0Tree;

// retail 0x009CF7A0, a 36-byte node: four bytes of key and 16 of mapped type
Rva009CF7A0Tree::iterator BfmeRbTreeInsertAnchor009CF7A0( Rva009CF7A0Tree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva009CF7A0Pair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}


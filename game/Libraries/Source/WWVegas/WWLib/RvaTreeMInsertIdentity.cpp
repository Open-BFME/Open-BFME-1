// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport _Rb_tree<K, K, _Identity<K> >::_M_insert, the
// four-argument form, 8 bodies of 179 bytes each.  Every one of them carried
// only a machine byte-dump row, and every one is the callee of an
// insert_unique converted in RvaTreeInsertUniqueIdentity.cpp -- that call is
// what found these addresses and what named their trees.
//
// The __w_ and __x_ arguments let a caller that has already compared skip the
// comparison, and both short-circuits are visible: __w_ non-null goes straight
// to the right-hand arm, __x_ non-null straight to the left-hand one, and only
// with both null does the body compare the incoming key against the parent's.
//
// The node these push to the allocator is 20 bytes -- sixteen of
// _Rb_tree_node_base and four of value -- which is what makes them _Identity
// trees rather than the pair-valued ones in RvaTreeMInsertPair.cpp: no pair
// fits in four bytes, so the value is the key.  The three extra bytes over the
// pair form are that construction, which inlines here instead of calling
// _Construct.
//
// The null check between the allocation and the value store is not a guard
// anyone wrote.  It is placement new: MSVC 7.1 tests the pointer that
// operator new(size_t, void *) hands back before constructing through it.
//
// The key is still known only by its comparison -- an enumeration where retail
// emits `setl`, a pointer where it emits `setb` -- and is named for the address
// of the insert_unique that reaches it, exactly as that source spells it.

inline void *operator new(unsigned int, void *place) { return place; }

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
inline void _Construct(T1 *p, const T2 &value)
{
	new (p) T1(value);
}

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
		_STL::_Rb_tree_node_base *y, const Value &value, _STL::_Rb_tree_node_base *w )
	{
		return tree->_M_insert( x, y, value, w );
	}
};

enum Rva000EEC50Key
{
	RVA_000EEC50_KEY_ZERO = 0
};

typedef _STL::_Rb_tree<Rva000EEC50Key, Rva000EEC50Key, _STL::_Identity<Rva000EEC50Key>,
	_STL::less<Rva000EEC50Key>, _STL::allocator<Rva000EEC50Key> > EnumIdentityTree000EEC50;

// retail 0x000EE420, called by the insert_unique at 0x000EEC50
EnumIdentityTree000EEC50::iterator BfmeRbTreeInsertAnchor000EEC50( EnumIdentityTree000EEC50 *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const Rva000EEC50Key &value, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, value, w );
}

struct Rva00076190Target;

typedef Rva00076190Target *PointerKey00076190;

typedef _STL::_Rb_tree<PointerKey00076190, PointerKey00076190, _STL::_Identity<PointerKey00076190>,
	_STL::less<PointerKey00076190>, _STL::allocator<PointerKey00076190> > PointerIdentityTree00076190;

// retail 0x00072C90, called by the insert_unique at 0x00076190
PointerIdentityTree00076190::iterator BfmeRbTreeInsertAnchor00076190( PointerIdentityTree00076190 *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const PointerKey00076190 &value, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, value, w );
}

struct Rva0013FA60Target;

typedef Rva0013FA60Target *PointerKey0013FA60;

typedef _STL::_Rb_tree<PointerKey0013FA60, PointerKey0013FA60, _STL::_Identity<PointerKey0013FA60>,
	_STL::less<PointerKey0013FA60>, _STL::allocator<PointerKey0013FA60> > PointerIdentityTree0013FA60;

// retail 0x0013F760, called by the insert_unique at 0x0013FA60
PointerIdentityTree0013FA60::iterator BfmeRbTreeInsertAnchor0013FA60( PointerIdentityTree0013FA60 *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const PointerKey0013FA60 &value, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, value, w );
}

struct Rva0025BD30Target;

typedef Rva0025BD30Target *PointerKey0025BD30;

typedef _STL::_Rb_tree<PointerKey0025BD30, PointerKey0025BD30, _STL::_Identity<PointerKey0025BD30>,
	_STL::less<PointerKey0025BD30>, _STL::allocator<PointerKey0025BD30> > PointerIdentityTree0025BD30;

// retail 0x0025BAB0, called by the insert_unique at 0x0025BD30
PointerIdentityTree0025BD30::iterator BfmeRbTreeInsertAnchor0025BD30( PointerIdentityTree0025BD30 *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const PointerKey0025BD30 &value, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, value, w );
}

struct Rva00296ED0Target;

typedef Rva00296ED0Target *PointerKey00296ED0;

typedef _STL::_Rb_tree<PointerKey00296ED0, PointerKey00296ED0, _STL::_Identity<PointerKey00296ED0>,
	_STL::less<PointerKey00296ED0>, _STL::allocator<PointerKey00296ED0> > PointerIdentityTree00296ED0;

// retail 0x00296B90, called by the insert_unique at 0x00296ED0
PointerIdentityTree00296ED0::iterator BfmeRbTreeInsertAnchor00296ED0( PointerIdentityTree00296ED0 *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const PointerKey00296ED0 &value, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, value, w );
}

struct Rva0036ED40Target;

typedef Rva0036ED40Target *PointerKey0036ED40;

typedef _STL::_Rb_tree<PointerKey0036ED40, PointerKey0036ED40, _STL::_Identity<PointerKey0036ED40>,
	_STL::less<PointerKey0036ED40>, _STL::allocator<PointerKey0036ED40> > PointerIdentityTree0036ED40;

// retail 0x0036E1E0, called by the insert_unique at 0x0036ED40
PointerIdentityTree0036ED40::iterator BfmeRbTreeInsertAnchor0036ED40( PointerIdentityTree0036ED40 *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const PointerKey0036ED40 &value, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, value, w );
}

struct Rva00442AB0Target;

typedef Rva00442AB0Target *PointerKey00442AB0;

typedef _STL::_Rb_tree<PointerKey00442AB0, PointerKey00442AB0, _STL::_Identity<PointerKey00442AB0>,
	_STL::less<PointerKey00442AB0>, _STL::allocator<PointerKey00442AB0> > PointerIdentityTree00442AB0;

// retail 0x004408A0, called by the insert_unique at 0x00442AB0
PointerIdentityTree00442AB0::iterator BfmeRbTreeInsertAnchor00442AB0( PointerIdentityTree00442AB0 *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const PointerKey00442AB0 &value, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, value, w );
}

struct Rva006DE9B0Target;

typedef Rva006DE9B0Target *PointerKey006DE9B0;

typedef _STL::_Rb_tree<PointerKey006DE9B0, PointerKey006DE9B0, _STL::_Identity<PointerKey006DE9B0>,
	_STL::less<PointerKey006DE9B0>, _STL::allocator<PointerKey006DE9B0> > PointerIdentityTree006DE9B0;

// retail 0x006DBFF0, called by the insert_unique at 0x006DE9B0
PointerIdentityTree006DE9B0::iterator BfmeRbTreeInsertAnchor006DE9B0( PointerIdentityTree006DE9B0 *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const PointerKey006DE9B0 &value, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, value, w );
}


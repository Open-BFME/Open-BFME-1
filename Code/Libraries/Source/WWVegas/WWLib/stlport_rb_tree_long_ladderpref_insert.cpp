// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::_Rb_tree<Long, pair<const Long, LadderPref> >::_M_insert,
// retail 0x000AAD50, 176 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// This is STLport's four-argument _M_insert, the one whose __w_ and __x_
// arguments let a caller that has already done the comparison skip it. Both
// short-circuits are visible: __w_ non-null jumps straight to the right-hand
// arm, __x_ non-null straight to the left-hand one, and only when both are
// null does the body actually compare the value against the parent's key.
//
// The node is 0x24 bytes: colour, parent, left and right, then the 20-byte
// pair, so LadderPref itself is 16. _Select1st makes the key the pair's first, which sits at the front of
// the value and so at node+0x10.
//
// Unlike the _Identity sibling at 0x002348E0 this instantiation does not inline
// the value construction: _Construct is a call here, so it is declared and left
// undefined rather than written as placement new.

typedef int Int;

struct BfmeRbTreeInsertAnchorHelper;

typedef long Long;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LadderPreferences.h
class LadderPref
{
	char m_bfmeBody[16];
};


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
void _Construct(T1 *p, const T2 &value);			// ILT 0x0002367D

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
	typedef _STL::pair<const Long, LadderPref> Value;
	typedef _STL::_Rb_tree<Long, Value, _STL::_Select1st<Value>,
		_STL::less<Long>, _STL::allocator<Value> > Tree;

	static Tree::iterator run(Tree *tree, _STL::_Rb_tree_node_base *x,
		_STL::_Rb_tree_node_base *y, const Value &v, _STL::_Rb_tree_node_base *w)
	{
		return tree->_M_insert(x, y, v, w);
	}
};

// run() is defined in-class and therefore inline, so it is only emitted if
// something calls it; this is what reaches the template.
BfmeRbTreeInsertAnchorHelper::Tree::iterator BfmeRbTreeInsertAnchor(
	BfmeRbTreeInsertAnchorHelper::Tree *tree, _STL::_Rb_tree_node_base *x,
	_STL::_Rb_tree_node_base *y, const BfmeRbTreeInsertAnchorHelper::Value &v,
	_STL::_Rb_tree_node_base *w)
{
	return BfmeRbTreeInsertAnchorHelper::run(tree, x, y, v, w);
}

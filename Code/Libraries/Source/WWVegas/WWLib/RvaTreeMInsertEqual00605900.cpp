// cl: /DNDEBUG /MD /EHsc

// Open-BFME: STLport _Rb_tree equal-insert body at 0x00605900.
// The value constructor at 0x00605630 makes the value field 0x60 bytes, so
// the node allocation is 0x70.  Unlike the unique-insert siblings, this
// equal-insert form has no key comparison: the caller supplies the side via
// the x/w arguments.

struct BfmeRbTreeInsertEqual00605900Anchor;

namespace _STL
{

void *__cdecl nodeAllocate(unsigned int bytes);

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
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class V>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	V _M_value_field;
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
		_Rb_tree_node_base *&root);
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class T, class Alloc>
struct _Rb_tree_base
{
	typedef _Rb_tree_node<T> _Node;

	_STLP_alloc_proxy<_Node *, _Node, allocator<_Node> > _M_header;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree : public _Rb_tree_base<Value, Alloc>
{
public:
	typedef unsigned int size_type;
	typedef _Rb_tree_node<Value> _Node;
	typedef _Node *_Link_type;
	typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;

	static _Link_type &_S_left(_Link_type node)
	{
		return (_Link_type &)node->_M_left;
	}

	static _Link_type &_S_right(_Link_type node)
	{
		return (_Link_type &)node->_M_right;
	}

	static _Link_type &_S_parent(_Link_type node)
	{
		return (_Link_type &)node->_M_parent;
	}

	static _Link_type &_S_left(_Rb_tree_node_base *node)
	{
		return (_Link_type &)node->_M_left;
	}

	static _Link_type &_S_right(_Rb_tree_node_base *node)
	{
		return (_Link_type &)node->_M_right;
	}

	static _Link_type &_S_parent(_Rb_tree_node_base *node)
	{
		return (_Link_type &)node->_M_parent;
	}

private:
	iterator _M_insert(_Rb_tree_node_base *x_, _Rb_tree_node_base *y_,
		const Value &v, _Rb_tree_node_base *w_);

	_Link_type _M_create_node(const Value &v)
	{
		_Link_type tmp = (_Link_type)nodeAllocate(sizeof(_Node));
		_Construct(&tmp->_M_value_field, v);
		return tmp;
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

	static const Key &_S_key(_Rb_tree_node_base *node)
	{
		return KeyOfValue()(((_Link_type)node)->_M_value_field);
	}

	size_type _M_node_count;
	Compare _M_key_compare;

	friend struct ::BfmeRbTreeInsertEqual00605900Anchor;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_insert(
	_Rb_tree_node_base *x_, _Rb_tree_node_base *y_, const Value &v,
	_Rb_tree_node_base *w_)
{
	_Link_type z;
	_Link_type y = (_Link_type)y_;

	if (y == this->_M_header._M_data
		|| (w_ == 0 && (x_ != 0
			|| _M_key_compare(KeyOfValue()(v), _S_key(y)))))
	{
		z = _M_create_node(v);
		_S_left(y) = z;
		if (y == this->_M_header._M_data)
		{
			_M_root() = z;
			_M_rightmost() = z;
		}
		else if (y == _M_leftmost())
			_M_leftmost() = z;
	}
	else
	{
		z = _M_create_node(v);
		_S_right(y) = z;
		if (y == _M_rightmost())
			_M_rightmost() = z;
	}

	_S_parent(z) = y;
	_S_left(z) = 0;
	_S_right(z) = 0;
	_Rb_global<bool>::_Rebalance(z, this->_M_header._M_data->_M_parent);
	++_M_node_count;
	return iterator(z);
}

}

template <class T>
class StringBase
{
public:
	StringBase(const StringBase &other);
	int compareNoCase(const StringBase<T> &other) const;

protected:
	void *m_data;
};

struct Gen_t_00605630_p12cd
{
	unsigned char m_body[0x54];
};

struct U4Item00605320
{
	U4Item00605320(const U4Item00605320 &other);

	StringBase<char> m_name;
	int m_f04;
	float m_f08;
};

bool __stdcall u4Less00605320(const U4Item00605320 &a,
	const U4Item00605320 &b);

namespace _STL
{

template <>
struct less<U4Item00605320>
{
	bool operator()(const U4Item00605320 &a,
		const U4Item00605320 &b) const;
};

}

typedef _STL::pair<const U4Item00605320, Gen_t_00605630_p12cd>
	Gen_t_00605630Value;

typedef _STL::_Rb_tree<U4Item00605320, Gen_t_00605630Value,
	_STL::_Select1st<Gen_t_00605630Value>, _STL::less<U4Item00605320>,
	_STL::allocator<Gen_t_00605630Value> > Gen_t_00605630Tree;

struct BfmeRbTreeInsertEqual00605900Anchor
{
	static Gen_t_00605630Tree::iterator run(Gen_t_00605630Tree *tree,
		_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
		const Gen_t_00605630Value &value, _STL::_Rb_tree_node_base *w)
	{
		return tree->_M_insert(x, y, value, w);
	}
};

Gen_t_00605630Tree::iterator BfmeRbTreeInsertEqual00605900(
	Gen_t_00605630Tree *tree, _STL::_Rb_tree_node_base *x,
	_STL::_Rb_tree_node_base *y, const Gen_t_00605630Value &value,
	_STL::_Rb_tree_node_base *w)
{
	return BfmeRbTreeInsertEqual00605900Anchor::run(tree, x, y, value, w);
}

// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: STLport _Rb_tree<U4Item00605320,...>::insert_equal at
// 0x00605F00.  This shares the tree with the already-landed pieces:
// u4Less00605320 (0x00605320, Code/GameEngine/Source/Common/
// U4CompareAndTailPoke.cpp -- StringBase<char>::compareNoCase then a float
// tie-break) and the equal-insert leaf _M_insert (0x00605900, Code/
// Libraries/Source/WWVegas/WWLib/RvaTreeMInsertEqual00605900.cpp, whose
// comment records the 0x60-byte value / 0x70-byte node).  Retail inlines the
// comparator here (u4Less00605320's own TU keeps it an out-of-line call), so
// the StringBase<char>::compareNoCase body is duplicated inline exactly as
// RvaTreeBoundsAsciiStringNoCase.cpp already proved it for the sibling
// 0x00605550 lower_bound: length/data pulled from the ref-counted header
// (0 when the pointer is null, falling back to the shared empty-string
// literal), one _memicmp call, then a length-difference fallback -- and only
// when that combined result is exactly zero does the float member at +8
// decide the order (fld/fcomp/fnstsw ax/test ah,5, matching u4Less00605320's
// own tie-break shape byte for byte).

#define _STLP_NO_EXCEPTIONS 1

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

extern const char g_bfmeEmptyAscii[];

template <class T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &other) const
	{
		const int len = other.m_data ? other.m_data->length : 0;
		const T *data = other.m_data ? &other.m_data->data[0] : (const T *)g_bfmeEmptyAscii;
		const int myLen = m_data ? m_data->length : 0;
		const T *myData = m_data ? &m_data->data[0] : (const T *)g_bfmeEmptyAscii;
		int result = _memicmp(myData, data, myLen < len ? myLen : len);
		if (result == 0) {
			result = myLen - len;
		}
		return result;
	}

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

struct U4Item00605320
{
	StringBase<char> m_name;
	int m_f04;
	float m_f08;
};

bool u4Item00605320Less(const U4Item00605320 &a, const U4Item00605320 &b)
{
	int order = a.m_name.compareNoCase(b.m_name);
	if (order < 0)
		return true;
	if (order > 0)
		return false;
	return a.m_f08 < b.m_f08;
}

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
struct less;

template <>
struct less<U4Item00605320>
{
	bool operator()(const U4Item00605320 &a, const U4Item00605320 &b) const
	{
		return u4Item00605320Less(a, b);
	}
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

	// The only known caller passes v by reference and gets the returned
	// iterator through the hidden-return-value slot; the search loop
	// inlines the same three-way comparator u4Less00605320 wraps.
	iterator insert_equal(const Value &v)
	{
		_Link_type y = this->_M_header._M_data;
		_Link_type x = (_Link_type)_M_root();

		while (x != 0)
		{
			y = x;
			x = _M_key_compare(KeyOfValue()(v), _S_key(x)) ? _S_left(x) : _S_right(x);
		}

		return _M_insert(x, y, v, 0);
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

	_Rb_tree_node_base *&_M_root(void)
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

struct Gen_t_00605630_p12cd
{
	unsigned char m_body[0x54];
};

typedef _STL::pair<const U4Item00605320, Gen_t_00605630_p12cd>
	Gen_t_00605630Value;

typedef _STL::_Rb_tree<U4Item00605320, Gen_t_00605630Value,
	_STL::_Select1st<Gen_t_00605630Value>, _STL::less<U4Item00605320>,
	_STL::allocator<Gen_t_00605630Value> > Gen_t_00605630Tree;

Gen_t_00605630Tree::iterator Rva00605F00InsertEqual(Gen_t_00605630Tree *tree,
	const Gen_t_00605630Value &v)
{
	return tree->insert_equal(v);
}

// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: two STLport _Rb_tree<K, V>::_M_insert bodies of 176 bytes whose
// tree is not a model but the real one.  Both carried only a machine byte-dump
// row, and in both cases a converted caller names the instantiation outright.
//
// 0x00765220 is reached by W3DModelDraw's PristineBoneInfoMap insert at
// 0x00765300, a map<NameKeyType, PristineBoneInfo>.  The node it allocates is
// 72 bytes, and PristineBoneInfo is a Matrix3D and an Int -- 52 bytes -- next
// to a four-byte NameKeyType, which is a pair of 56 and a node of 72.  The size
// is the check, and it passes.  A second caller at 0x00768710 also reaches this
// body carrying the name of a map<NameKeyType, VeterancyLevel>; that tree's
// node would be 24, not 72, so what it shares with this one is identical-code
// folding of the caller, not the instantiation.
//
// 0x003DBDC0 is reached by the insert_equal at 0x003E2580 in
// Code/gen_small/tgrid_114.cpp, a map<Int, Gen_t_003e2580_p12cd>.  Its node is
// 24, which is a four-byte key beside a four-byte mapped type, and that is what
// the generator's type is.
//
// NameKeyType is an enumeration, so both comparisons are signed, and both
// bodies duly compare with `jl`.

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

struct Matrix3D
{
	float m_row[ 3 ][ 4 ];
};

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct PristineBoneInfo
{
	Matrix3D mtx;
	Int boneIndex;
};

typedef _STL::pair<const NameKeyType, PristineBoneInfo> PristineBonePair;

typedef _STL::_Rb_tree<NameKeyType, PristineBonePair,
	_STL::_Select1st<PristineBonePair>, _STL::less<NameKeyType>,
	_STL::allocator<PristineBonePair> > PristineBoneTree;

// retail 0x00765220
PristineBoneTree::iterator BfmeRbTreeInsertAnchor00765220( PristineBoneTree *tree,
	_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *y,
	const PristineBonePair &v, _STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

struct Gen_t_003e2580_p12cd
{
	int m_body;
};

typedef _STL::pair<const Int, Gen_t_003e2580_p12cd> Gen_t_003e2580_p12cdPair;

typedef _STL::_Rb_tree<Int, Gen_t_003e2580_p12cdPair,
	_STL::_Select1st<Gen_t_003e2580_p12cdPair>, _STL::less<Int>,
	_STL::allocator<Gen_t_003e2580_p12cdPair> > Gen_t_003e2580_p12cdTree;

// retail 0x003DBDC0
Gen_t_003e2580_p12cdTree::iterator BfmeRbTreeInsertAnchor003DBDC0(
	Gen_t_003e2580_p12cdTree *tree, _STL::_Rb_tree_node_base *x,
	_STL::_Rb_tree_node_base *y, const Gen_t_003e2580_p12cdPair &v,
	_STL::_Rb_tree_node_base *w )
{
	return BfmeRbTreeInsertAnchorHelper::run( tree, x, y, v, w );
}

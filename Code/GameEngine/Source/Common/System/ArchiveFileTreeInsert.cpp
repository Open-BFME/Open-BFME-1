// cl: /DNDEBUG /MD /EHsc

// Complete ArchiveFile pointer-tree insertion at retail RVA 0x00063140.
// ArchiveFileSystem callers establish the mapped type; node layout and
// all six callee routes are independently verified.

template <class T>
class StringBase
{
protected:
	void *m_data;
};

// The four-byte thin AsciiString layout and member compare route are the same
// view used by the already matched RvaTreeMInsertStringKey.cpp family.
class AsciiString : public StringBase<char>
{
public:
	int compare( const AsciiString &other ) const;
};

// ArchiveFile is only stored as a pointer in the pair.  The actual owner and
// mapped width are proved by ArchiveFileSystem::openFile callers of RVA
// 0x00063960; no incomplete-class method is needed here.
class ArchiveFile;

namespace _STL
{

void *__cdecl vectorLargeAllocate( unsigned int bytes );
void *__cdecl vectorSmallAllocate( unsigned int bytes ); // retail 0x0082E540

inline void *BfmeNodeAllocate( unsigned int bytes )
{
	if (bytes > 128)
		return vectorLargeAllocate( bytes );
	return vectorSmallAllocate( bytes );
}

template <class T1, class T2>
void _Construct( T1 *p, const T2 &value ); // retail route 0x00005E4D -> 0x00062900

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
	const typename T::first_type &operator()( const T &x ) const
	{
		return x.first;
	}
};

template <class T>
struct less
{
	bool operator()( const T &a, const T &b ) const
	{
		return a < b;
	}
};

template <>
struct less<AsciiString>
{
	bool operator()( const AsciiString &a, const AsciiString &b ) const
	{
		return a.compare( b ) < 0;
	}
};

template <class T>
struct _Nonconst_traits {};

template <class T>
class allocator {};

struct _Rb_tree_node_base
{
	bool _M_color;                        // +0x00; three-byte implicit padding precedes +0x04
	_Rb_tree_node_base *_M_parent;        // +0x04
	_Rb_tree_node_base *_M_left;          // +0x08
	_Rb_tree_node_base *_M_right;         // +0x0C
};

template <class V>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	V _M_value_field;                     // +0x10
};

template <class V, class Traits>
struct _Rb_tree_iterator
{
	_Rb_tree_iterator( _Rb_tree_node_base *node ) : _M_node( node ) {}

	_Rb_tree_node_base *_M_node;
};

template <class Threads>
struct _Rb_global
{
	static void __cdecl _Rebalance( _Rb_tree_node_base *x,
		_Rb_tree_node_base *&root );        // retail 0x0082C9D0
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;                       // +0x00
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

private:
	iterator _M_insert( _Rb_tree_node_base *x_, _Rb_tree_node_base *y_,
		const Value &v, _Rb_tree_node_base *w_ );

	_Link_type _M_create_node( const Value &v )
	{
		_Link_type tmp = (_Link_type)BfmeNodeAllocate( sizeof( _Node ) );
		_Construct( &tmp->_M_value_field, v );
		return tmp;
	}

	static const Key &_S_key( _Rb_tree_node_base *node )
	{
		return KeyOfValue()( ((_Link_type)node)->_M_value_field );
	}

	_Rb_tree_node_base *&_M_root( void ) const
	{
		return this->_M_header._M_data->_M_parent;
	}

	_Rb_tree_node_base *&_M_leftmost( void ) const
	{
		return this->_M_header._M_data->_M_left;
	}

	_Rb_tree_node_base *&_M_rightmost( void ) const
	{
		return this->_M_header._M_data->_M_right;
	}

	size_type _M_node_count;               // +0x04
	Compare _M_key_compare;                // +0x08

};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_insert(
	_Rb_tree_node_base *x_, _Rb_tree_node_base *y_, const Value &v,
	_Rb_tree_node_base *w_ )
{
	_Link_type w = (_Link_type)w_;
	_Link_type x = (_Link_type)x_;
	_Link_type y = (_Link_type)y_;
	_Link_type z;

	if (y == this->_M_header._M_data
		|| (w == 0 && (x != 0 || _M_key_compare( KeyOfValue()( v ), _S_key( y ) ))))
	{
		z = _M_create_node( v );
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
		z = _M_create_node( v );
		y->_M_right = z;
		if (y == _M_rightmost())
			_M_rightmost() = z;
	}

	z->_M_parent = y;
	z->_M_left = 0;
	z->_M_right = 0;
	_Rb_global<bool>::_Rebalance( z, this->_M_header._M_data->_M_parent );
	++_M_node_count;
	return iterator( z );
}

}

typedef _STL::pair<const AsciiString, ArchiveFile *> Rva00063140Pair;
typedef _STL::_Rb_tree<AsciiString, Rva00063140Pair,
	_STL::_Select1st<Rva00063140Pair>, _STL::less<AsciiString>,
	_STL::allocator<Rva00063140Pair> > Rva00063140Tree;

// Explicit member instantiation is the only emission request.  It preserves
// the actual private _M_insert symbol and does not add an artificial caller or
// wrapper body.
template Rva00063140Tree::iterator Rva00063140Tree::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva00063140Pair &, _STL::_Rb_tree_node_base * );

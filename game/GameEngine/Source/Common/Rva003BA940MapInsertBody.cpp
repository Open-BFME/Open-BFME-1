// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport map::insert(iterator, const value_type &), retail 0x003BA940,
// 31 bytes. The body carried only a machine byte-dump row and no name.
//
// This is the hinted insert: it returns an iterator by value, so the caller
// hands it a hidden return pointer and the frame cleans twelve bytes. All the
// body does is copy the hint into an outgoing by-value slot and forward
// everything, this included, to the tree's insert_unique through the link thunk
// at 0x000144F2 -- the tree is the map's first member, so `this` needs no
// adjustment and the call is a plain forward.
//
// The key and mapped types are not recoverable: nothing in these 31 bytes
// depends on either, and the callee is an unnamed dump of its own. So both are
// named for the address of the body and left opaque.

struct Rva003BA940Key
{
	unsigned char m_data[4];
};

struct Rva003BA940Value
{
	unsigned char m_data[4];
};

namespace _STL
{
template <class First, class Second>
struct pair
{
	First first;
	Second second;
};

template <class Value>
struct _Nonconst_traits
{
};

template <class Value, class Traits>
struct _Rb_tree_iterator
{
	_Rb_tree_iterator( const _Rb_tree_iterator &that )
		: m_node( that.m_node )
	{
	}

	void *m_node;
};

template <class Type>
struct _Select1st
{
};

template <class Type>
struct less
{
};

template <class Type>
class allocator
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;

	iterator insert_unique( iterator position, const Value &value );
};

template <class Key, class Value, class Compare, class Alloc>
class map
{
public:
	typedef pair<const Key, Value> value_type;
	typedef _Rb_tree_iterator<value_type, _Nonconst_traits<value_type> > iterator;

	iterator insert( iterator position, const value_type &value )
	{
		return m_tree.insert_unique( position, value );
	}

private:
	_Rb_tree<Key, value_type, _Select1st<value_type>, Compare, Alloc> m_tree;
};

typedef pair<const Rva003BA940Key, Rva003BA940Value> Rva003BA940Entry;

template class map<Rva003BA940Key, Rva003BA940Value, less<Rva003BA940Key>, allocator<Rva003BA940Entry> >;
}

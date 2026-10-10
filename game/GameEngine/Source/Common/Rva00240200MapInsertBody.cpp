// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Native hinted insert: ECX tree; output iterator, by-value hint, value ref; RET12.
extern "C" void __identifier("?insert_unique@?$_Rb_tree@HU?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@U?$_Select1st@U?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHUGen_t_0023de30_p12cd@@@2@@Z")();

// Open-BFME5: STLport map::insert(iterator, const value_type &), retail 0x00240200,
// 31 bytes. The body carried only a machine byte-dump row and no name.
//
// This is the hinted insert: it returns an iterator by value, so the caller
// hands it a hidden return pointer and the frame cleans twelve bytes. All the
// body does is copy the hint into an outgoing by-value slot and forward
// everything, this included, to the tree's insert_unique through the link thunk
// at 0x0003A260 -- the tree is the map's first member, so `this` needs no
// adjustment and the call is a plain forward.
//
// The key and mapped types are not recoverable: nothing in these 31 bytes
// depends on either, and the callee is an unnamed dump of its own. So both are
// named for the address of the body and left opaque.

struct Rva00240200Key
{
	unsigned char m_data[4];
};

struct Rva00240200Value
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
	// Source-only construction directly in the caller return storage.
	template <class Tree>
	__forceinline _Rb_tree_iterator(Tree *, const _Rb_tree_iterator &, const Value &);

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

};

template <class Value, class Traits>
template <class Tree>
__forceinline _Rb_tree_iterator<Value, Traits>::_Rb_tree_iterator(
	Tree *tree, const _Rb_tree_iterator &position, const Value &value)
{
	union
	{
		void (*address)();
		void (Tree::*member)(_Rb_tree_iterator *, _Rb_tree_iterator, const Value &);
	} route = { __identifier("?insert_unique@?$_Rb_tree@HU?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@U?$_Select1st@U?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUGen_t_0023de30_p12cd@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHUGen_t_0023de30_p12cd@@@2@@Z") };
	(tree->*route.member)(this, position, value);
}

template <class Key, class Value, class Compare, class Alloc>
class map
{
public:
	typedef pair<const Key, Value> value_type;
	typedef _Rb_tree_iterator<value_type, _Nonconst_traits<value_type> > iterator;

	iterator insert( iterator position, const value_type &value )
	{
		return iterator(&m_tree, position, value);
	}

private:
	_Rb_tree<Key, value_type, _Select1st<value_type>, Compare, Alloc> m_tree;
};

typedef pair<const Rva00240200Key, Rva00240200Value> Rva00240200Entry;

template class map<Rva00240200Key, Rva00240200Value, less<Rva00240200Key>, allocator<Rva00240200Entry> >;
}

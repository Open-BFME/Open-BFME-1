// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Clean reconstruction of TeamsInfoRec::clear at retail 0x001991F0.

struct Gen_t_00195a00_p8cd
{
	int m_value;
};

class TeamsInfoRec;

namespace _STL
{

struct RbTreeNodeBase
{
	unsigned char m_color;
	unsigned char m_padding[3];
	void *m_parent;
	void *m_left;
	void *m_right;
};

template <class First, class Second>
struct pair
{
};

template <class Value>
struct _Rb_tree_node
{
	unsigned char m_color;
	unsigned char m_padding[3];
	void *m_parent;
	void *m_left;
	void *m_right;
};

template <class Value>
struct _Select1st
{
};

template <class Key>
struct less
{
};

template <class Value>
class allocator
{
};

template <class Key, class Value, class Select, class Compare, class Alloc>
class _Rb_tree
{
	friend class ::TeamsInfoRec;

	private:
	void _M_erase( _Rb_tree_node<Value> *root ) throw();

	public:
	_Rb_tree_node<Value> *m_header;
	unsigned int m_nodeCount;
	int m_compare;
};

template <class Type>
inline void swap( Type &left, Type &right )
{
	Type value = left;
	left = right;
	right = value;
}

template <class Type>
class vector
{
public:
	void swap( vector<Type> &other )
	{
		_STL::swap( other.m_begin, m_begin );
		_STL::swap( other.m_end, m_end );
		_STL::swap( other.m_capacity, m_capacity );
	}

	Type *m_begin;
	Type *m_end;
	Type *m_capacity;
};

}

// Retail calls leave this TU through the incremental-link thunks at ILT
// 0x18129 (construct) and 0x2d6a5 (destructor); name them directly.
extern void j_00018129();
extern void j_0002d6a5();

class Rva0019A1D0Member : public _STL::vector<void *>
{
public:
	Rva0019A1D0Member *construct( int count ) throw();
};

class Rva0019A1D0Tree : public _STL::_Rb_tree<
	int,
	_STL::pair<const int, Gen_t_00195a00_p8cd>,
	_STL::_Select1st<_STL::pair<const int, Gen_t_00195a00_p8cd> >,
	_STL::less<int>,
	_STL::allocator<_STL::pair<const int, Gen_t_00195a00_p8cd> > >
{
};

class TeamsInfoRec
{
public:
	void clear();

private:
	Rva0019A1D0Tree m_tree;
	Rva0019A1D0Member m_member;
	short m_a;
	short m_b;
};

void TeamsInfoRec::clear()
{
	{
		typedef Rva0019A1D0Member *(Rva0019A1D0Member::*FnConstruct)( int );
		union { void (*fn)(); FnConstruct call; } construct_thunk = { j_00018129 };
		typedef void (Rva0019A1D0Member::*FnDestruct)();
		union { void (*fn)(); FnDestruct call; } destruct_thunk = { j_0002d6a5 };
		Rva0019A1D0Member storage;
		Rva0019A1D0Member *member = (storage.*construct_thunk.call)( 1 );
		m_member.swap( *member );
		(storage.*destruct_thunk.call)();
	}

	if ( m_tree.m_nodeCount != 0 )
	{
		m_tree._M_erase( (_STL::_Rb_tree_node<
			_STL::pair<const int, Gen_t_00195a00_p8cd> > *)m_tree.m_header->m_parent );
		m_tree.m_header->m_left = m_tree.m_header;
		m_tree.m_header->m_parent = 0;
		m_tree.m_header->m_right = m_tree.m_header;
		m_tree.m_nodeCount = 0;
	}

	m_a = 0;
	m_b = 0;
}

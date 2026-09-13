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

class Rva0019A1D0Member : public _STL::vector<void *>
{
public:
	Rva0019A1D0Member *construct( int count ) throw();
	~Rva0019A1D0Member() throw();
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

#pragma comment(linker, "/alternatename:?construct@Rva0019A1D0Member@@QAEPAV1@H@Z=?j_00018129@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva0019A1D0Member@@QAE@XZ=?j_0002d6a5@@YAXXZ")

void TeamsInfoRec::clear()
{
	{
		Rva0019A1D0Member storage;
		Rva0019A1D0Member *member = storage.construct( 1 );
		m_member.swap( *member );
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

// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport list<T>::insert(iterator, const T &) and
// list<T>::push_back(const T &) over an eight-byte element -- 13 and 10 bodies,
// 54 and 48 bytes.  All of them carried only a machine byte-dump row.
//
// The list is the usual intrusive ring: a node is two pointers and then the
// value at +8, and the header node the list holds at offset 0 is both the end
// iterator and the anchor.  insert allocates, copies the value in, and splices
// the node in front of the position it was handed; push_back is that same
// insert with the header as the position, which the compiler inlines whole --
// the only difference in the bytes is where the position comes from.
//
// Sixteen bytes of node is eight of links and eight of value.  The value is
// copied by a CALL to _Construct rather than by two moves, which is what a
// non-trivial copy constructor forces, so the element is eight bytes wide and
// not trivially copyable -- and that is all these bodies say about it.  Each is
// named for the address of the body, with its _Construct pinned beside it.

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
void __cdecl _Construct(T1 *destination, const T2 &value);

template <class T>
class allocator
{
};

template <class T>
struct _Nonconst_traits
{
};

struct _List_node_base
{
	_List_node_base *_M_next;				// +0x00
	_List_node_base *_M_prev;				// +0x04
};

template <class T>
struct _List_node : public _List_node_base
{
	T _M_data;						// +0x08
};

template <class T, class Traits>
struct _List_iterator
{
	_List_iterator(_List_node_base *node) : _M_node(node) {}

	_List_node_base *_M_node;
};

template <class T, class Alloc>
class _List_base
{
public:
	typedef _List_node<T> _Node;

	_Node *_M_node;						// +0x00
};

template <class T, class Alloc>
class list : public _List_base<T, Alloc>
{
public:
	typedef _List_node<T> _Node;
	typedef _List_iterator<T, _Nonconst_traits<T> > iterator;

	iterator insert( iterator position, const T &value )
	{
		_Node *node = _M_create_node( value );
		_List_node_base *at = position._M_node;
		_List_node_base *before = at->_M_prev;
		node->_M_next = at;
		node->_M_prev = before;
		before->_M_next = node;
		at->_M_prev = node;
		return iterator( node );
	}

	void push_back( const T &value )
	{
		insert( iterator( this->_M_node ), value );
	}

	void push_front( const T &value )
	{
		insert( iterator( this->_M_node->_M_next ), value );
	}

private:
	_Node *_M_create_node( const T &value )
	{
		_Node *node = (_Node *)BfmeNodeAllocate( sizeof( _Node ) );
		_Construct( &node->_M_data, value );
		return node;
	}
};

}

struct Rva0010FF90Element
{
	char m_body[ 8 ];
};

// retail 0x0010FF90
template class _STL::list<Rva0010FF90Element, _STL::allocator<Rva0010FF90Element> >;

struct Rva00148B80Element
{
	char m_body[ 8 ];
};

// retail 0x00148B80
template class _STL::list<Rva00148B80Element, _STL::allocator<Rva00148B80Element> >;

struct Rva0014C4C0Element
{
	char m_body[ 8 ];
};

// retail 0x0014C4C0
template class _STL::list<Rva0014C4C0Element, _STL::allocator<Rva0014C4C0Element> >;

struct Rva001CB1F0Element
{
	char m_body[ 8 ];
};

// retail 0x001CB1F0
template class _STL::list<Rva001CB1F0Element, _STL::allocator<Rva001CB1F0Element> >;

struct Rva0021B530Element
{
	char m_body[ 8 ];
};

// retail 0x0021B530
template class _STL::list<Rva0021B530Element, _STL::allocator<Rva0021B530Element> >;

struct Rva0022D610Element
{
	char m_body[ 8 ];
};

// retail 0x0022D610
template class _STL::list<Rva0022D610Element, _STL::allocator<Rva0022D610Element> >;

struct Rva0033F410Element
{
	char m_body[ 8 ];
};

// retail 0x0033F410
template class _STL::list<Rva0033F410Element, _STL::allocator<Rva0033F410Element> >;

struct Rva003406C0Element
{
	char m_body[ 8 ];
};

// retail 0x003406C0
template class _STL::list<Rva003406C0Element, _STL::allocator<Rva003406C0Element> >;

struct Rva00379B80Element
{
	char m_body[ 8 ];
};

// retail 0x00379B80
template class _STL::list<Rva00379B80Element, _STL::allocator<Rva00379B80Element> >;

struct Rva0038BA50Element
{
	char m_body[ 8 ];
};

// retail 0x0038BA50
template class _STL::list<Rva0038BA50Element, _STL::allocator<Rva0038BA50Element> >;

struct Rva00430E90Element
{
	char m_body[ 8 ];
};

// retail 0x00430E90
template class _STL::list<Rva00430E90Element, _STL::allocator<Rva00430E90Element> >;

struct Rva00439D50Element
{
	char m_body[ 8 ];
};

// retail 0x00439D50
template class _STL::list<Rva00439D50Element, _STL::allocator<Rva00439D50Element> >;

struct Rva004489E0Element
{
	char m_body[ 8 ];
};

// retail 0x004489E0
template class _STL::list<Rva004489E0Element, _STL::allocator<Rva004489E0Element> >;

struct Rva00110D70Element
{
	char m_body[ 8 ];
};

// retail 0x00110D70
template class _STL::list<Rva00110D70Element, _STL::allocator<Rva00110D70Element> >;

struct Rva00148BD0Element
{
	char m_body[ 8 ];
};

// retail 0x00148BD0
template class _STL::list<Rva00148BD0Element, _STL::allocator<Rva00148BD0Element> >;

struct Rva001CFDB0Element
{
	char m_body[ 8 ];
};

// retail 0x001CFDB0
template class _STL::list<Rva001CFDB0Element, _STL::allocator<Rva001CFDB0Element> >;

struct Rva0021BD70Element
{
	char m_body[ 8 ];
};

// retail 0x0021BD70
template class _STL::list<Rva0021BD70Element, _STL::allocator<Rva0021BD70Element> >;

struct Rva0022DA10Element
{
	char m_body[ 8 ];
};

// retail 0x0022DA10
template class _STL::list<Rva0022DA10Element, _STL::allocator<Rva0022DA10Element> >;

struct Rva00342BB0Element
{
	char m_body[ 8 ];
};

// retail 0x00342BB0
template class _STL::list<Rva00342BB0Element, _STL::allocator<Rva00342BB0Element> >;

struct Rva00342C30Element
{
	char m_body[ 8 ];
};

// retail 0x00342C30
template class _STL::list<Rva00342C30Element, _STL::allocator<Rva00342C30Element> >;

struct Rva00379D20Element
{
	char m_body[ 8 ];
};

// retail 0x00379D20
template class _STL::list<Rva00379D20Element, _STL::allocator<Rva00379D20Element> >;

struct Rva0038EAD0Element
{
	char m_body[ 8 ];
};

// retail 0x0038EAD0
template class _STL::list<Rva0038EAD0Element, _STL::allocator<Rva0038EAD0Element> >;

struct Rva00431310Element
{
	char m_body[ 8 ];
};

// retail 0x00431310
template class _STL::list<Rva00431310Element, _STL::allocator<Rva00431310Element> >;


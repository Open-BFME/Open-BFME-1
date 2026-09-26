// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport list<T>::push_front(const T &) over a four-byte element,
// 12 bodies of 47 bytes.  All of them carried only a machine byte-dump row.
//
// push_front is insert with the header's successor as the position, inlined
// whole.  The node is twelve bytes -- two link pointers and four of value --
// and unlike the eight-byte-element siblings in RvaListInsert8.cpp the value
// copy does NOT become a call: it is one dword move, preceded by a test of the
// destination pointer against null.  Nobody wrote that test.  It is placement
// new: MSVC 7.1 checks what operator new(size_t, void *) returned before
// constructing through it, and the check survives even though the pointer is a
// lea off a just-allocated block.
//
// So the element is four bytes and trivially copyable, and nothing further.
// Each is named for the address of the body.

inline void *operator new(unsigned int, void *place) { return place; }

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
inline void __cdecl _Construct(T1 *destination, const T2 &value)
{
	new (destination) T1(value);
}

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

struct Rva00093470Element
{
	int m_body;
};

// retail 0x00093470
template class _STL::list<Rva00093470Element, _STL::allocator<Rva00093470Element> >;

struct Rva000FE130Element
{
	int m_body;
};

// retail 0x000FE130
template class _STL::list<Rva000FE130Element, _STL::allocator<Rva000FE130Element> >;

struct Rva0010EBE0Element
{
	int m_body;
};

// retail 0x0010EBE0
template class _STL::list<Rva0010EBE0Element, _STL::allocator<Rva0010EBE0Element> >;

struct Rva00202350Element
{
	int m_body;
};

// retail 0x00202350
template class _STL::list<Rva00202350Element, _STL::allocator<Rva00202350Element> >;

struct Rva00236000Element
{
	int m_body;
};

// retail 0x00236000
template class _STL::list<Rva00236000Element, _STL::allocator<Rva00236000Element> >;

struct Rva00442570Element
{
	int m_body;
};

// retail 0x00442570
template class _STL::list<Rva00442570Element, _STL::allocator<Rva00442570Element> >;

struct Rva004425E0Element
{
	int m_body;
};

// retail 0x004425E0
template class _STL::list<Rva004425E0Element, _STL::allocator<Rva004425E0Element> >;

struct Rva00442660Element
{
	int m_body;
};

// retail 0x00442660
template class _STL::list<Rva00442660Element, _STL::allocator<Rva00442660Element> >;

struct Rva00442700Element
{
	int m_body;
};

// retail 0x00442700
template class _STL::list<Rva00442700Element, _STL::allocator<Rva00442700Element> >;

struct Rva0048CA90Element
{
	int m_body;
};

// retail 0x0048CA90
template class _STL::list<Rva0048CA90Element, _STL::allocator<Rva0048CA90Element> >;

struct Rva004FFE70Element
{
	int m_body;
};

// retail 0x004FFE70
template class _STL::list<Rva004FFE70Element, _STL::allocator<Rva004FFE70Element> >;

struct Rva006F9160Element
{
	int m_body;
};

// retail 0x006F9160
template class _STL::list<Rva006F9160Element, _STL::allocator<Rva006F9160Element> >;


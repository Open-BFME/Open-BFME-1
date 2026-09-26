// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport list<T>::insert(iterator, const T &) and
// list<T>::push_back(const T &) at 10 more element widths -- 35 bodies.  Every
// one carried only a machine byte-dump row.  RvaListInsert8.cpp already holds
// the eight-byte-element half of this family; these are the same two functions
// over everything else.
//
// A node is two link pointers and then the value at +8, so the immediate pushed
// to the allocator is eight more than the element.  Those immediates run 4, 12, 16, 20, 24, 28, 36, 60, 216, 816.
// The two largest cross STLport's 128-byte threshold and so reach the large
// allocator instead of the small one, which is the three bytes that make those
// bodies 51 and 57 rather than 48 and 54.
//
// Every one of them copies its value through a call rather than inline, so no
// element here is trivially copyable -- and beyond that, and its width, the
// bodies say nothing about what the element is.  Each is named for the address
// of the body that allocates it; where an insert and a push_back share a list
// in retail, this file cannot tell which pair, so it does not guess and gives
// each body its own.

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


struct Rva00080220Element
{
	char m_body[ 4 ];
};

// retail 0x00080220, a 12-byte node
template class _STL::list<Rva00080220Element, _STL::allocator<Rva00080220Element> >;

struct Rva0009F200Element
{
	char m_body[ 4 ];
};

// retail 0x0009F200, a 12-byte node
template class _STL::list<Rva0009F200Element, _STL::allocator<Rva0009F200Element> >;

struct Rva0009F3A0Element
{
	char m_body[ 4 ];
};

// retail 0x0009F3A0, a 12-byte node
template class _STL::list<Rva0009F3A0Element, _STL::allocator<Rva0009F3A0Element> >;

struct Rva000BF1B0Element
{
	char m_body[ 12 ];
};

// retail 0x000BF1B0, a 20-byte node
template class _STL::list<Rva000BF1B0Element, _STL::allocator<Rva000BF1B0Element> >;

struct Rva001ACF10Element
{
	char m_body[ 4 ];
};

// retail 0x001ACF10, a 12-byte node
template class _STL::list<Rva001ACF10Element, _STL::allocator<Rva001ACF10Element> >;

struct Rva001F4BF0Element
{
	char m_body[ 12 ];
};

// retail 0x001F4BF0, a 20-byte node
template class _STL::list<Rva001F4BF0Element, _STL::allocator<Rva001F4BF0Element> >;

struct Rva001F4C70Element
{
	char m_body[ 12 ];
};

// retail 0x001F4C70, a 20-byte node
template class _STL::list<Rva001F4C70Element, _STL::allocator<Rva001F4C70Element> >;

struct Rva001F52F0Element
{
	char m_body[ 12 ];
};

// retail 0x001F52F0, a 20-byte node
template class _STL::list<Rva001F52F0Element, _STL::allocator<Rva001F52F0Element> >;

struct Rva001F5360Element
{
	char m_body[ 12 ];
};

// retail 0x001F5360, a 20-byte node
template class _STL::list<Rva001F5360Element, _STL::allocator<Rva001F5360Element> >;

struct Rva002248F0Element
{
	char m_body[ 28 ];
};

// retail 0x002248F0, a 36-byte node
template class _STL::list<Rva002248F0Element, _STL::allocator<Rva002248F0Element> >;

struct Rva00225B80Element
{
	char m_body[ 28 ];
};

// retail 0x00225B80, a 36-byte node
template class _STL::list<Rva00225B80Element, _STL::allocator<Rva00225B80Element> >;

struct Rva0033F460Element
{
	char m_body[ 16 ];
};

// retail 0x0033F460, a 24-byte node
template class _STL::list<Rva0033F460Element, _STL::allocator<Rva0033F460Element> >;

struct Rva00342BF0Element
{
	char m_body[ 16 ];
};

// retail 0x00342BF0, a 24-byte node
template class _STL::list<Rva00342BF0Element, _STL::allocator<Rva00342BF0Element> >;

struct Rva00381CC0Element
{
	char m_body[ 216 ];
};

// retail 0x00381CC0, a 224-byte node
template class _STL::list<Rva00381CC0Element, _STL::allocator<Rva00381CC0Element> >;

struct Rva00381D80Element
{
	char m_body[ 216 ];
};

// retail 0x00381D80, a 224-byte node
template class _STL::list<Rva00381D80Element, _STL::allocator<Rva00381D80Element> >;

struct Rva003BFEF0Element
{
	char m_body[ 12 ];
};

// retail 0x003BFEF0, a 20-byte node
template class _STL::list<Rva003BFEF0Element, _STL::allocator<Rva003BFEF0Element> >;

struct Rva003C07C0Element
{
	char m_body[ 12 ];
};

// retail 0x003C07C0, a 20-byte node
template class _STL::list<Rva003C07C0Element, _STL::allocator<Rva003C07C0Element> >;

struct Rva00452280Element
{
	char m_body[ 12 ];
};

// retail 0x00452280, a 20-byte node
template class _STL::list<Rva00452280Element, _STL::allocator<Rva00452280Element> >;

struct Rva004EBBC0Element
{
	char m_body[ 24 ];
};

// retail 0x004EBBC0, a 32-byte node
template class _STL::list<Rva004EBBC0Element, _STL::allocator<Rva004EBBC0Element> >;

struct Rva004ECFD0Element
{
	char m_body[ 24 ];
};

// retail 0x004ECFD0, a 32-byte node
template class _STL::list<Rva004ECFD0Element, _STL::allocator<Rva004ECFD0Element> >;

struct Rva004FD920Element
{
	char m_body[ 816 ];
};

// retail 0x004FD920, a 824-byte node
template class _STL::list<Rva004FD920Element, _STL::allocator<Rva004FD920Element> >;

struct Rva004FD970Element
{
	char m_body[ 816 ];
};

// retail 0x004FD970, a 824-byte node
template class _STL::list<Rva004FD970Element, _STL::allocator<Rva004FD970Element> >;

struct Rva0056DDC0Element
{
	char m_body[ 60 ];
};

// retail 0x0056DDC0, a 68-byte node
template class _STL::list<Rva0056DDC0Element, _STL::allocator<Rva0056DDC0Element> >;

struct Rva0056E120Element
{
	char m_body[ 60 ];
};

// retail 0x0056E120, a 68-byte node
template class _STL::list<Rva0056E120Element, _STL::allocator<Rva0056E120Element> >;

struct Rva005C5580Element
{
	char m_body[ 12 ];
};

// retail 0x005C5580, a 20-byte node
template class _STL::list<Rva005C5580Element, _STL::allocator<Rva005C5580Element> >;

struct Rva005C6B20Element
{
	char m_body[ 12 ];
};

// retail 0x005C6B20, a 20-byte node
template class _STL::list<Rva005C6B20Element, _STL::allocator<Rva005C6B20Element> >;

struct Rva006272F0Element
{
	char m_body[ 28 ];
};

// retail 0x006272F0, a 36-byte node
template class _STL::list<Rva006272F0Element, _STL::allocator<Rva006272F0Element> >;

struct Rva00627550Element
{
	char m_body[ 28 ];
};

// retail 0x00627550, a 36-byte node
template class _STL::list<Rva00627550Element, _STL::allocator<Rva00627550Element> >;

struct Rva0069DF60Element
{
	char m_body[ 4 ];
};

// retail 0x0069DF60, a 12-byte node
template class _STL::list<Rva0069DF60Element, _STL::allocator<Rva0069DF60Element> >;

struct Rva0069FC00Element
{
	char m_body[ 4 ];
};

// retail 0x0069FC00, a 12-byte node
template class _STL::list<Rva0069FC00Element, _STL::allocator<Rva0069FC00Element> >;

struct Rva00754AD0Element
{
	char m_body[ 12 ];
};

// retail 0x00754AD0, a 20-byte node
template class _STL::list<Rva00754AD0Element, _STL::allocator<Rva00754AD0Element> >;

struct Rva0076A930Element
{
	char m_body[ 36 ];
};

// retail 0x0076A930, a 44-byte node
template class _STL::list<Rva0076A930Element, _STL::allocator<Rva0076A930Element> >;

struct Rva0076AA30Element
{
	char m_body[ 20 ];
};

// retail 0x0076AA30, a 28-byte node
template class _STL::list<Rva0076AA30Element, _STL::allocator<Rva0076AA30Element> >;

struct Rva0076CEE0Element
{
	char m_body[ 36 ];
};

// retail 0x0076CEE0, a 44-byte node
template class _STL::list<Rva0076CEE0Element, _STL::allocator<Rva0076CEE0Element> >;

struct Rva0076D210Element
{
	char m_body[ 20 ];
};

// retail 0x0076D210, a 28-byte node
template class _STL::list<Rva0076D210Element, _STL::allocator<Rva0076D210Element> >;


// ?parseKeyLabelList@Rva0043A3B0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.99 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// The parser's list, string temporaries, and pair layout identify the retail
// callback at 0x0043A3B0. The list owner stores its sentinel pointer at +0x134.

#include <new>

#pragma comment(linker, "/alternatename:?releaseBuffer@UnicodeString@@AAEXXZ=?releaseBuffer@AsciiString@@AAEXXZ")

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	~AsciiString() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

class INI
{
public:
	AsciiString getNextAsciiString();
};

class UnicodeString
{
public:
	UnicodeString() : m_data( 0 ) {}
	~UnicodeString() { ((AsciiString *)this)->releaseBuffer(); }
	void set( const UnicodeString &other );

private:
	void *m_data;
};

struct Gen_t_00439370_k4
{
	UnicodeString m_value;
};

struct Gen_t_00439370_p12cd
{
	AsciiString m_value;
};

namespace _STL
{

template <class T1, class T2>
struct pair
{
public:
	pair() : first(), second() {}
	pair( const pair &other );
	T1 first;
	T2 second;
};

template <class T>
class allocator
{
};

template <class T>
struct _Nonconst_traits
{
};

template <class T, class Alloc>
class list;

template <bool threads, int instance>
class __node_alloc
{
	template <class T, class Alloc>
	friend class list;

	static void *_M_allocate( unsigned int bytes );
};

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

template <class T>
struct _List_node : public _List_node_base
{
	T _M_data;
};

template <class T, class Traits>
struct _List_iterator
{
	_List_iterator( _List_node_base *node ) : _M_node( node ) {}

	_List_node_base *_M_node;
};

template <class T, class Alloc>
class list
{
public:
	typedef _List_node<T> _Node;
	typedef _List_iterator<T, _Nonconst_traits<T> > iterator;

	_Node *_M_node;

	void push_back( const T &value )
	{
		_List_node_base *at = _M_node;
		_Node *node = (_Node *)__node_alloc<true, 0>::_M_allocate( sizeof( _Node ) );
		_Construct( &node->_M_data, value );
		_List_node_base *before = at->_M_prev;
		node->_M_next = at;
		node->_M_prev = before;
		before->_M_next = node;
		at->_M_prev = node;
	}

private:
	template <class U>
	static void _Construct( U *destination, const U &value )
	{
		new( destination ) U( value );
	}
};

}

typedef _STL::pair<const Gen_t_00439370_k4, Gen_t_00439370_p12cd> Rva0043A3B0Pair;

struct Rva0043A3B0Store
{
	unsigned char m_prefix[0x134];
	_STL::list<Rva0043A3B0Pair, _STL::allocator<Rva0043A3B0Pair> > *m_items;
};

class Rva0043A3B0
{
public:
	static void parseKeyLabelList( INI *ini, void *instance, void *, const void * );
};

void Rva0043A3B0::parseKeyLabelList( INI *ini, void *instance, void *, const void *)
{
	Rva0043A3B0Store *self = (Rva0043A3B0Store *)instance;
	AsciiString token = ini->getNextAsciiString();
	Rva0043A3B0Pair entry;
	((UnicodeString *)&entry.first)->set( *(const UnicodeString *)&token );
	self->m_items->push_back( entry );
}

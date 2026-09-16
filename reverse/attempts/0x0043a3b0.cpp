// ?parseFontFileName@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.99 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include "string_base.h"
#include "ascii_string.h"

class INI
{
public:
	AsciiString getNextAsciiString();
};

class Open2Rec439370
{
public:
	Open2Rec439370() {}
	Open2Rec439370( const Open2Rec439370 &other );

	AsciiString m_at00;
	AsciiString m_at04;
};

namespace _STL
{

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

template <class T>
class allocator
{
};

template <class T, class Alloc>
class list
{
public:
	typedef _List_node<T> _Node;

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

inline void *operator new( unsigned int, void *place ) { return place; }
inline void operator delete( void *, void * ) {}

class GlobalLanguage
{
public:
	static void parseFontFileName( INI *ini, void *instance, void *store, const void *userData );

	unsigned char m_unmodelled[ 0x134 ];
	_STL::list<Open2Rec439370, _STL::allocator<Open2Rec439370> > *m_localFonts;
};

void GlobalLanguage::parseFontFileName( INI *ini, void *instance, void *store, const void *userData )
{
	GlobalLanguage *self = (GlobalLanguage *)instance;
	AsciiString token = ini->getNextAsciiString();
	Open2Rec439370 entry;
	entry.m_at00.set( token );
	self->m_localFonts->push_back( entry );
}

// Six of 203 bytes differ and both residues are register choices.
//
// At +0x76 retail computes the address of entry into edx and we compute it
// into eax. At +0xbf retail writes fs:[0] and then pops ebx while we pop ebx
// first. Everything else matches, frame slots and unwind states included.
//
// These spellings left both residues untouched: a named const reference at the
// call site, a source pointer inside _Construct, a named destination local, the
// assignment operator instead of set, an inlined instance cast, a raw void*
// local before the node cast, _M_create_node as an inline and as a forceinline
// member, _M_insert taking the sentinel, push_back taking a pointer, _Construct
// as a free function template, throw() on _M_allocate, and throw() on the
// placement operator new. The flag sweep /G5 /G6 /G7 /GB /Ot /Oy /Gy /Ob1 /Oi
// /Ow /Oa /Op /Og /GF /Gf changed nothing either, and /Os and /Oy- made the
// body shorter and much further away.

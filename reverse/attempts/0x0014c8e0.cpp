// ?parseTemplateNameIntList@Rva0014C8E0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.35 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME7: INI field parser at 0x0014C8E0 (196 B): resolves a
// ThingTemplate via the already-matched INI::parseThingTemplate (0x000BAD60),
// reads an Int with INI::parseInt, copies the template's UnicodeString field
// at +0x20 into the entry when that field is non-empty (buffer non-null and
// its length word non-zero) and pushes the finished (name Int) entry onto
// the instance's list at +0x14 -- the same eight-byte element and
// _Construct pin (0x0014C4C0) as the landed sibling list<Rva0014C4C0Element>
// family (Rva0014C5A0ListInsert.cpp). Names are address-derived; the
// ThingTemplate field offset is read directly off the body, not named.

typedef int Int;

class INI;

class ThingTemplate
{
public:
	char m_pad[ 0x20 ];
	struct
	{
		char *m_data;
	} m_nameField;			// +0x20
};

class UnicodeString
{
public:
	UnicodeString() : m_data( 0 ) {}
	~UnicodeString();

	void set( const UnicodeString &other );

private:
	unsigned short *m_data;
};

class INI
{
public:
	static void parseThingTemplate( INI *ini, void *instance, void *store, const void *userData );
	static void parseInt( INI *ini, void *instance, void *store, const void *userData );
};

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
	_List_iterator(_List_node_base *node) : _M_node(node) {}

	_List_node_base *_M_node;
};

template <class T, class Alloc>
class _List_base
{
public:
	typedef _List_node<T> _Node;

	_Node *_M_node;
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

private:
	_Node *_M_create_node( const T &value )
	{
		_Node *node = (_Node *)BfmeNodeAllocate( sizeof( _Node ) );
		_Construct( &node->_M_data, value );
		return node;
	}
};

}

struct Rva0014C4C0Element
{
	UnicodeString m_name;
	Int m_value;
};

class Rva0014C8E0Store
{
public:
	char m_bfmeHead[ 0x14 ];
	_STL::list<Rva0014C4C0Element, _STL::allocator<Rva0014C4C0Element> > m_bfmeItems;
};

class Rva0014C8E0
{
public:
	static void parseTemplateNameIntList( INI *ini, void *instance, void *, const void *userData );
};

// ?parseTemplateNameIntList@Rva0014C8E0@@SAXPAVINI@@PAX1PBX@Z
void Rva0014C8E0::parseTemplateNameIntList( INI *ini, void *instance, void *, const void *userData )
{
	const ThingTemplate *tmplate = 0;
	INI::parseThingTemplate( ini, 0, &tmplate, 0 );

	Rva0014C4C0Element entry;
	entry.m_value = 0;
	INI::parseInt( ini, 0, &entry.m_value, 0 );

	if( tmplate && tmplate->m_nameField.m_data && *(short *)( tmplate->m_nameField.m_data + 4 ) != 0 )
	{
		entry.m_name.set( *(const UnicodeString *)&tmplate->m_nameField );
	}

	Rva0014C8E0Store *self = (Rva0014C8E0Store *)instance;
	self->m_bfmeItems.push_back( entry );
}

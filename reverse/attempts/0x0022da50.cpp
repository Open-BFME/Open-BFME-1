// ?parseNameIntList@Rva0022DA50@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.4 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME7: INI field parser at 0x0022DA50 (223 B): reads a name token,
// then an optional value token (getNextTokenOrNull) scanned as an Int
// (default 1 when the value token is absent), sets a RetailLayoutString
// name from the name token (inline strlen guarded against a null token)
// and inserts the finished (name value) entry at the tail of the
// instance's list at +0x174 -- the same eight-byte element, node layout
// and _Construct pin (0x0022D610's own _Construct at 0x000402C8) as the
// landed sibling list<Rva0022D610Element> in RvaListInsert8.cpp. Names
// are address-derived.

typedef int Int;

extern "C" __declspec(dllimport) unsigned int __stdcall strlen(const char *s);

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	static Int scanInt(const char *token);
};

class RetailLayoutString
{
public:
	RetailLayoutString()
	{
		m_data = 0;
	}

	~RetailLayoutString();

	void set(const char *text, int length);

private:
	char *m_data;
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

struct Rva0022D610Element
{
	RetailLayoutString m_name;
	Int m_value;
};

class Rva0022DA50Store
{
public:
	char m_bfmeHead[ 0x174 ];
	_STL::list<Rva0022D610Element, _STL::allocator<Rva0022D610Element> > m_bfmeItems;
};

class Rva0022DA50
{
public:
	static void parseNameIntList( INI *ini, void *instance, void *, const void * );
};

// ?parseNameIntList@Rva0022DA50@@SAXPAVINI@@PAX1PBX@Z
void Rva0022DA50::parseNameIntList( INI *ini, void *instance, void *, const void * )
{
	const char *name = ini->getNextToken();
	const char *valueToken = ini->getNextTokenOrNull();

	Rva0022D610Element entry;
	entry.m_value = valueToken ? INI::scanInt( valueToken ) : 1;
	entry.m_name.set( name, name ? (int)strlen( name ) : 0 );

	Rva0022DA50Store *self = (Rva0022DA50Store *)instance;
	self->m_bfmeItems.push_back( entry );
}

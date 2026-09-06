// ?parseKeyLabelList@Rva0043A3B0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.35 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME7: INI field parser at 0x0043A3B0 (203 B): reads a label via
// INI::getNextAsciiString (hidden-return AsciiString), sets a UnicodeString
// local from it and inserts a (key value) pair into the instance's
// associative list at +0x214 -- the pair ctor at 0x00439370 (already
// matched, key 4 bytes / value 12 bytes) is the node's _Construct.  The
// UnicodeString::set(const UnicodeString&) mangled name given for the
// 0x00887C90 callee is used as-is even though the source value here is
// built from an AsciiString; not yet byte-verified.

typedef int Int;

class AsciiString
{
public:
	AsciiString();
	~AsciiString();
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
	~UnicodeString();

	void set( const UnicodeString &other );

private:
	unsigned short *m_data;
};

struct Rva00439370Pair
{
	Int m_key;
	UnicodeString m_value;
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

class Rva0043A3B0Store
{
public:
	char m_bfmeHead[ 0x214 ];
	_STL::list<Rva00439370Pair, _STL::allocator<Rva00439370Pair> > m_bfmeItems;
};

class Rva0043A3B0
{
public:
	static void parseKeyLabelList( INI *ini, void *instance, void *, const void * );
};

// ?parseKeyLabelList@Rva0043A3B0@@SAXPAVINI@@PAX1PBX@Z
void Rva0043A3B0::parseKeyLabelList( INI *ini, void *instance, void *, const void * )
{
	AsciiString token = ini->getNextAsciiString();

	Rva00439370Pair entry;
	entry.m_key = 0;
	entry.m_value.set( *(const UnicodeString *)&token );

	Rva0043A3B0Store *self = (Rva0043A3B0Store *)instance;
	self->m_bfmeItems.push_back( entry );
}

// ?parseTarget@Rva0014C8E0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.95 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: the Target field parser of the AI AttackPriority block, retail
// 0x0014C8E0, 196 bytes.
//
// The identity is settled by two tables. The AI FieldParse table at 0x01094B00
// pairs 'AttackPriority' at row 0x01094CE0 with the parser at 0x0014E130, and
// that parser is the only place in the image that reads the sub-table at
// 0x010959F4. Row 0x01095A04 of the sub-table pairs 'Target' with this body, so
// the field names the function. Nothing in the image names the owning class, so
// the class name here keeps the address.
//
// The body reads a ThingTemplate through INI::parseThingTemplate at 0x000BAD60
// and a count through INI::parseInt, builds an eight-byte record on the stack,
// and appends it to the list the store argument points at. The record copy runs
// through the landed Open2Construct14BBC0 at 0x0014BBC0.
#include "string_base.h"
#include "ascii_string.h"

class INI
{
public:
	static void parseThingTemplate( INI *ini, void *instance, void *store, const void *userData );
	static void parseInt( INI *ini, void *instance, void *store, const void *userData );
};

struct BfmeStringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

class ThingTemplate
{
public:
	unsigned char m_unmodelled[ 0x20 ];
	BfmeStringHeader *m_name;
};

class Open2Rec14BBC0
{
public:
	Open2Rec14BBC0() : m_at04( 0 ) {}

	AsciiString m_at00;
	int m_at04;
};

void Open2Construct14BBC0( Open2Rec14BBC0 *place, const Open2Rec14BBC0 &value );

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

	__forceinline void push_back( const T &value )
	{
		_List_node_base *at = _M_node;
		_Node *node = (_Node *)__node_alloc<true, 0>::_M_allocate( sizeof( _Node ) );
		Open2Construct14BBC0( &node->_M_data, value );
		_List_node_base *before = at->_M_prev;
		node->_M_next = at;
		node->_M_prev = before;
		before->_M_next = node;
		at->_M_prev = node;
	}
};

}

typedef _STL::list<Open2Rec14BBC0, _STL::allocator<Open2Rec14BBC0> > Open2Rec14BBC0List;

class Rva0014C8E0
{
public:
	static void parseTarget( INI *ini, void *instance, void *store, const void *userData );
};

void Rva0014C8E0::parseTarget( INI *ini, void *instance, void *store, const void *userData )
{
	const ThingTemplate *tmpl;
	int priority;

	INI::parseThingTemplate( ini, 0, &tmpl, 0 );
	INI::parseInt( ini, 0, &priority, 0 );

	Open2Rec14BBC0 entry;
	if( tmpl != 0 && tmpl->m_name != 0 && tmpl->m_name->m_length != 0 )
	{
		entry.m_at00.set( *(const AsciiString *)&tmpl->m_name );
		Open2Rec14BBC0List *items = *(Open2Rec14BBC0List **)store;
		entry.m_at04 = priority;
		items->push_back( entry );
	}
}

// Nine of 196 bytes differ and both residues are register choices.
//
// At +0x6b retail loads store into eax, the count into edx and the list into
// ecx. We load them in the same order into edx, ecx and eax. At +0xb8 retail
// writes fs:[0] and then pops esi, while we pop esi first. Every other byte
// matches, including the frame slots, the unwind states and the whole guard
// chain.
//
// push_back needs __forceinline. Without it MSVC leaves it out of line and the
// body comes to 177 bytes. Reading the list pointer into a local before the
// count assignment is what fixed the load order, which took the body from
// fourteen differing bytes to nine.
//
// These spellings moved neither residue: a pointer-to-pointer local, a
// reference to the list, a comma expression, a named local for the count, the
// assignment operator in place of set, a real AsciiString member on
// ThingTemplate, a named reference to the source string, a free function
// instead of a static member, allocating the node before reading the sentinel,
// dropping the record's default constructor for an explicit zero store, and
// value-initialising both members. The flag sweep /O1 /Os /Ot /Gy /G5 /G6 /Ob1
// /EHs /EHa /GX /MT /MDd /Zp1 /Zp16 /GS /Gd /W4 changed nothing either.
//
// The 0.95 bank of 2026-09-06 stalled on the same two residues. What is new
// here is the identity above and the two callee names, since 0x0014BBC0 now
// carries ?Open2Construct14BBC0@@YAXPAVOpen2Rec14BBC0@@ABV1@@Z instead of a
// gen-tgrid pair placeholder.

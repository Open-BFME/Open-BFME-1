// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
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
// and pushes it onto the front of the list the store argument addresses. The
// store is the list itself (the AINamedListNode tail parseAttackPriority hands
// initFromINI): retail loads the sentinel from the store and links the new node
// before the sentinel's next, which is insert(begin()). The record copy runs
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

#include <list>
namespace _STL {
template <> __forceinline void _Construct<Open2Rec14BBC0, Open2Rec14BBC0>(Open2Rec14BBC0 *place, const Open2Rec14BBC0 &value) { Open2Construct14BBC0(place, value); }
template <> __forceinline void list<Open2Rec14BBC0, allocator<Open2Rec14BBC0> >::push_front(const Open2Rec14BBC0 &value) { insert(begin(), value); }
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
		entry.m_at00.StringBase<char>::set( *(const AsciiString *)&tmpl->m_name );
		Open2Rec14BBC0List *items = (Open2Rec14BBC0List *)store;
		entry.m_at04 = priority;
		items->push_front( entry );
	}
}

// Native list and force-inlined native push_front preserve the retail FS restore
// before pop ESI. The earlier list-pointer push_back reading left a five-byte
// store/priority/list register rotation at +0x6B; the in-place list with
// push_front is exact. The _Construct specialization delegates to the
// already-landed Open2Construct14BBC0; no new pin is required.

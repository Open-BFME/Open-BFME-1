// cl: /DNDEBUG /DWIN32 /MD /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class ThingTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
// The lookup itself is the BfmeThingFactory facade (const return, proven by
// the retail body at 0x00137E80); accepts() still wants a mutable template.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
};

extern BfmeThingFactory *TheThingFactory;

class Rva001DB720Predicate
{
public:
	bool accepts( ThingTemplate *thingTemplate );
};

class Rva001DB720NameList
{
public:
	bool anyTemplateAcceptedBy( Rva001DB720Predicate *predicate );

private:
	unsigned char m_unmodelled_000[ 8 ];
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

bool Rva001DB720NameList::anyTemplateAcceptedBy(
	Rva001DB720Predicate *predicate )
{
	for ( AsciiString *i = m_begin; i != m_end; ++i )
	{
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate( *i );
		if ( thingTemplate && predicate->accepts( (ThingTemplate *)thingTemplate ) )
			return true;
	}

	return false;
}

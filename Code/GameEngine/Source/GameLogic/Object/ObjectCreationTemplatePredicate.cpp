// cl: /DNDEBUG /DWIN32 /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	void *m_data;
};

class ThingTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	ThingTemplate *findTemplate( const AsciiString &name );
};

extern ThingFactory *TheThingFactory;

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
		ThingTemplate *thingTemplate = TheThingFactory->findTemplate( *i );
		if ( thingTemplate && predicate->accepts( thingTemplate ) )
			return true;
	}

	return false;
}

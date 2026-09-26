// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// ThingFactory::parseObjectDefinition( ini, name, reskinFrom, childOf ), retail
// 0x00139D00. The shared body behind the Object, ObjectReskin and ChildObject
// blocks (INIObject.cpp): Zero Hour's static ThingFactory::parseObjectDefinition
// with a third name. It sits in ThingFactory.cpp's contribution, after
// newOverride (0x00139A80) and newTemplate (0x00139B40) as in Zero Hour's
// ThingFactory.cpp, and reaches the private newOverride directly.
// BFME builds one MultiIniFieldParse for every variant, and a ChildObject
// parses its block with the INI load type temporarily set to 4.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"

// validateAudio is protected (its matched name is IAE); retail calls it from
// this ThingFactory body, so BFME's ThingTemplate lets ThingFactory in.
class ThingTemplate : public Overridable
{
	friend class ThingFactory;
public:
	void copyFrom( const ThingTemplate *that );						// 0x00148600
	void setCopiedFromDefault();										// 0x0013FDB0
	void setReskinnedFrom( const ThingTemplate *tt );					// 0x00146840
protected:
	void validateAudio();												// 0x0013E2F0
};

// ThingFactory's template hash map, seen through the out-of-line STLport
// _M_find (0x001366A0) the landed ThingFactory::findTemplate calls; the
// iterator pair is inlined around it as STLport's find() != end() is.
struct Rva001366A0Node;
class Rva00137E80Map;
struct Rva00137E80Iterator
{
	Rva001366A0Node *m_cur;
	Rva00137E80Map *m_ht;
	Rva00137E80Iterator( Rva001366A0Node *n, Rva00137E80Map *ht ) : m_cur( n ), m_ht( ht ) {}
	bool operator!=( const Rva00137E80Iterator &it ) const { return m_cur != it.m_cur; }
};
class Rva00137E80Map
{
public:
	Rva001366A0Node *find( const AsciiString & );
	Rva00137E80Iterator findIterator( const AsciiString &k ) { return Rva00137E80Iterator( find( k ), this ); }
	Rva00137E80Iterator end() { return Rva00137E80Iterator( 0, this ); }
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );		// 0x00137E80
	ThingTemplate *newTemplate( const AsciiString &name );				// 0x00139B40

	// BFME's takes three names, not Zero Hour's two: the body prints both
	// "ObjectReskin must come after the original Object" and "ChildObject must
	// come after the original Object".
	static void parseObjectDefinition( INI *ini, const AsciiString &name,
									   const AsciiString &reskinFrom,
									   const AsciiString &childOf );

	// Also emitted out of line at 0x00137E20; retail inlines it here.
	Bool rva00137E20( const AsciiString &name )
	{
		if (!strncmp( name.str(), "***TESTING", 10 ))
			return TRUE;
		return m_templateHashMap.findIterator( name ) != m_templateHashMap.end();
	}

private:
	ThingTemplate *newOverride( ThingTemplate *thingTemplate );			// 0x00139A80

	unsigned char m_unmodelled00[0x10];
	Rva00137E80Map m_templateHashMap;									// +0x10
};

extern ThingFactory *TheThingFactory;

// 0x0013E170: adds the two object field-parse tables (extra offsets 0 and 0xE0).
class Rva0013E170
{
public:
	static void buildFieldParse( MultiIniFieldParse &p );
};

void ThingFactory::parseObjectDefinition( INI *ini, const AsciiString &name,
										  const AsciiString &reskinFrom,
										  const AsciiString &childOf )
{
	// find existing item if present
	ThingTemplate *thingTemplate = NULL;
	if (TheThingFactory->rva00137E20( name ))
		thingTemplate = (ThingTemplate *)TheThingFactory->findTemplate( name );

	if (!thingTemplate)
	{
		// no item is present, create a new one
		thingTemplate = TheThingFactory->newTemplate( name );
		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
			thingTemplate->markAsOverride();
	}
	else if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
	{
		thingTemplate = TheThingFactory->newOverride( thingTemplate );
	}

	MultiIniFieldParse p;
	Rva0013E170::buildFieldParse( p );

	if (!childOf.isEmpty())
	{
		const ThingTemplate *parent = TheThingFactory->findTemplate( childOf );
		if (parent)
		{
			thingTemplate->copyFrom( parent );
			thingTemplate->setCopiedFromDefault();
			INILoadType loadType = ini->m_loadType;
			ini->m_loadType = (INILoadType)4;	// BFME-only value, no Zero Hour name
			ini->initFromINIMulti( thingTemplate, p );
			ini->m_loadType = loadType;
		}
		else
		{
			throw INIException( 3, "ChildObject must come after the original Object (%s, %s).",
								childOf.str(), name.str() );
		}
	}
	else if (!reskinFrom.isEmpty())
	{
		const ThingTemplate *reskinTmpl = TheThingFactory->findTemplate( reskinFrom );
		if (reskinTmpl)
		{
			thingTemplate->copyFrom( reskinTmpl );
			thingTemplate->setCopiedFromDefault();
			thingTemplate->setReskinnedFrom( reskinTmpl );
			ini->initFromINIMulti( thingTemplate, p );
		}
		else
		{
			throw INIException( 3, "ObjectReskin must come after the original Object (%s, %s).",
								reskinFrom.str(), name.str() );
		}
	}
	else
	{
		ini->initFromINIMulti( thingTemplate, p );
	}

	thingTemplate->validateAudio();
}

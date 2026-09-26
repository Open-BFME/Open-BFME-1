// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// ThingFactory::reset (0x00137D50): slot 4 of ThingFactory's table 0x01090E6C,
// the SubsystemInterface reset slot (init 1, loadIniFilesFromLegend 2,
// postProcessLoad 3, reset 4, update 5; WeaponStore::update and
// InGameUI::update are named in slot 5 of their tables). Zero Hour's body with
// Overridable::deleteOverrides inline, which is what puts the not-an-override
// arm after the epilogue: MSVC inlines one level and calls the out-of-line
// copy for the recursion.

#include "ascii_string.h"

typedef bool Bool;

// Only the erase call is needed; these declarations give it STLport's mangling.
namespace _STL
{
	template <class T1, class T2> struct pair;
	template <class T> struct _Select1st;
	template <class T> struct equal_to;
	template <class T> class allocator;

	template <class V, class K, class HF, class ExK, class EqK, class A>
	class hashtable
	{
	public:
		unsigned int erase( const K &key );
	};
}

namespace rts
{
	template <class T> struct hash;
}

class ThingTemplate;

typedef _STL::pair<const AsciiString, ThingTemplate *> ThingTemplateHashPair;
typedef _STL::hashtable< ThingTemplateHashPair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<ThingTemplateHashPair>, _STL::equal_to<AsciiString>,
	_STL::allocator<ThingTemplateHashPair> > ThingTemplateHashMap;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	void deleteInstance( void ) { delete this; }

	Overridable *deleteOverrides( void )
	{
		if ( m_isOverride )
		{
			deleteInstance();
			return 0;
		}
		else if ( m_nextOverride )
		{
			m_nextOverride = m_nextOverride->deleteOverrides();
		}
		return this;
	}

private:
	Overridable *m_nextOverride;							///< this+0x04
	Bool m_isOverride;										///< this+0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName( void ) const { return m_nameString; }
	ThingTemplate *friend_getNextTemplate( void ) const { return m_nextThingTemplate; }

private:
	char m_unmodelled00C[0x20 - 0x0c];
	AsciiString m_nameString;								///< this+0x20
	char m_unmodelled024[0x38c - 0x24];
	ThingTemplate *m_nextThingTemplate;						///< this+0x38C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	virtual void reset( void );

private:
	char m_unmodelled004[0x4];
	ThingTemplate *m_firstTemplate;							///< this+0x08
	char m_unmodelled00C[0x4];
	ThingTemplateHashMap m_templateHashMap;					///< this+0x10
};

// ?reset@ThingFactory@@UAEXXZ
void ThingFactory::reset( void )
{
	ThingTemplate *t;
	// go through all templates and delete any overrides
	for( t = m_firstTemplate; t; /* empty */ )
	{
		Bool possibleAdjustment = false;
		// t itself can be deleted if it is something created for this map only. Therefore, 
		// we need to store what the next item is so that we don't orphan a bunch of templates.
		ThingTemplate *nextT = t->friend_getNextTemplate();
		if (t == m_firstTemplate) {
			possibleAdjustment = true;
		}

		AsciiString templateName = t->getName();
		
		Overridable *stillValid = t->deleteOverrides();
		if (stillValid == 0 && possibleAdjustment) {
			m_firstTemplate = nextT;
		}
		
		if (stillValid == 0) {
			// Also needs to be removed from the Hash map.
			m_templateHashMap.erase(templateName);
		}

		t = nextT;
	}
}  // end reset

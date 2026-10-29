// ?rva00592130@AptPalantirHeroSelector@@QAEXABVAsciiString@@H@Z
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I. /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <hash_map>
#include <list>

#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef bool Bool;
#include "Common/GameMemory.h"
#include "Common/Overridable.h"
#include "Common/OVERRIDE.h"

class ThingTemplate : public Overridable
{
public:
	char m_unmodelled[0x14];
	AsciiString m_name;
	const AsciiString &getName() const { return m_name; }
};

#define THING_TU_MEMBERS const ThingTemplate *getTemplate() const { return OVERRIDE<ThingTemplate>(m_template); }
#include "game/GameEngine/Source/GameLogic/Object/object.h"

#include "game/GameEngine/Source/Common/Thing/GameLogicObjectLookup.h"

// ?findObjectByID@GameLogic@@QAEPAVObject@@H@Z present-unmatched
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	ObjectPtrHash &m_objectHash = m_objHash;
	if (id == 0)
		return 0;
	ObjectPtrHash::iterator it = m_objectHash.find(id);
	if (it == m_objectHash.end())
		return 0;
	return (*it).second;
}

// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic TheGameLogic

class __single_inheritance FunctorTargetSingle
{
};

class AptPalantirHeroSelector : public FunctorTargetSingle
{
private:
	struct HeroListEntry
	{
		ObjectID objectID;
		int unused;
		int value;
	};

public:
	void rva00592130(const AsciiString &name, int value);

private:
	bool m_active;
	_STL::list<HeroListEntry> m_heroes;
};

// The receiver and record layout are documented in the target evidence note.
// ?rva00592130@AptPalantirHeroSelector@@QAEXABVAsciiString@@H@Z
void AptPalantirHeroSelector::rva00592130(const AsciiString &name, int value)
{
	for (_STL::list<HeroListEntry>::iterator it = m_heroes.begin(); it != m_heroes.end(); ++it)
	{
		HeroListEntry *entry = &*it;
		Object *object = TheBfmeGameLogic->findObjectByID(entry->objectID);
		if (object != 0)
		{
			const ThingTemplate *finalTemplate = object->getTemplate();
			if (finalTemplate->getName().compare(name) == 0
				&& value > entry->value)
				entry->value = value;
		}
	}
}

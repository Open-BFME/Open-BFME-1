// ?rva00592130@AptPalantirHeroSelector@@QAEXABVAsciiString@@H@Z
// partial score=0.9 date=2026-09-18
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>


extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct Rva00592130StringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char text[1];
};

class AsciiString
{
public:
	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->length : 0;
		const char *otherText = other.m_data ? other.m_data->text : (const char *)0x0107388B;
		int thisLength = m_data ? m_data->length : 0;
		const char *thisText = m_data ? m_data->text : (const char *)0x0107388B;
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisText, otherText, length);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

private:
	Rva00592130StringData *m_data;
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

class ThingTemplate : public Overridable
{
public:
	char m_unmodelled[0x18];
	AsciiString m_name;
};

class Object
{
public:
	char m_unmodelled[4];
	ThingTemplate *m_template;
};

typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	char m_unmodelled[0xB0];
	ObjectPtrHash m_objectHash;

	Object *findObjectByID(ObjectID id)
	{
		Object *result = 0;
		if (id != 0)
		{
			ObjectPtrHash::iterator it = m_objectHash.find(id);
			if (it != m_objectHash.end())
				result = (*it).second;
		}
		return result;
	}
};

extern GameLogic *TheBfmeGameLogic;

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

// The constructor at 0x00595AC0 establishes this list at this+4, its
// 12-byte entries, and the AptPalantirHeroSelector owner.
void AptPalantirHeroSelector::rva00592130(const AsciiString &name, int value)
{
	for (_STL::list<HeroListEntry>::iterator it = m_heroes.begin(); it != m_heroes.end(); ++it)
	{
		HeroListEntry *entry = &*it;
		Object *object = TheBfmeGameLogic->findObjectByID(entry->objectID);
		if (object != 0)
		{
			ThingTemplate *thingTemplate = object->m_template;
			Overridable *finalTemplate = 0;
			if (thingTemplate != 0)
			{
				if (thingTemplate->m_nextOverride != 0)
					finalTemplate = (Overridable *)thingTemplate->m_nextOverride->getFinalOverride();
				else
					finalTemplate = (Overridable *)thingTemplate;
			}
			if (((const ThingTemplate *)finalTemplate)->m_name.compare(name) == 0
				&& value > entry->value)
				entry->value = value;
		}
	}
}

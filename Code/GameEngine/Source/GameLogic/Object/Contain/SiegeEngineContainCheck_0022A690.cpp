// ?bfmeCheck@Gen_0022A690@@QAE_NPAVObject@@PAX@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: 0x0022A690. Calls SiegeEngineContain::isValidContainerFor(other,
// false) as a "prep" step, then for an ALLIES relationship and an unset +0xE8
// flag, scans up to eight configured AsciiString template names on the
// module data at +0x24C through ThingFactory::findTemplate and accepts if
// any is ThingTemplate::isEquivalentTo the other object's (final-override)
// template. Owner-class identity is not fully recovered: the -0x18/-0x1c
// field pair and the +0xE8 flag match SiegeEngineContainIsValidContainerFor.cpp
// and SiegeEngineContainCtorThunk.cpp exactly, and the isValidContainerFor
// call is direct (not virtual), so this is very likely another
// SiegeEngineContain member, but no caller or vtable slot names which one.

typedef bool Bool;
typedef int Int;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object
{
public:
	Relationship getRelationship(const Object *other) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isEquivalentTo(const ThingTemplate *tt) const;
};

class AsciiString
{
public:
	struct Data
	{
		int m_refCount;
		unsigned short m_len;
	};

	Data *m_data;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

// Real matched sibling: SiegeEngineContainIsValidContainerFor.cpp. The
// isValidContainerFor call here is direct/non-virtual (retail: `call`, not
// `call [reg+n]`), so this class is used only through that one entry point.
class SiegeEngineContain
{
public:
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;
};

class Gen_0022A690
{
public:
	bool bfmeCheck(Object *other, void *unused);
};

// ?bfmeCheck@Gen_0022A690@@QAE_NPAVObject@@PAX@Z
bool Gen_0022A690::bfmeCheck(Object *other, void *unused)
{
	bool prep = ((const SiegeEngineContain *)this)->SiegeEngineContain::isValidContainerFor(other, false);
	if ((*(Object **)((char *)this - 0x18))->getRelationship(other) != ALLIES)
		return prep;
	else
	{
		const ThingTemplate *found;
		if (prep && *(void **)((char *)this + 0xE8) == 0)
		{
			char *moduleData = *(char **)((char *)this - 0x1C);
			int i = 0;
			AsciiString *slot = (AsciiString *)(moduleData + 0x24C);
			do
			{
				if (slot->m_data != 0 && slot->m_data->m_len != 0)
				{
					found = TheThingFactory->findTemplate(*slot);
					if (found != 0)
					{
						void *arg = *(void **)((char *)other + 4);
						if (arg != 0)
						{
							Overridable *next = *(Overridable **)((char *)arg + 4);
							if (next != 0)
								arg = (void *)next->getFinalOverride();
						}
						if (found->isEquivalentTo((const ThingTemplate *)arg))
							return true;
					}
				}
				++i;
				slot = (AsciiString *)((char *)slot + 0x18);
			} while (i < 8);
		}
		return false;
	}
}

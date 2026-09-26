// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: RiderChangeContain::isValidContainerFor at retail RVA 0x0022A690.
// This source uses the adjusted containment pointer passed by the retail body.

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

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

class SiegeEngineContain
{
public:
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;
};

class AsciiString
{
public:
	struct Data
	{
		Int m_padding;
		UnsignedShort m_length;
	};

	Data *m_data;
};

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
	Bool isEquivalentTo(const ThingTemplate *other) const;
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

#define TheThingFactory (*(ThingFactory **)0x012EF1D8)

class RiderChangeContain
{
public:
	virtual Bool isValidContainerFor(const Object *rider, Bool checkCapacity) const;
};

// ?isValidContainerFor@RiderChangeContain@@UBE_NPBVObject@@_N@Z
Bool RiderChangeContain::isValidContainerFor(const Object *rider, Bool checkCapacity) const
{
	Bool prep = ((SiegeEngineContain *)this)->SiegeEngineContain::isValidContainerFor(rider, 0);
	if ((*(Object **)((char *)this - 0x18))->getRelationship(rider) != ALLIES)
		return prep;
	else
	{
		ThingTemplate *found;
		if (prep && *(void **)((char *)this + 0xE8) == 0)
		{
			char *owner = *(char **)((char *)this - 0x1C);
			Int i = 0;
			AsciiString *slot = (AsciiString *)(owner + 0x24C);
			do
			{
				if (slot->m_data != 0 && slot->m_data->m_length != 0)
				{
					found = TheThingFactory->findTemplate(*slot);
					if (found != 0)
					{
						void *arg = *(void **)((char *)rider + 4);
						if (arg != 0)
						{
							Overridable *next = *(Overridable **)((char *)arg + 4);
							if (next != 0)
								arg = (void *)next->getFinalOverride();
						}
						if (found->isEquivalentTo((ThingTemplate *)arg))
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

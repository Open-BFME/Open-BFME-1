// ?d_0022a690@@YAXXZ
// partial score=0.62 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022A690. Prep the argument, require ALLIES, then scan eight
// AsciiString slots through ThingFactory::findTemplate.

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

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_next;
};

class AsciiString
{
public:
	struct Data
	{
		int m_pad;
		unsigned short m_n;
	};

	Data *m_data;
};

class BfmeD975
{
public:
	bool bfmeUse975D(void *arg);
};

class ThingFactory
{
public:
	BfmeD975 *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class Gen_0022A690
{
public:
	bool bfmePrep(Object *other, int zero);
	bool bfmeCheck(Object *other, void *unused);
};

// ?bfmeCheck@Gen_0022A690@@QAE_NPAVObject@@PAX@Z
bool Gen_0022A690::bfmeCheck(Object *other, void *unused)
{
	bool prep = bfmePrep(other, 0);
	if ((*(Object **)((char *)this - 0x18))->getRelationship(other) != ALLIES)
		return prep;
	else
	{
		BfmeD975 *found;
		if (!prep)
			return false;
		if (*(void **)((char *)this + 0xE8) != 0)
			return false;

		char *owner = *(char **)((char *)this - 0x1C);
		int i = 0;
		AsciiString *slot = (AsciiString *)(owner + 0x24C);
		do
		{
			if (slot->m_data != 0 && slot->m_data->m_n != 0)
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
					if (found->bfmeUse975D(arg))
						return true;
				}
			}
			++i;
			slot = (AsciiString *)((char *)slot + 0x18);
		} while (i < 8);
		return false;
	}
}

// cl: /O2 /Ob0
//
// Retail 0x001DE0B0 and 0x001DE120 (swapped args).  Unconditional add-4 is
// the member this of a +4 slot, matching GettingBuiltBehaviorCostForDamage's
// OVERRIDE load.

class Overridable
{
public:
	__inline const Overridable *getFinalOverride() const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

__inline const Overridable *Overridable::getFinalOverride() const
{
	if (m_nextOverride != 0)
		return m_nextOverride->getFinalOverride();
	return this;
}

class Rva001DE0B0Thing : public Overridable
{
public:
	unsigned char m_gap[0x47a - 8];
	unsigned short m_key;
};

class Rva001DE0B0Slot
{
public:
	Rva001DE0B0Thing *volatile m_value;
};

class Rva001DE0B0Entry
{
public:
	int m_spare;
	Rva001DE0B0Slot m_slot;
};

class Rva001DE0B0Holder
{
public:
	unsigned char m_head[8];
	Rva001DE0B0Entry *m_entry;
};

float __cdecl rva001DE0B0(Rva001DE0B0Holder *first, Rva001DE0B0Holder *second)
{
	Rva001DE0B0Slot &firstSlot = first->m_entry->m_slot;
	Rva001DE0B0Thing *value = firstSlot.m_value;
	Rva001DE0B0Thing *firstThing;
	if (value == 0)
		firstThing = 0;
	else if (value->m_nextOverride == 0)
		firstThing = value;
	else
		firstThing = (Rva001DE0B0Thing *)value->m_nextOverride->getFinalOverride();

	Rva001DE0B0Slot &secondSlot = second->m_entry->m_slot;
	value = secondSlot.m_value;
	Rva001DE0B0Thing *secondThing;
	if (value == 0)
		secondThing = 0;
	else if (value->m_nextOverride == 0)
		secondThing = value;
	else
		secondThing = (Rva001DE0B0Thing *)value->m_nextOverride->getFinalOverride();

	return (float)(firstThing->m_key - secondThing->m_key);
}

float __cdecl rva001DE120(Rva001DE0B0Holder *second, Rva001DE0B0Holder *first)
{
	Rva001DE0B0Slot &firstSlot = first->m_entry->m_slot;
	Rva001DE0B0Thing *value = firstSlot.m_value;
	Rva001DE0B0Thing *firstThing;
	if (value == 0)
		firstThing = 0;
	else if (value->m_nextOverride == 0)
		firstThing = value;
	else
		firstThing = (Rva001DE0B0Thing *)value->m_nextOverride->getFinalOverride();

	Rva001DE0B0Slot &secondSlot = second->m_entry->m_slot;
	value = secondSlot.m_value;
	Rva001DE0B0Thing *secondThing;
	if (value == 0)
		secondThing = 0;
	else if (value->m_nextOverride == 0)
		secondThing = value;
	else
		secondThing = (Rva001DE0B0Thing *)value->m_nextOverride->getFinalOverride();

	return (float)(firstThing->m_key - secondThing->m_key);
}

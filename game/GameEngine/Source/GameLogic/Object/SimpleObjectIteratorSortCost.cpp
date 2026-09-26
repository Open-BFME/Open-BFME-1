// cl: /O2 /Ob0
//
// BFME's cost-order callbacks.  The callback table used by
// SimpleObjectIterator::sort routes its third and fourth order values through
// ILT thunks to these two bodies.

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

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed08[0x47a - 8];
	unsigned short m_unreconstructed047a;
};

class ThingTemplateSlot
{
public:
	ThingTemplate *volatile m_value;
};

class Object
{
public:
	int m_unreconstructed00;
	ThingTemplateSlot m_template;
};

class SimpleObjectIterator
{
public:
	class Clump
	{
	public:
		int m_unreconstructed00;
		Clump *m_nextClump;
		Object *m_obj;
	};

private:
	static float sortCheapToExpensive(Clump *first, Clump *second);
	static float sortExpensiveToCheap(Clump *first, Clump *second);
};

float SimpleObjectIterator::sortCheapToExpensive(Clump *first, Clump *second)
{
	ThingTemplateSlot &firstSlot = first->m_obj->m_template;
	ThingTemplate *value = firstSlot.m_value;
	ThingTemplate *firstTemplate;
	if (value == 0)
		firstTemplate = 0;
	else if (value->m_nextOverride == 0)
		firstTemplate = value;
	else
		firstTemplate = (ThingTemplate *)value->m_nextOverride->getFinalOverride();

	ThingTemplateSlot &secondSlot = second->m_obj->m_template;
	value = secondSlot.m_value;
	ThingTemplate *secondTemplate;
	if (value == 0)
		secondTemplate = 0;
	else if (value->m_nextOverride == 0)
		secondTemplate = value;
	else
		secondTemplate = (ThingTemplate *)value->m_nextOverride->getFinalOverride();

	return (float)(firstTemplate->m_unreconstructed047a - secondTemplate->m_unreconstructed047a);
}

float SimpleObjectIterator::sortExpensiveToCheap(Clump *second, Clump *first)
{
	ThingTemplateSlot &firstSlot = first->m_obj->m_template;
	ThingTemplate *value = firstSlot.m_value;
	ThingTemplate *firstTemplate;
	if (value == 0)
		firstTemplate = 0;
	else if (value->m_nextOverride == 0)
		firstTemplate = value;
	else
		firstTemplate = (ThingTemplate *)value->m_nextOverride->getFinalOverride();

	ThingTemplateSlot &secondSlot = second->m_obj->m_template;
	value = secondSlot.m_value;
	ThingTemplate *secondTemplate;
	if (value == 0)
		secondTemplate = 0;
	else if (value->m_nextOverride == 0)
		secondTemplate = value;
	else
		secondTemplate = (ThingTemplate *)value->m_nextOverride->getFinalOverride();

	return (float)(firstTemplate->m_unreconstructed047a - secondTemplate->m_unreconstructed047a);
}

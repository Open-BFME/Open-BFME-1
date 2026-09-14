// ?chooseLocomotorSetExplicit@AIUpdateInterface@@AAE_NW4LocomotorSetType@@@Z
// partial score=0.9 date=2026-09-14
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0
};

class LocomotorTemplate;

class LocomotorTemplateVector
{
public:
	char *m_start;
	char *m_finish;

	UnsignedInt size() const
	{
		return (UnsignedInt)((m_finish - m_start) >> 2);
	}

	const LocomotorTemplate *operator[](UnsignedInt index) const
	{
		return ((const LocomotorTemplate **)m_start)[index];
	}
};

class BfmeThingTemplate
{
public:
	const BfmeThingTemplate *getFinalOverride() const;
	const LocomotorTemplateVector *findLocomotorTemplateVector(LocomotorSetType type) const;

	char m_vtable[4];
	const BfmeThingTemplate *m_nextOverride;
};

class BfmeObject
{
public:
	__forceinline const BfmeThingTemplate *getTemplate() const
	{
		const BfmeThingTemplate *const volatile *templateSlot = &m_template;
		const BfmeThingTemplate *thingTemplate = *templateSlot;
		if (thingTemplate == 0)
			return 0;
		if (thingTemplate->m_nextOverride)
			thingTemplate = thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}

	char m_vtable[4];
	const BfmeThingTemplate *m_template;
};

class LocomotorSet
{
public:
	void clear();
	void addLocomotor(const LocomotorTemplate *lt);

	char m_fields[0x24];
};

class AIUpdateInterface
{
private:
	Bool chooseLocomotorSetExplicit(LocomotorSetType wst);
	__forceinline BfmeObject *getObject() const { return m_object; }

	char m_fields[8];
	BfmeObject *m_object;
	char m_fieldsBeforeLocomotorSet[0x1a8 - 0x0c];
	LocomotorSet m_locomotorSet;
	void *m_curLocomotor;
	LocomotorSetType m_curLocomotorSet;
};

Bool AIUpdateInterface::chooseLocomotorSetExplicit(LocomotorSetType wst)
{
	BfmeObject *object = getObject();
	const BfmeThingTemplate *thingTemplate = object->getTemplate();
	const LocomotorTemplateVector *set = thingTemplate->findLocomotorTemplateVector(wst);
	if (set)
	{
		m_locomotorSet.clear();
		m_curLocomotor = 0;
		for (Int i = 0; i < set->size(); ++i)
		{
			const LocomotorTemplate *lt = (*set)[i];
			if (lt)
				m_locomotorSet.addLocomotor(lt);
		}
		m_curLocomotorSet = wst;
		return true;
	}
	return false;
}

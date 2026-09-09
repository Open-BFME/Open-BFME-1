// ?freeDatabase@ThingFactory@@AAEXXZ
// partial score=0.85 date=2026-09-09

class ThingTemplate
{
public:
	ThingTemplate *getNextTemplate() const
	{
		return *(ThingTemplate **)((const char *)this + 0x38c);
	}
	virtual void deleteInstance(bool destroy = true) = 0;
};

class ThingTemplateHashMap
{
public:
	void clear();
};

class ThingFactory
{
	void freeDatabase();

public:
	char m_base[8];
	ThingTemplate *m_firstTemplate;
	char m_pad0c[4];
	ThingTemplateHashMap m_templateHashMap;
};

void ThingFactory::freeDatabase()
{
	while (m_firstTemplate)
	{
		ThingTemplate *tmpl = m_firstTemplate;
		m_firstTemplate = tmpl->getNextTemplate();
		tmpl->deleteInstance();
	}

	m_templateHashMap.clear();
}

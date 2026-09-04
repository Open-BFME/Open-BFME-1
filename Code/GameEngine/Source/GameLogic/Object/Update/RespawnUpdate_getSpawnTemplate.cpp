// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
	char *m_data;
};

class ThingTemplate;

class Overridable
{
public:
	void *m_vtbl;
	ThingTemplate *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	ThingTemplate *getFinalOverride();
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class Object
{
public:
	void *m_vtbl;
	ThingTemplate *m_template;
};

class RespawnUpdateModuleData
{
public:
	unsigned char m_pad[0xb0];
	AsciiString m_spawnTemplateName;
};

class RespawnUpdate
{
public:
	ThingTemplate *getSpawnTemplate();

private:
	void *m_vtbl;
	RespawnUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_gap[0x28 - 0x0c];
	ThingTemplate *m_cachedTemplate;
};

// ?getSpawnTemplate@RespawnUpdate@@QAEPAVThingTemplate@@XZ
ThingTemplate *RespawnUpdate::getSpawnTemplate()
{
	if (m_cachedTemplate == (ThingTemplate *)-1)
	{
		ThingTemplate *t = TheThingFactory->findTemplate(m_moduleData->m_spawnTemplateName);
		m_cachedTemplate = t;
		if (!t)
		{
			Object *obj = m_object;
			volatile unsigned char *raw = (volatile unsigned char *)obj;
			raw += 4;
			t = *(ThingTemplate * volatile *)raw;
			if (!t)
			{
				m_cachedTemplate = t;
				return t;
			}
			ThingTemplate *next = t->m_nextOverride;
			if (next)
				t = next->getFinalOverride();
			m_cachedTemplate = t;
		}
	}
	return m_cachedTemplate;
}

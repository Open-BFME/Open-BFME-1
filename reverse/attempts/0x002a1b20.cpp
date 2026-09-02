// ?getSpawnTemplate@RespawnUpdate@@QAEPAVThingTemplate@@XZ
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// RespawnUpdate lazy ThingTemplate cache at +0x28. Sentinel -1 means
// unresolved; findTemplate on module-data+0xb0, else the object's template
// walked through Overridable::friend_getFinalOverride.

class AsciiString
{
	char *m_data;
};

class Overridable
{
public:
	Overridable *friend_getFinalOverride();

	void *m_vtbl;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
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
			unsigned char *raw = (unsigned char *)obj;
			raw += 4;
			t = *(ThingTemplate **)raw;
			if (!t)
			{
				m_cachedTemplate = t;
				return t;
			}
			Overridable *next = t->m_nextOverride;
			if (next)
				t = (ThingTemplate *)next->friend_getFinalOverride();
			m_cachedTemplate = t;
		}
	}
	return m_cachedTemplate;
}

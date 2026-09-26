// cl: /DNDEBUG /MD /EHsc

// ?newOverride@ThingFactory@@AAEPAVThingTemplate@@PAV2@@Z
// BFME stores ThingTemplate as 0x4d4 bytes.  The retail body also brackets the
// copy-assignment ILT with writes to its global copy-state byte.

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
	bool m_isOverride;

	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	void markAsOverride()
	{
		m_isOverride = true;
	}

	void setNextOverride(Overridable *next)
	{
		m_nextOverride = next;
	}
};

class ThingTemplate : public Overridable
{
private:
	unsigned char m_padding[0x4d4 - 0xc];
	virtual ~ThingTemplate();

public:
	ThingTemplate();
	ThingTemplate &operator=(const ThingTemplate &other);
	void setCopiedFromDefault();
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
};

class ThingFactory : public SubsystemInterface
{
private:
	ThingTemplate *newOverride(ThingTemplate *thingTemplate);
};

ThingTemplate *ThingFactory::newOverride(ThingTemplate *thingTemplate)
{
	ThingTemplate *child =
		(ThingTemplate *)thingTemplate->friend_getFinalOverride();

	ThingTemplate *newTemplate = new ThingTemplate;
	*(unsigned char *)0x012ed611 = 1;
	*newTemplate = *child;
	*(unsigned char *)0x012ed611 = 0;
	newTemplate->setCopiedFromDefault();
	newTemplate->markAsOverride();
	child->setNextOverride(newTemplate);
	return newTemplate;
}

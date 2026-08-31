// cl: /DNDEBUG /MD /EHsc
// BFME ExperienceTracker::isTrainable at retail RVA 0x001B2380.

typedef bool Bool;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

private:
	void *m_vtable;
	Overridable *m_nextOverride;

	friend class Thing;
};

class ThingTemplate : public Overridable
{
public:
	Bool isTrainable() const
	{
		return m_isTrainable;
	}

private:
	unsigned char m_unreconstructed_008[0x487 - 0x008];
	Bool m_isTrainable;

	friend class ThingTemplateRef;
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const;

protected:
	virtual ~Thing();

private:
	const ThingTemplate *m_template;
};

inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *const volatile *templateSlot = &m_template;
	const ThingTemplate *thingTemplate = *templateSlot;
	if (thingTemplate == 0)
		return 0;
	if (thingTemplate->m_nextOverride)
		thingTemplate = static_cast<const ThingTemplate *>(
			thingTemplate->m_nextOverride->getFinalOverride());
	return thingTemplate;
}

class Object : public Thing
{
};

class ExperienceTracker
{
public:
	Bool isTrainable() const;

private:
	void *m_vtable;
	Object *m_parent;
};

Bool ExperienceTracker::isTrainable() const
{
	return m_parent->getTemplate()->isTrainable();
}

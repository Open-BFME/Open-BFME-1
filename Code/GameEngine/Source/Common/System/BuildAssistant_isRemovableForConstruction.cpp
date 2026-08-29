// cl: /DNDEBUG /MD /EHs-c-

// BuildAssistant::isRemovableForConstruction, retail 0x000FE5D0 (90 bytes).
//
// BFME keeps the inert kind at bit 24 of ThingTemplate::m_kindof (+0xd0),
// while the two ordinary tests remain calls through Thing::isKindOf.  The
// effectively-dead flag is the low bit of Object's private status byte at
// +0x344.  These are the BFME offsets; the vendored Zero Hour headers use a
// different Object layout and cannot be included for this leaf body.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum KindOfType
{
	KINDOF_SHRUBBERY = 6,
	KINDOF_CLEARED_BY_BUILD = 50,
	KINDOF_INERT = 24
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindof & (1U << kind)) != 0;
	}

private:
	unsigned char m_pad[0xc8];
	UnsignedInt m_kindof;
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl != 0 && tmpl->m_nextOverride != 0)
			tmpl = static_cast<const ThingTemplate *>(
				tmpl->m_nextOverride->getFinalOverride());
		return tmpl;
	}

	Bool isKindOf(KindOfType kind) const;

private:
	void *_vptr;
	const ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	Bool isEffectivelyDead() const
	{
		return *reinterpret_cast<const unsigned char *>(
			reinterpret_cast<const char *>(this) + 0x344) & 1;
	}
};

class BuildAssistant
{
protected:
	Bool isRemovableForConstruction(Object *obj);
};

// ?isRemovableForConstruction@BuildAssistant@@IAE_NPAVObject@@@Z
Bool BuildAssistant::isRemovableForConstruction(Object *obj)
{
	if (obj == 0)
		return false;

	if (obj->getTemplate()->isKindOf(KINDOF_INERT))
	{
		((void)0);
		return false;
	}

	if (obj->isKindOf(KINDOF_SHRUBBERY))
		return true;

	if (obj->isKindOf(KINDOF_CLEARED_BY_BUILD))
		return true;

	if (obj->isEffectivelyDead())
		return true;

	return false;
}

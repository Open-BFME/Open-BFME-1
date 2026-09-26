// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x001FE8A0, 86 bytes.  GettingBuiltBehavior's constructor and
// vftable 0x010A45E0 prove that this receiver is its secondary base at +0x20.
// Therefore the two negative reads are the primary module's ModuleData at
// this-0x1C (owner+0x04) and Object at this-0x18 (owner+0x08).
//
// The Object layout is independently established in ObjectDamageAndWeapons:
// its OVERRIDE<ThingTemplate> is at +0x04 and BodyModuleInterface is at
// +0x200.  Slot 8 of the latter is getDamageState().  The adjacent
// GettingBuiltBehaviorModuleData constructor establishes four Real values at
// +0x30..+0x3C, one for each BodyDamageType.  The existing named callers of
// ThingTemplate::calcCostToBuild prove its (const Player *, Int) ABI.

typedef int Int;
typedef float Real;

class Player;

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
	Int calcCostToBuild(const Player *player, Int buildIndex) const;
};

class ThingTemplateOverride
{
public:
	__forceinline operator const ThingTemplate *() const
	{
		const ThingTemplate *value = m_value;
		if (value == 0)
			return 0;
		return (const ThingTemplate *)value->getFinalOverride();
	}

private:
	// The retail compiler materializes this member's address before loading it.
	const ThingTemplate *volatile m_value;
};

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual BodyDamageType getDamageState() const = 0;
};

class Object
{
public:
	__forceinline const ThingTemplate *getTemplate() const
	{
		return m_template;
	}

	__forceinline BodyModuleInterface *getBodyModule() const
	{
		return m_body;
	}

private:
	void *m_vtable;
	ThingTemplateOverride m_template;
	unsigned char m_unreconstructed_08[0x200 - 0x08];
	BodyModuleInterface *m_body;
};

class GettingBuiltBehaviorModuleData
{
public:
	unsigned char m_unreconstructed_00[0x30];
	Real m_costByDamageState[4];
};

class GettingBuiltBehaviorPrimary
{
public:
	virtual void primarySlot00();

protected:
	__forceinline const GettingBuiltBehaviorModuleData *getModuleData() const
	{
		return m_moduleData;
	}

	__forceinline Object *getObject() const
	{
		return m_object;
	}

private:
	const GettingBuiltBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unreconstructed_0C[0x20 - 0x0C];
};

class Rva001FE8A0SecondaryInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual Real rva001FE8A0(const Player *player) const = 0;
};

class GettingBuiltBehavior :
	public GettingBuiltBehaviorPrimary,
	public Rva001FE8A0SecondaryInterface
{
public:
	virtual Real rva001FE8A0(const Player *player) const;
};

Real GettingBuiltBehavior::rva001FE8A0(const Player *player) const
{
	Real cost = (Real)getObject()->getTemplate()->calcCostToBuild(player, -1);
	return cost * getModuleData()->m_costByDamageState[
		getObject()->getBodyModule()->getDamageState()];
}

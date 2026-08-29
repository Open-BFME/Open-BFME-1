// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

enum WeaponSetType
{
	WEAPONSET_INVALID = 0
};

class WeaponTemplateSet;

template <unsigned int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	explicit BitFlags(WeaponSetType type)
		: m_bits(1U << (static_cast<unsigned int>(type) & 31))
	{
	}

	unsigned int m_bits;
};

typedef BitFlags<17> WeaponSetFlags;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	const WeaponTemplateSet *findWeaponTemplateSet(const WeaponSetFlags &flags) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const;
	Bool bfmeHasWeaponTemplateSet(WeaponSetType type) const;

private:
	virtual ~Thing();
	const ThingTemplate *m_template;
};

inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *thingTemplate = m_template;
	if (thingTemplate == 0)
		return 0;
	if (thingTemplate->m_nextOverride)
		thingTemplate = static_cast<const ThingTemplate *>(
			thingTemplate->m_nextOverride->getFinalOverride());
	return thingTemplate;
}

Bool Thing::bfmeHasWeaponTemplateSet(WeaponSetType type) const
{
	WeaponSetFlags flags(type);
	const WeaponTemplateSet *weaponSet =
		getTemplate()->findWeaponTemplateSet(flags);
	Bool found = weaponSet != 0;
	return found;
}

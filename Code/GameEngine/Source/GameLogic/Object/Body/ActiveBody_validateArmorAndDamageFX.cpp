// cl: /DNDEBUG /MD /EHsc
// ActiveBody::validateArmorAndDamageFX, retail 0x0020E9A0, 83 bytes.
// ZH twin: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp
//
// Identity: the only references to this body are vtable slot 14 (+0x38, ILT
// 0x0004360D) of ActiveBody's primary vtable 0x010A78B0 and the ten derived
// body vtables; no direct call exists.  Slots 14..18 follow Zero Hour's
// protected block order: createParticleSystems is slot 16 and
// deleteAllParticleSystems slot 17.  The ActiveBody constructor 0x00211A50
// inlines this exact sequence where Zero Hour's constructor calls
// validateArmorAndDamageFX(), then calls slot 18 (setCorrectDamageState).
// BFME made the helper virtual; Armor holds only its template pointer, so
// makeArmor/clear both reduce to one store.

template <int NUMBITS>
class BitFlags
{
private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<11> ArmorSetFlags;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const	// out-of-line copy: ILT 0x000022BB
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T> class OVERRIDE
{
public:
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	operator const T *() const { return operator*(); }

private:
	const T *m_overridable;
};

class ArmorTemplate;
class DamageFX;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Armor.h
class ArmorTemplateSet
{
public:
	const ArmorTemplate *getArmorTemplate() const { return m_template; }
	const DamageFX *getDamageFX() const { return m_fx; }

private:
	ArmorSetFlags m_types;
	const ArmorTemplate *m_template;
	const DamageFX *m_fx;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	const ArmorTemplateSet *findArmorTemplateSet(const ArmorSetFlags &t) const;	// ILT 0x0003BA89
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	virtual ~Thing();
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	OVERRIDE<ThingTemplate> m_template;	// +0x04
};

class Object : public Thing
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Armor.h
class Armor
{
public:
	inline Armor(const ArmorTemplate *tmpl = 0) : m_template(tmpl) {}
	inline void clear() { m_template = 0; }

private:
	const ArmorTemplate *m_template;
};

class ArmorStore
{
public:
	inline Armor makeArmor(const ArmorTemplate *tmpl) const
	{
		return Armor(tmpl);
	}
};

extern ArmorStore *TheArmorStore;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBody
{
protected:
	const Object *getObject() const { return m_object; }

	virtual void validateArmorAndDamageFX() const;	// primary vtable slot 14 (+0x38)

private:
	void *m_unmodelled04;
	Object *m_object;					// +0x08
	unsigned char m_unmodelled0C[0xD0 - 0x0C];
	ArmorSetFlags m_curArmorSetFlags;			// +0xD0
	mutable const ArmorTemplateSet *m_curArmorSet;		// +0xD4
	mutable Armor m_curArmor;				// +0xD8
	mutable const DamageFX *m_curDamageFX;			// +0xDC
};

void ActiveBody::validateArmorAndDamageFX() const
{
	const ArmorTemplateSet *set = getObject()->getTemplate()->findArmorTemplateSet(m_curArmorSetFlags);
	if (set && set != m_curArmorSet)
	{
		if (set->getArmorTemplate())
		{
			m_curArmor = TheArmorStore->makeArmor(set->getArmorTemplate());
		}
		else
		{
			m_curArmor.clear();
		}
		m_curDamageFX = set->getDamageFX();
		m_curArmorSet = set;
	}
}

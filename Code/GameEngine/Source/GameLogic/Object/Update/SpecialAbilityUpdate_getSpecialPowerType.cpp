// cl: /DNDEBUG /MD /EHsc

// SpecialAbilityUpdate::getSpecialPowerType, retail 0x002A6320. The module data
// at +0x04 holds the special power template at +0x1D8; with no template the
// answer is zero, and otherwise the type is read off the template's final
// override.
//
// That override walk is the same one-level-unrolled shape
// SpecialPowerStore_canUseSpecialPower_Thunk.cpp writes up for
// getRequiredScience: if there is an override step to it, and only if THAT one
// also has an override call the out-of-line walker. A single-entry chain costs
// no call. The field this one reads is at template+0x14 rather than +0x1C.

enum SpecialPowerType {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride( void );		// ILT thunk at 0x00048C61

	Overridable *m_nextOverride;						// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType() const
	{
		const SpecialPowerTemplate *self;
		Overridable *o = m_nextOverride;

		if( o )
		{
			if( o->m_nextOverride )
				o = o->m_nextOverride->friend_getFinalOverride();

			self = (const SpecialPowerTemplate *)o;
		}
		else
			self = this;

		return self->m_specialPowerType;
	}

private:
	unsigned char m_unmodelled_08[ 0x14 - 8 ];
	SpecialPowerType m_specialPowerType;				// +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[ 0x1D8 ];
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x1D8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate
{
public:
	SpecialPowerType getSpecialPowerType() const;

private:
	unsigned int m_unmodelled_00;
	const SpecialAbilityUpdateModuleData *m_moduleData;	// +0x04
};

// ?getSpecialPowerType@SpecialAbilityUpdate@@QBE?AW4SpecialPowerType@@XZ
SpecialPowerType SpecialAbilityUpdate::getSpecialPowerType() const
{
	const SpecialPowerTemplate *tmpl = m_moduleData->m_specialPowerTemplate;

	if( !tmpl )
		return (SpecialPowerType)0;

	return tmpl->getSpecialPowerType();
}

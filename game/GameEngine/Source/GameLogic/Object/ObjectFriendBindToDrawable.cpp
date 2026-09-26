// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME's binding body uses a 40-byte model-condition mask and the BFME Object
// offsets. The reference Object header uses a different weapon-set map and
// places the global time and weather fields at different offsets.

typedef unsigned int UnsignedInt;

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1,
	MODELCONDITION_NIGHT = 7,
	MODELCONDITION_SNOW = 8,
	MODELCONDITION_WEAPONSET_VETERAN = 12,
	MODELCONDITION_WEAPONSET_ELITE = 13,
	MODELCONDITION_WEAPONSET_HERO = 14,
	MODELCONDITION_WEAPONSET_CRATEUPGRADE_ONE = 15,
	MODELCONDITION_WEAPONSET_CRATEUPGRADE_TWO = 16,
	MODELCONDITION_WEAPONSET_PLAYER_UPGRADE = 17
};

class ModelConditionFlags
{
public:
	void clearAndSet(const ModelConditionFlags &clear, const ModelConditionFlags &set);

	void set(ModelConditionFlagType bit)
	{
		m_bits[(UnsignedInt)bit >> 5] |= 1 << ((UnsignedInt)bit & 31);
	}

	void set(ModelConditionFlagType bit, bool value)
	{
		if (value)
			m_bits[(UnsignedInt)bit >> 5] |= 1 << ((UnsignedInt)bit & 31);
		else
			m_bits[(UnsignedInt)bit >> 5] &= ~(1 << ((UnsignedInt)bit & 31));
	}

	bool operator!=(const ModelConditionFlags &other) const
	{
		for (UnsignedInt i = 0; i < 10; ++i)
		{
			if (m_bits[i] != other.m_bits[i])
				return true;
		}
		return false;
	}

	UnsignedInt m_bits[10];
};

class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &flags,
		bool forceReplace, UnsignedInt value);
};

class BfmeUpdVKP
{
public:
	void bfmeUpdateVKP();
};

class BehaviorModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void onDrawableBoundToObject();
};

class GlobalData
{
public:
	unsigned char m_pad000[0x218];
	UnsignedInt m_timeOfDay;
	UnsignedInt m_weather;
	unsigned char m_pad220[2];
	bool m_forceModelsToFollowTimeOfDay;
	bool m_forceModelsToFollowWeather;
};

extern GlobalData *TheWritableGlobalData;

// Retail stores this BFME-only 29-entry table at VA 0x010A15C0.
static const ModelConditionFlagType TheWeaponSetTypeToModelConditionTypeMap[29] =
{
	MODELCONDITION_WEAPONSET_VETERAN,
	MODELCONDITION_WEAPONSET_ELITE,
	MODELCONDITION_WEAPONSET_HERO,
	MODELCONDITION_WEAPONSET_PLAYER_UPGRADE,
	MODELCONDITION_WEAPONSET_CRATEUPGRADE_ONE,
	MODELCONDITION_WEAPONSET_CRATEUPGRADE_TWO,
	(ModelConditionFlagType)135, (ModelConditionFlagType)149,
	(ModelConditionFlagType)151, (ModelConditionFlagType)182,
	(ModelConditionFlagType)218, (ModelConditionFlagType)219,
	(ModelConditionFlagType)220, (ModelConditionFlagType)221,
	(ModelConditionFlagType)222, (ModelConditionFlagType)223,
	(ModelConditionFlagType)224, (ModelConditionFlagType)225,
	(ModelConditionFlagType)226, (ModelConditionFlagType)227,
	(ModelConditionFlagType)230, (ModelConditionFlagType)236,
	(ModelConditionFlagType)239, (ModelConditionFlagType)240,
	(ModelConditionFlagType)268, (ModelConditionFlagType)269,
	(ModelConditionFlagType)270, (ModelConditionFlagType)271,
	(ModelConditionFlagType)242
};

class Object
{
public:
	virtual void slot00();

	void friend_bindToDrawable(Drawable *draw);

private:
	unsigned char m_pad004[0x80 - 4];
	Drawable *m_drawable;
	unsigned char m_pad084[0x110 - 0x84];
	ModelConditionFlags m_conditionFlags;
	unsigned char m_pad138[0x1f0 - 0x138];
	BehaviorModule **m_behaviors;
	unsigned char m_pad1f4[0x204 - 0x1f4];
	BfmeUpdVKP *m_ai;
	unsigned char m_pad208[0x29c - 0x208];
	UnsignedInt m_curWeaponSetFlags;
};

// ?friend_bindToDrawable@Object@@QAEXPAVDrawable@@@Z
void Object::friend_bindToDrawable(Drawable *draw)
{
	m_drawable = draw;
	if (m_drawable)
	{
		ModelConditionFlags set = {};
		ModelConditionFlags clr = {};
		for (int i = 0; i < 29; ++i)
		{
			ModelConditionFlagType mcs = TheWeaponSetTypeToModelConditionTypeMap[i];
			if (mcs != MODELCONDITION_INVALID)
			{
				if ((m_curWeaponSetFlags & (1 << (i & 31))) != 0)
					set.set(mcs);
				else
					clr.set(mcs);
			}
		}

		GlobalData *global = TheWritableGlobalData;
		if (global)
		{
			if (global->m_forceModelsToFollowTimeOfDay)
				set.set(MODELCONDITION_NIGHT, global->m_timeOfDay == 4);

			if (global->m_forceModelsToFollowWeather)
				set.set(MODELCONDITION_SNOW, global->m_weather == 1);
		}

		ModelConditionFlags old = m_conditionFlags;
		m_conditionFlags.clearAndSet(clr, set);
		if (old != m_conditionFlags)
		{
			if (m_drawable)
				m_drawable->replaceModelConditionState(m_conditionFlags, false, 0);

			if (m_ai)
				m_ai->bfmeUpdateVKP();
		}
	}

	for (BehaviorModule **b = m_behaviors; *b; ++b)
		(*b)->onDrawableBoundToObject();
}

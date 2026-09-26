// Address-derived candidate for the unclaimed 0x002A7DB0 SpecialAbilityUpdate
// predicate.  Its first lookup and override walk are shared with the adjacent
// getSpecialObjectMax/apply bodies.

typedef unsigned int UnsignedInt;
typedef bool Bool;

enum SpecialPowerType { SPECIAL_POWER_TYPE_27 = 0x27 };
enum KindOfType { KINDOF_6 = 6 };

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();
	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_08[0x14 - 8];
	SpecialPowerType m_specialPowerType;
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class KindObjectA : public Thing
{
};

class KindObjectB : public Thing
{
};

class Object : public Thing
{
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x1D8];
	const SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_unmodelled_1DC[0x210 - 0x1DC];
	volatile UnsignedInt m_maxSpecialObjects;
};

struct Rva002A7DB0Fields
{
	unsigned int m_unmodelled_00;
	const SpecialAbilityUpdateModuleData *m_moduleData;
	unsigned char m_unmodelled_08[0x24 - 8];
	volatile int m_field24;
	unsigned char m_unmodelled_28[0xAC - 0x28];
	int m_targetID;
};

class ModuleMaxA
{
public:
	unsigned char m_unmodelled_000[0x210];
	volatile UnsignedInt m_maxSpecialObjects;
};

class ModuleMaxB
{
public:
	unsigned char m_unmodelled_000[0x210];
	volatile UnsignedInt m_maxSpecialObjects;
};

class ModuleMaxC
{
public:
	unsigned char m_unmodelled_000[0x210];
	volatile UnsignedInt m_maxSpecialObjects;
};

class Rva002A7DB0
{
public:
	Bool check() const;
	const SpecialAbilityUpdateModuleData *getModuleData() const
	{
		return m_moduleData;
	}

private:
	unsigned int m_unmodelled_00;
	const SpecialAbilityUpdateModuleData *m_moduleData;
	unsigned char m_unmodelled_08[0x24 - 8];
	volatile int m_field24;
	unsigned char m_unmodelled_28[0xAC - 0x28];
	int m_targetID;
};

// ?check@Rva002A7DB0@@QBE_NXZ
Bool Rva002A7DB0::check() const
{
	const Rva002A7DB0Fields *fields =
		(const Rva002A7DB0Fields *)this;
	Object *target;
	const SpecialAbilityUpdateModuleData *md = fields->m_moduleData;
	const SpecialPowerTemplate *tmpl = md->m_specialPowerTemplate;
	target = TheGameLogic->findObjectByID(fields->m_targetID);

	Overridable *o = tmpl->m_nextOverride;
	if (o)
	{
		if (o->m_nextOverride)
			o = o->m_nextOverride->friend_getFinalOverride();
		tmpl = (const SpecialPowerTemplate *)o;
	}

	if (tmpl->m_specialPowerType != SPECIAL_POWER_TYPE_27)
		goto normal_result;
	goto special_power;

normal_result:
	return ((const ModuleMaxA *)md)->m_maxSpecialObjects > 0;

special_power:
	if (!target)
		goto null_target;
	goto target_present;

null_target:
	if (fields->m_field24 > 1)
		goto false_result;
	return ((const ModuleMaxB *)md)->m_maxSpecialObjects > 0;

target_present:
	if (((KindObjectA *)target)->isKindOf(KINDOF_6))
		goto test_count;
	if (((KindObjectB *)target)->isKindOf(KINDOF_6))
		goto test_count;
	goto false_result;

test_count:
	if (fields->m_field24 > 1)
		goto false_result;
	return ((const ModuleMaxC *)md)->m_maxSpecialObjects > 0;

false_result:
	return false;
}

// ?onDamage@ReflectDamage@@UAEXPAUBFMEDamageInfo@@@Z
// ReflectDamage's callback at retail RVA 0x002518B0.

typedef int Int;
typedef float Real;

enum DamageType
{
	DAMAGE_DEPLOY = 13
};

enum DeathType
{
	DEATH_CRUSHED = 2
};

struct DamageInfoInput
{
	unsigned char m_unreconstructed_00[8];
	Int m_sourceObject;
	unsigned char m_unreconstructed_0c[4];
	DamageType m_damageType;
	Int m_unreconstructed_14;
	DeathType m_deathType;
	Real m_amount;
	unsigned char m_kill;
};

struct BFMEDamageInfo
{
	BFMEDamageInfo();
	DamageInfoInput in;
	unsigned char m_unreconstructed_24[0x5c - 0x24];
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void attemptDamage(BFMEDamageInfo *damageInfo);

private:
	unsigned char m_unreconstructed_04[0x70];

public:
	Int m_id;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

struct ReflectDamageModuleData
{
	unsigned char m_unreconstructed_00[8];
	unsigned m_damageTypes;
	Real m_reflectDamagePercentage;
	Real m_reflectDamageMinimum;
};

class ReflectDamage
{
public:
	virtual void onDamage(BFMEDamageInfo *damageInfo);
};

#define TheGameLogic (*(GameLogic **)0x012F0898)

void ReflectDamage::onDamage(BFMEDamageInfo *damageInfo)
{
	ReflectDamageModuleData *moduleData =
		*(ReflectDamageModuleData **)((char *)this - 0x0c);
	if (damageInfo->in.m_damageType == DAMAGE_DEPLOY)
		return;

	if ((moduleData->m_damageTypes &
		(1 << ((unsigned)damageInfo->in.m_damageType - 1))) == 0)
		return;

	if (Object *source = TheGameLogic->findObjectByID(
		damageInfo->in.m_sourceObject))
	{
		BFMEDamageInfo reflected;
		Real amount =
			moduleData->m_reflectDamagePercentage * damageInfo->in.m_amount;
		reflected.in.m_unreconstructed_14 = 2;
		reflected.in.m_deathType = DEATH_CRUSHED;
		reflected.in.m_damageType = DAMAGE_DEPLOY;
		reflected.in.m_sourceObject = *(volatile Int *)
			((char *)*(Object *volatile *)((char *)this - 0x08) + 0x74);
		if (!(amount > moduleData->m_reflectDamageMinimum))
			amount = moduleData->m_reflectDamageMinimum;
		reflected.in.m_amount = amount;
		source->attemptDamage(&reflected);
	}
}

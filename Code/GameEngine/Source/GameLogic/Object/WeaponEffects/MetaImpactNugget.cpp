// cl: /DNDEBUG /MD /EHsc
// Open-BFME: MetaImpactNugget::execute, retail 0x002DDA40, 326 bytes.
//
// Identity: Made001E5F00 vtable 0x010CEFA4 slot 13 (+0x34) thunks here via
// j_0000beba, the ctor at 0x002DDBE0 installs that vtable, parseMetaImpactNugget
// allocates the class, and this body passes the source-path string
// F:\bfme\Code\gameengine\Source\GameLogic\Object\WeaponEffects\MetaImpactNugget.cpp
// to GetGameLogicRandomValueReal.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum KindOfType
{
	KINDOF_META_59 = 0x59,
	KINDOF_META_6C = 0x6C
};

class Object;
class Weapon;
class DamageInfo;

class Thing
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void attemptDamage(DamageInfo *info);

	Bool isKindOf(KindOfType kind) const;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;
extern const Real BfmeZeroRange;

Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);

class DamageInfo
{
public:
	DamageInfo();

private:
	unsigned char m_bytes[0x5C];
};

class BFMEReportDamageSource
{
public:
	void report(Object *victim, Int flag);
};

class MetaModuleA
{
public:
	virtual MetaModuleA *vslot00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void vslot34(void *arg);
};

class MetaModule
{
public:
	virtual MetaModuleA *vslot00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5c();
	virtual void v60();
	virtual void v64();
	virtual void *vslot68(Object *victim);
};

class Object : public Thing
{
public:
	Bool getAttributeModifierBonus(Int which, Real *value) const;

	unsigned char m_pad04[0x94 - 4];
	unsigned char m_status94;
	unsigned char m_pad95[0x1FC - 0x95];
	MetaModule *m_contain;
	unsigned char m_pad200[0x214 - 0x200];
	Object *m_214;
};

class Weapon
{
public:
	virtual void unused();
	unsigned char m_pad04[4];
	Int m_ownerID;
};

class MetaImpactNugget
{
public:
	virtual ~MetaImpactNugget();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual unsigned char fillDamage(Weapon *weapon, Object *victim, DamageInfo *info);
	void execute(Weapon *weapon, Object *victim);

	unsigned char m_pad04[0x78 - 4];
	Real m_chance78;
};

static char kMetaImpactFile[] =
	"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\WeaponEffects\\MetaImpactNugget.cpp";

// ?execute@MetaImpactNugget@@QAEXPAVWeapon@@PAVObject@@@Z
void MetaImpactNugget::execute(Weapon *weapon, Object *victim)
{
	MetaImpactNugget *self = this;
	if (!weapon)
		return;
	if (!victim)
		return;

	Real bonus;
	victim->getAttributeModifierBonus(9, &bonus);
	if (bonus > BfmeZeroRange)
	{
		if (!(GetGameLogicRandomValueReal(0.0f, 0.999f, kMetaImpactFile, 344) > bonus))
			return;
	}

	if (victim->isKindOf(KINDOF_META_59))
	{
		if (GetGameLogicRandomValueReal(0.0f, 0.999f, kMetaImpactFile, 353) < self->m_chance78)
			return;
	}

	Object *outer = victim->m_214;
	if ((victim->m_status94 & 0x20) != 0)
	{
		if (outer && outer->m_214 && outer->isKindOf(KINDOF_META_6C))
		{
			MetaModule *mod = outer->m_214->m_contain;
			if (!mod)
				return;

			Object *source = TheGameLogic->findObjectByID(weapon->m_ownerID);
			if (source)
				((BFMEReportDamageSource *)source)->report(victim, 1);

			MetaModuleA *iface = mod->vslot00();
			iface->vslot34(mod->vslot68(victim));
			return;
		}
	}

	DamageInfo info;
	if (self->fillDamage(weapon, victim, &info) == 1)
	{
		DamageInfo *pInfo = &info;
		victim->attemptDamage(pInfo);
	}
}

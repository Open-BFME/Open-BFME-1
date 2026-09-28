// cl: /DNDEBUG /MD /EHsc

typedef float Real;
typedef bool Bool;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D;
class WeaponTemplate;

class DamageInfo
{
public:
	unsigned char m_unmodelled_000[0x10];
	Int m_damageType;
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual const DamageInfo *getLastDamageInfo() const;
};

class Object
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *reinterpret_cast<BodyModuleInterface *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x200);
	}

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const unsigned char *>(this) + 0x38);
	}
};

class FXList
{
public:
	Bool isEmpty() const;
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primarySpeed, const Coord3D *secondary) const;
};

class StructureToppleUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x48];
	unsigned int m_damageFXTypes;
	unsigned char m_unmodelled_04c[0x10];
	FXList *m_crushingFXList;
};

enum StructureTopplePhaseType
{
	STPHASE_DELAY,
	STPHASE_INITIAL,
	STPHASE_FINAL
};

class StructureToppleUpdate
{
protected:
	virtual ~StructureToppleUpdate();
	void doDamageLine(Object *building, const WeaponTemplate *wt,
		Real jcos, Real jsin, Real facingWidth, Real toppleAngle);
	void doPhaseStuff(StructureTopplePhaseType stphase, const Coord3D *target);
	StructureToppleUpdateModuleData *m_moduleData;
	Object *m_object;

	const StructureToppleUpdateModuleData *getModuleData() const
	{
		return m_moduleData;
	}

	Object *getObject()
	{
		return m_object;
	}
};

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *weapon,
		const Object *source, const Coord3D *position);
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
};

extern WeaponStore *TheWeaponStore;
extern TerrainLogic *TheTerrainLogic;

Real Sin(Real angle);
Real Cos(Real angle);

static __forceinline Bool getDamageTypeFlag(unsigned int flags, Int damageType)
{
	return (flags & (1u << (damageType - 1))) != 0;
}

// ?doDamageLine@StructureToppleUpdate@@IAEXPAVObject@@PBVWeaponTemplate@@MMMM@Z
void StructureToppleUpdate::doDamageLine(Object *building, const WeaponTemplate *wt,
	Real jcos, Real jsin, Real facingWidth, Real toppleAngle)
{
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();
	static const Real WEAPON_SPACING_PARALLEL = 25;
	const StructureToppleUpdateModuleData *d = getModuleData();
	Coord3D target;

	for (Real i = -facingWidth; i < facingWidth; i += WEAPON_SPACING_PARALLEL)
	{
		target.x = building->getPosition()->x + jcos + (i * Sin(toppleAngle));
		target.y = building->getPosition()->y + jsin + (i * Cos(toppleAngle));
		target.z = TheTerrainLogic->getGroundHeight(target.x, target.y);

		TheWeaponStore->createAndFireTempWeapon(wt, building, &target);

		if (lastDamageInfo == 0 ||
			getDamageTypeFlag(d->m_damageFXTypes, lastDamageInfo->m_damageType))
		{
			FXList *crushingFX = d->m_crushingFXList;
			if (crushingFX != 0 && !crushingFX->isEmpty())
				crushingFX->doFXPos(&target, 0, 0.0f, 0);
		}
	}

	target.x = building->getPosition()->x + jcos + (facingWidth * Sin(toppleAngle));
	target.y = building->getPosition()->y + jsin + (facingWidth * Cos(toppleAngle));
	target.z = TheTerrainLogic->getGroundHeight(target.x, target.y);
	TheWeaponStore->createAndFireTempWeapon(wt, building, &target);

	if (lastDamageInfo == 0 ||
		getDamageTypeFlag(d->m_damageFXTypes, lastDamageInfo->m_damageType))
	{
		FXList *crushingFX = d->m_crushingFXList;
		if (crushingFX != 0 && !crushingFX->isEmpty())
			crushingFX->doFXPos(&target, 0, 0.0f, 0);
	}

	target.x = building->getPosition()->x + jcos;
	target.y = building->getPosition()->y + jsin;
	target.z = TheTerrainLogic->getGroundHeight(target.x, target.y);
	doPhaseStuff(STPHASE_FINAL, &target);
}

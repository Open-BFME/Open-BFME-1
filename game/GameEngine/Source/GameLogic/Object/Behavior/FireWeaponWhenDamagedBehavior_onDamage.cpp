// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum DamageType
{
	DAMAGE_EXPLOSION = 0
};

struct DamageInfoInput
{
	unsigned char m_unreconstructed_000[0x10];
	DamageType m_damageType;
	unsigned char m_unreconstructed_014[0x3c];
};

struct DamageInfoOutput
{
	float m_actualDamageDealt;
};

class DamageInfo
{
public:
	DamageInfoInput in;
	DamageInfoOutput out;
};

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

enum WeaponStatus
{
	READY_TO_FIRE
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	Object *forceFireWeapon(const Object *source, const Coord3D *position);
};

class FireWeaponWhenDamagedBehaviorModuleData
{
public:
	unsigned char m_unreconstructed_000[0x74];
	unsigned int m_damageTypes;
	float m_damageAmount;
};

class FireWeaponWhenDamagedBehavior
{
public:
	virtual void onDamage(DamageInfo *damageInfo);

	Weapon *m_reactionWeaponPristine;
	Weapon *m_reactionWeaponDamaged;
	Weapon *m_reactionWeaponReallyDamaged;
	Weapon *m_reactionWeaponRubble;
};

class BfmeFireWeaponUpgradeMux
{
public:
	virtual bool isAlreadyUpgraded() const = 0;
};

class BfmeFireWeaponBodyModule
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual BodyDamageType getDamageState() = 0;
};

struct BfmeFireWeaponObjectBody
{
	unsigned char m_unreconstructed_000[0x200];
	BfmeFireWeaponBodyModule *m_body;
};

// ?onDamage@FireWeaponWhenDamagedBehavior@@UAEXPAVDamageInfo@@@Z
void FireWeaponWhenDamagedBehavior::onDamage(DamageInfo *damageInfo)
{
	const char *self = reinterpret_cast<const char *>(this);
	const BfmeFireWeaponUpgradeMux *upgrade = reinterpret_cast<const BfmeFireWeaponUpgradeMux *>(self - 8);
	if (!upgrade->isAlreadyUpgraded())
		return;

	const FireWeaponWhenDamagedBehaviorModuleData *data =
		*reinterpret_cast<const FireWeaponWhenDamagedBehaviorModuleData *const *>(self - 0x24);
	if (!(data->m_damageTypes & (1U << (damageInfo->in.m_damageType - 1))))
		return;
	if (damageInfo->out.m_actualDamageDealt < data->m_damageAmount)
		return;

	const Object *obj = *reinterpret_cast<const Object *const *>(self - 0x20);
	BfmeFireWeaponBodyModule *body =
		reinterpret_cast<const BfmeFireWeaponObjectBody *>(obj)->m_body;
	BodyDamageType damageState = body->getDamageState();

	if (damageState == BODY_RUBBLE)
	{
		if (m_reactionWeaponRubble && m_reactionWeaponRubble->getStatus() == READY_TO_FIRE)
			m_reactionWeaponRubble->forceFireWeapon(obj, obj->getPosition());
	}
	else if (damageState == BODY_REALLYDAMAGED)
	{
		if (m_reactionWeaponReallyDamaged && m_reactionWeaponReallyDamaged->getStatus() == READY_TO_FIRE)
			m_reactionWeaponReallyDamaged->forceFireWeapon(obj, obj->getPosition());
	}
	else if (damageState == BODY_DAMAGED)
	{
		if (m_reactionWeaponDamaged && m_reactionWeaponDamaged->getStatus() == READY_TO_FIRE)
			m_reactionWeaponDamaged->forceFireWeapon(obj, obj->getPosition());
	}
	else
	{
		if (m_reactionWeaponPristine && m_reactionWeaponPristine->getStatus() == READY_TO_FIRE)
			m_reactionWeaponPristine->forceFireWeapon(obj, obj->getPosition());
	}
}

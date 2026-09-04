// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
// stlport
// WeaponTemplate::shouldProjectileCollideWith, retail 0x001E63A0 size 428.
// ZH twin in Weapon.cpp. BFME adds NEUTRAL collide bit 4, extra kind 0x0A,
// controlled-structure bit 0x200, and a kind 0x3B / getLayer>1 reject.
// Airfield parking-place walk is gone. Burned check goes through
// bfmeAllowsRelationship(6, launcher->find(0)) then testStatus(0xB).
// handle() at 0x001F08B0 calls this as its last thiscall (ILT 0x00048D06).

typedef bool Bool;
typedef int Int;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum KindOfType
{
	KINDOF_SHRUBBERY = 0x06,
	KINDOF_STRUCTURE = 0x07,
	KINDOF_0A = 0x0A,
	KINDOF_PROJECTILE = 0x19,
	KINDOF_SMALL_MISSILE = 0x33,
	KINDOF_LAYERED = 0x3B,
	KINDOF_BALLISTIC_MISSILE = 0x4A
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BURNED = 0x0B
};

enum WeaponCollideMaskType
{
	WEAPON_COLLIDE_ALLIES = 0x0001,
	WEAPON_COLLIDE_ENEMIES = 0x0002,
	WEAPON_COLLIDE_NEUTRAL = 0x0004,
	WEAPON_COLLIDE_STRUCTURES = 0x0008,
	WEAPON_COLLIDE_SHRUBBERY = 0x0010,
	WEAPON_COLLIDE_PROJECTILE = 0x0020,
	WEAPON_COLLIDE_WALLS = 0x0040,
	WEAPON_COLLIDE_SMALL_MISSILES = 0x0080,
	WEAPON_COLLIDE_BALLISTIC_MISSILES = 0x0100,
	WEAPON_COLLIDE_CONTROLLED_STRUCTURES = 0x0200,
	WEAPON_COLLIDE_0A = 0x0400
};

class AIUpdateInterface
{
public:
#define AI_PAD(n) virtual int pad_##n()
	AI_PAD(0); AI_PAD(1); AI_PAD(2); AI_PAD(3); AI_PAD(4); AI_PAD(5); AI_PAD(6); AI_PAD(7);
	AI_PAD(8); AI_PAD(9); AI_PAD(10); AI_PAD(11); AI_PAD(12); AI_PAD(13); AI_PAD(14); AI_PAD(15);
	AI_PAD(16); AI_PAD(17); AI_PAD(18); AI_PAD(19); AI_PAD(20); AI_PAD(21); AI_PAD(22); AI_PAD(23);
	AI_PAD(24); AI_PAD(25); AI_PAD(26); AI_PAD(27); AI_PAD(28); AI_PAD(29); AI_PAD(30); AI_PAD(31);
	AI_PAD(32); AI_PAD(33); AI_PAD(34); AI_PAD(35); AI_PAD(36); AI_PAD(37); AI_PAD(38); AI_PAD(39);
	AI_PAD(40); AI_PAD(41); AI_PAD(42); AI_PAD(43); AI_PAD(44); AI_PAD(45); AI_PAD(46); AI_PAD(47);
	AI_PAD(48); AI_PAD(49); AI_PAD(50); AI_PAD(51); AI_PAD(52); AI_PAD(53); AI_PAD(54); AI_PAD(55);
	AI_PAD(56); AI_PAD(57); AI_PAD(58); AI_PAD(59); AI_PAD(60); AI_PAD(61); AI_PAD(62); AI_PAD(63);
	AI_PAD(64); AI_PAD(65); AI_PAD(66); AI_PAD(67); AI_PAD(68); AI_PAD(69); AI_PAD(70); AI_PAD(71);
	AI_PAD(72); AI_PAD(73); AI_PAD(74); AI_PAD(75); AI_PAD(76); AI_PAD(77); AI_PAD(78); AI_PAD(79);
	AI_PAD(80); AI_PAD(81); AI_PAD(82); AI_PAD(83); AI_PAD(84); AI_PAD(85); AI_PAD(86); AI_PAD(87);
	AI_PAD(88); AI_PAD(89); AI_PAD(90); AI_PAD(91); AI_PAD(92); AI_PAD(93); AI_PAD(94); AI_PAD(95);
	AI_PAD(96); AI_PAD(97); AI_PAD(98); AI_PAD(99); AI_PAD(100); AI_PAD(101); AI_PAD(102); AI_PAD(103);
	AI_PAD(104); AI_PAD(105); AI_PAD(106); AI_PAD(107); AI_PAD(108); AI_PAD(109); AI_PAD(110); AI_PAD(111);
	AI_PAD(112); AI_PAD(113);
#undef AI_PAD
	virtual Bool getSneakyTargetingOffset(void *offset);
};

class Player;

class ThingTemplate
{
public:
	ThingTemplate *getFinalOverride();

	char m_pad00[4];
	ThingTemplate *m_overridable;
	char m_pad08[0x398 - 8];
	float m_fenceWidth;
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;

	char m_pad00[4];
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	void *find(Int key);
	Relationship getRelationship(const Object *that) const;
	Player *getControllingPlayer() const;
	Bool testStatus(Int status) const;
	Int getLayer() const;

	char m_pad08[0x74 - 8];
	ObjectID m_id;
	char m_pad78[0x204 - 0x78];
	AIUpdateInterface *m_ai;
	char m_pad208[0x214 - 0x208];
	Object *m_containedBy;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class WeaponTemplate
{
public:
	Bool bfmeAllowsRelationship(Int kind, void *entry) const;
	Bool shouldProjectileCollideWith(
		const Object *projectileLauncher,
		const Object *projectile,
		const Object *thingWeCollidedWith,
		ObjectID intendedVictimID) const;

	char m_pad00[0x4E0];
	unsigned m_projectileCollideMask;
};

// ?shouldProjectileCollideWith@WeaponTemplate@@QBE_NPBVObject@@00W4ObjectID@@@Z
Bool WeaponTemplate::shouldProjectileCollideWith(
	const Object *projectileLauncher,
	const Object *projectile,
	const Object *thingWeCollidedWith,
	ObjectID intendedVictimID) const
{
	const Object *proj = projectile;
	const Object *vic = thingWeCollidedWith;
	const WeaponTemplate *self = this;
	if (!proj || !vic)
		return false;

	if (intendedVictimID == vic->m_id)
		return true;

	if (projectileLauncher)
	{
		if (projectileLauncher == vic)
			return false;
		if (projectileLauncher->m_containedBy == vic)
			return false;
		if (self->bfmeAllowsRelationship(6, const_cast<Object *>(projectileLauncher)->find(0)))
		{
			if (vic->testStatus(OBJECT_STATUS_BURNED))
				return false;
		}
	}

	AIUpdateInterface *ai = vic->m_ai;
	if (ai && ai->getSneakyTargetingOffset(0))
		return false;

	Int requiredMask = 0;
	Relationship r = proj->getRelationship(vic);
	if (r == ALLIES)
		requiredMask = WEAPON_COLLIDE_ALLIES;
	else if (r == ENEMIES)
		requiredMask = WEAPON_COLLIDE_ENEMIES;
	else if (r == NEUTRAL)
		requiredMask = WEAPON_COLLIDE_NEUTRAL;

	if (vic->isKindOf(KINDOF_STRUCTURE))
	{
		Player *projPlayer = proj->getControllingPlayer();
		Player *vicPlayer = vic->getControllingPlayer();
		if (vicPlayer == projPlayer)
			requiredMask |= WEAPON_COLLIDE_CONTROLLED_STRUCTURES;
		else
			requiredMask |= WEAPON_COLLIDE_STRUCTURES;
	}
	if (vic->isKindOf(KINDOF_SHRUBBERY))
		requiredMask |= WEAPON_COLLIDE_SHRUBBERY;
	if (vic->isKindOf(KINDOF_PROJECTILE))
		requiredMask |= WEAPON_COLLIDE_PROJECTILE;

	ThingTemplate *tmpl = vic->m_template;
	if (tmpl)
	{
		ThingTemplate *ovr = tmpl->m_overridable;
		if (ovr)
			tmpl = ovr->getFinalOverride();
	}
	if (tmpl->m_fenceWidth > 0.0f)
		requiredMask |= WEAPON_COLLIDE_WALLS;

	if (vic->isKindOf(KINDOF_SMALL_MISSILE))
		requiredMask |= WEAPON_COLLIDE_SMALL_MISSILES;
	if (vic->isKindOf(KINDOF_BALLISTIC_MISSILE))
		requiredMask |= WEAPON_COLLIDE_BALLISTIC_MISSILES;
	if (vic->isKindOf(KINDOF_0A))
		requiredMask |= WEAPON_COLLIDE_0A;

	if ((self->m_projectileCollideMask & requiredMask) == 0)
		return false;

	if (vic->isKindOf(KINDOF_LAYERED) && intendedVictimID)
	{
		Object *found = TheGameLogic->findObjectByID(intendedVictimID);
		if (found && found->getLayer() > 1)
			return false;
	}
	return true;
}

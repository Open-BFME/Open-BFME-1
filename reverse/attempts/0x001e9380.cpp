// ?d_001e9380@@YAXXZ
// partial score=0.18 date=2026-09-18
// cl: /DNDEBUG /MD /O2 /EHs-c-
//
// Open-BFME5: anonymous retail body 0x001E9380, 1519 bytes.  The caller at
// 0x001E9FD0 supplies the legacy BFME ABI (eleven stack dwords): source,
// source position, slot, barrel, victim, victim id, aimed position, bonus,
// detonation flag, firing weapon and projectile id.  The address-derived
// method name is intentional: the caller proves this WeaponTemplate-shaped
// body, but does not prove the original source spelling.
//
// The layout witnesses are the matched WeaponTemplate copy/parse bodies.  In
// particular, the retail accesses below prove +0x31, +0x58, +0x74, +0x94,
// +0x4e4, +0x4fd, +0x514, +0x520, +0x524 and the nugget list head at +0x538.
// The final list walk is kept as the witnessed three-pointer STLport node;
// the nugget identity and the 0x00040287 helper remain address-derived.

#include <math.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef int ObjectID;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct WeaponBonus
{
	Real fields[6];
};

class Object;
class Weapon;
class WeaponTemplate;
class FXList;
class Drawable;

struct TBridgeAttackInfo
{
	Coord3D attackPoint1;
	Coord3D attackPoint2;
};

class BfmePt951
{
public:
	Real m_x;
	Real m_y;
};

class BfmeGap951
{
public:
	Real bfmeGapB951(const BfmePt951 *other) const;

private:
	Int m_pad00[14];
	Real m_x;
	Real m_y;
	Int m_pad40[31];
	Real m_radius;
};

class Gen_000ED3B0
{
public:
	Real bfmeGapSq(const Gen_000ED3B0 *other) const;

private:
	Int m_pad00[14];
	Real m_x;
	Real m_y;
	Int m_pad40[31];
	Real m_radius;
};

#define RVA_VIRTUAL_SLOT(n) virtual void v##n();

class AIUpdateInterfaceBase
{
public:
	RVA_VIRTUAL_SLOT(000)
	RVA_VIRTUAL_SLOT(001)
	RVA_VIRTUAL_SLOT(002)
	RVA_VIRTUAL_SLOT(003)
	RVA_VIRTUAL_SLOT(004)
	RVA_VIRTUAL_SLOT(005)
	RVA_VIRTUAL_SLOT(006)
	RVA_VIRTUAL_SLOT(007)
	RVA_VIRTUAL_SLOT(008)
	RVA_VIRTUAL_SLOT(009)
	RVA_VIRTUAL_SLOT(010)
	RVA_VIRTUAL_SLOT(011)
	RVA_VIRTUAL_SLOT(012)
	RVA_VIRTUAL_SLOT(013)
	RVA_VIRTUAL_SLOT(014)
	RVA_VIRTUAL_SLOT(015)
	RVA_VIRTUAL_SLOT(016)
	RVA_VIRTUAL_SLOT(017)
	RVA_VIRTUAL_SLOT(018)
	RVA_VIRTUAL_SLOT(019)
	RVA_VIRTUAL_SLOT(020)
	RVA_VIRTUAL_SLOT(021)
	RVA_VIRTUAL_SLOT(022)
	RVA_VIRTUAL_SLOT(023)
	RVA_VIRTUAL_SLOT(024)
	RVA_VIRTUAL_SLOT(025)
	RVA_VIRTUAL_SLOT(026)
	RVA_VIRTUAL_SLOT(027)
	RVA_VIRTUAL_SLOT(028)
	RVA_VIRTUAL_SLOT(029)
	RVA_VIRTUAL_SLOT(030)
	RVA_VIRTUAL_SLOT(031)
	RVA_VIRTUAL_SLOT(032)
	RVA_VIRTUAL_SLOT(033)
	RVA_VIRTUAL_SLOT(034)
	RVA_VIRTUAL_SLOT(035)
	RVA_VIRTUAL_SLOT(036)
	RVA_VIRTUAL_SLOT(037)
	RVA_VIRTUAL_SLOT(038)
	RVA_VIRTUAL_SLOT(039)
	RVA_VIRTUAL_SLOT(040)
	RVA_VIRTUAL_SLOT(041)
	RVA_VIRTUAL_SLOT(042)
	RVA_VIRTUAL_SLOT(043)
	RVA_VIRTUAL_SLOT(044)
	RVA_VIRTUAL_SLOT(045)
	RVA_VIRTUAL_SLOT(046)
	RVA_VIRTUAL_SLOT(047)
	RVA_VIRTUAL_SLOT(048)
	RVA_VIRTUAL_SLOT(049)
	RVA_VIRTUAL_SLOT(050)
	RVA_VIRTUAL_SLOT(051)
	RVA_VIRTUAL_SLOT(052)
	RVA_VIRTUAL_SLOT(053)
	RVA_VIRTUAL_SLOT(054)
	RVA_VIRTUAL_SLOT(055)
	RVA_VIRTUAL_SLOT(056)
	RVA_VIRTUAL_SLOT(057)
	RVA_VIRTUAL_SLOT(058)
	RVA_VIRTUAL_SLOT(059)
	RVA_VIRTUAL_SLOT(060)
	RVA_VIRTUAL_SLOT(061)
	RVA_VIRTUAL_SLOT(062)
	RVA_VIRTUAL_SLOT(063)
	RVA_VIRTUAL_SLOT(064)
	RVA_VIRTUAL_SLOT(065)
	RVA_VIRTUAL_SLOT(066)
	RVA_VIRTUAL_SLOT(067)
	RVA_VIRTUAL_SLOT(068)
	RVA_VIRTUAL_SLOT(069)
	RVA_VIRTUAL_SLOT(070)
	RVA_VIRTUAL_SLOT(071)
	RVA_VIRTUAL_SLOT(072)
	RVA_VIRTUAL_SLOT(073)
	RVA_VIRTUAL_SLOT(074)
	RVA_VIRTUAL_SLOT(075)
	RVA_VIRTUAL_SLOT(076)
	RVA_VIRTUAL_SLOT(077)
	RVA_VIRTUAL_SLOT(078)
	RVA_VIRTUAL_SLOT(079)
	RVA_VIRTUAL_SLOT(080)
	RVA_VIRTUAL_SLOT(081)
	RVA_VIRTUAL_SLOT(082)
	RVA_VIRTUAL_SLOT(083)
	RVA_VIRTUAL_SLOT(084)
	RVA_VIRTUAL_SLOT(085)
	RVA_VIRTUAL_SLOT(086)
	RVA_VIRTUAL_SLOT(087)
	RVA_VIRTUAL_SLOT(088)
	RVA_VIRTUAL_SLOT(089)
	RVA_VIRTUAL_SLOT(090)
	RVA_VIRTUAL_SLOT(091)
	RVA_VIRTUAL_SLOT(092)
	RVA_VIRTUAL_SLOT(093)
	RVA_VIRTUAL_SLOT(094)
	RVA_VIRTUAL_SLOT(095)
	RVA_VIRTUAL_SLOT(096)
	RVA_VIRTUAL_SLOT(097)
	RVA_VIRTUAL_SLOT(098)
	RVA_VIRTUAL_SLOT(099)
	RVA_VIRTUAL_SLOT(100)
	RVA_VIRTUAL_SLOT(101)
	RVA_VIRTUAL_SLOT(102)
	RVA_VIRTUAL_SLOT(103)
	RVA_VIRTUAL_SLOT(104)
	RVA_VIRTUAL_SLOT(105)
	RVA_VIRTUAL_SLOT(106)
	RVA_VIRTUAL_SLOT(107)
	RVA_VIRTUAL_SLOT(108)
	RVA_VIRTUAL_SLOT(109)
	RVA_VIRTUAL_SLOT(110)
	RVA_VIRTUAL_SLOT(111)
	RVA_VIRTUAL_SLOT(112)
	RVA_VIRTUAL_SLOT(113)
};

class AIUpdateInterface : public AIUpdateInterfaceBase
{
public:
	virtual Bool getSneakyTargetingOffset(Coord3D *offset);
};

class Rva001E9380Query1fcBase
{
public:
	RVA_VIRTUAL_SLOT(000)
	RVA_VIRTUAL_SLOT(001)
	RVA_VIRTUAL_SLOT(002)
	RVA_VIRTUAL_SLOT(003)
	RVA_VIRTUAL_SLOT(004)
	RVA_VIRTUAL_SLOT(005)
	RVA_VIRTUAL_SLOT(006)
	RVA_VIRTUAL_SLOT(007)
	RVA_VIRTUAL_SLOT(008)
	RVA_VIRTUAL_SLOT(009)
	RVA_VIRTUAL_SLOT(010)
	RVA_VIRTUAL_SLOT(011)
	RVA_VIRTUAL_SLOT(012)
	RVA_VIRTUAL_SLOT(013)
	RVA_VIRTUAL_SLOT(014)
	RVA_VIRTUAL_SLOT(015)
	RVA_VIRTUAL_SLOT(016)
	RVA_VIRTUAL_SLOT(017)
	RVA_VIRTUAL_SLOT(018)
	RVA_VIRTUAL_SLOT(019)
	RVA_VIRTUAL_SLOT(020)
	RVA_VIRTUAL_SLOT(021)
	RVA_VIRTUAL_SLOT(022)
	RVA_VIRTUAL_SLOT(023)
	RVA_VIRTUAL_SLOT(024)
	RVA_VIRTUAL_SLOT(025)
	virtual void *queryPassenger();
};

class Rva001E9380Query200Base
{
public:
	RVA_VIRTUAL_SLOT(000)
	RVA_VIRTUAL_SLOT(001)
	RVA_VIRTUAL_SLOT(002)
	RVA_VIRTUAL_SLOT(003)
	RVA_VIRTUAL_SLOT(004)
	RVA_VIRTUAL_SLOT(005)
	RVA_VIRTUAL_SLOT(006)
	RVA_VIRTUAL_SLOT(007)
	RVA_VIRTUAL_SLOT(008)
	RVA_VIRTUAL_SLOT(009)
	RVA_VIRTUAL_SLOT(010)
	RVA_VIRTUAL_SLOT(011)
	RVA_VIRTUAL_SLOT(012)
	RVA_VIRTUAL_SLOT(013)
	RVA_VIRTUAL_SLOT(014)
	RVA_VIRTUAL_SLOT(015)
	RVA_VIRTUAL_SLOT(016)
	RVA_VIRTUAL_SLOT(017)
	RVA_VIRTUAL_SLOT(018)
	RVA_VIRTUAL_SLOT(019)
	RVA_VIRTUAL_SLOT(020)
	RVA_VIRTUAL_SLOT(021)
	RVA_VIRTUAL_SLOT(022)
	RVA_VIRTUAL_SLOT(023)
	RVA_VIRTUAL_SLOT(024)
	RVA_VIRTUAL_SLOT(025)
	RVA_VIRTUAL_SLOT(026)
	RVA_VIRTUAL_SLOT(027)
	RVA_VIRTUAL_SLOT(028)
	RVA_VIRTUAL_SLOT(029)
	RVA_VIRTUAL_SLOT(030)
	RVA_VIRTUAL_SLOT(031)
	RVA_VIRTUAL_SLOT(032)
	RVA_VIRTUAL_SLOT(033)
	RVA_VIRTUAL_SLOT(034)
	virtual Real queryHeight();
};

#undef RVA_VIRTUAL_SLOT

class Object
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
	virtual Drawable *getDrawable() const;

	char m_pad04[0x34];
	Coord3D m_position;
	char m_pad44[0x1b8];
	Rva001E9380Query1fcBase *m_query1fc;
	Rva001E9380Query200Base *m_query200;
	AIUpdateInterface *m_ai;

	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}
};

class Drawable
{
public:
	Bool handleWeaponFireFX(Int wslot, Int barrel, const FXList *fx,
		Real weaponSpeed, Real recoilAmount, Real recoilAngle,
		const Coord3D *victimPos, Real damageRadius);
};

class TerrainLogic
{
public:
	void getBridgeAttackPoints(const Object *victim, TBridgeAttackInfo *info);
};

class Weapon
{
public:
	Real getAttackRange(const Object *source, Real heightDifference) const;
	Bool isGoalPosWithinAttackRange(const Object *source,
		const Coord3D *goalPos, const Object *target,
		const Coord3D *targetPos, Int extra) const;

	char m_pad00[0x30];
	UnsignedInt m_suspendFXFrame;
	char m_pad34[0x1c];
	UnsignedInt m_rangeFrame;
};

class Rva003D8BC0AIQuery
{
};

class BFMEObjectLocalQuery
{
};

class BFMEObjectStealthQuery
{
};

class Rva001E7C30Host
{
};

extern void j_00001c17();
extern void j_0001253f();
extern void j_000158b1();
extern void j_000204ff();
extern void j_0002cca5();
extern void j_0003251f();
extern void j_0003b1b();
extern void j_0003ce25();
extern void j_0003de7e();
extern void j_00040287();
extern void j_00043ced();
extern void j_0001ff91();

extern Real GetGameLogicRandomValueReal(Real low, Real high, char *file,
	Int line);
extern void bfmeLinkRelation(void *fx, Object *source, Int victim);

#define BFME_TERRAIN_LOGIC (*(TerrainLogic **)0x012EF4CC)
#define BFME_GAME_LOGIC_FRAME (*(UnsignedInt *)((char *)0x012F0898 + 0x3c))
#define BFME_AI (*(void **)0x012EF214)
#define BFME_ZERO_RANGE (*(const Real *)0x01075350)
#define BFME_DEFAULT_BU (*(const Real *)0x01075334)
#define BFME_RANDOM_FILE ((char *)0x010A1378)

static Real rva001e9380DistanceToPoint(const Object *source,
	const Coord3D *point)
{
	typedef Real (BfmeGap951::*Call)(const BfmePt951 *) const;
	union
	{
		void (*raw)();
		Call member;
	} route;
	route.raw = j_000158b1;
	return (reinterpret_cast<BfmeGap951 *>(const_cast<Object *>(source))->*
		route.member)(reinterpret_cast<const BfmePt951 *>(point));
}

static Real rva001e9380DistanceToObject(const Object *source,
	const Object *victim)
{
	typedef Real (Gen_000ED3B0::*Call)(const Gen_000ED3B0 *) const;
	union
	{
		void (*raw)();
		Call member;
	} route;
	route.raw = j_00043ced;
	return (reinterpret_cast<Gen_000ED3B0 *>(const_cast<Object *>(source))->*
		route.member)(reinterpret_cast<const Gen_000ED3B0 *>(victim));
}

static Bool rva001e9380IsKindOf(const Object *object, Int kind)
{
	typedef Bool (BFMEObjectLocalQuery::*Call)(Int);
	union
	{
		void (*raw)();
		Call member;
	} route;
	route.raw = j_0003251f;
	return (reinterpret_cast<BFMEObjectLocalQuery *>(const_cast<Object *>(object))->*
		route.member)(kind);
}

static Bool rva001e9380IsLocallyControlled(const Object *object)
{
	typedef Bool (BFMEObjectLocalQuery::*Call)();
	union
	{
		void (*raw)();
		Call member;
	} route;
	route.raw = j_0001ff91;
	return (reinterpret_cast<BFMEObjectLocalQuery *>(const_cast<Object *>(object))->*
		route.member)();
}

static Bool rva001e9380IsStealthedAndUndetected(const Object *object)
{
	typedef Bool (BFMEObjectStealthQuery::*Call)(Int);
	union
	{
		void (*raw)();
		Call member;
	} route;
	route.raw = j_0003b1b;
	return (reinterpret_cast<BFMEObjectStealthQuery *>(const_cast<Object *>(object))->*
		route.member)(0);
}

static Bool rva001e9380WallQuery(const Coord3D *position)
{
	typedef Bool (Rva003D8BC0AIQuery::*Call)(const Coord3D *, Int);
	union
	{
		void (*raw)();
		Call member;
	} route;
	route.raw = j_0003ce25;
	return (reinterpret_cast<Rva003D8BC0AIQuery *>(
		reinterpret_cast<char *>(BFME_AI) + 0x0c)->*route.member)(position, 0);
}

static Coord3D *rva001e9380BuildNuggetPosition(
	Rva001E7C30Host *host, const Object *source, const Object *victim,
	Coord3D *position)
{
	typedef Coord3D *(Rva001E7C30Host::*Call)(const Object *,
		const Object *, Coord3D *);
	union
	{
		void (*raw)();
		Call member;
	} route;
	route.raw = j_00040287;
	return (host->*route.member)(source, victim, position);
}

class Rva001E9380Node
{
public:
	Rva001E9380Node *m_next;
	Rva001E9380Node *m_previous;
	void *m_value;
};

class Rva001E9380Nugget
{
public:
	virtual void v00();
	virtual Bool v01(Weapon *weapon, Object *victim);
	virtual Bool v02(Weapon *weapon, const Coord3D *position);
	virtual void v03();
	virtual void v04();
	virtual void v05(Weapon *weapon, Object *victim);
	virtual void v06(Weapon *weapon, const Coord3D *position);
};

class WeaponTemplate
{
public:
	Coord3D *getAimPosition(Coord3D *out, const Object *source,
		const Object *victim, Int weaponSlot);
	Real getMinimumAttackRange() const;

	void rva001e9380(const Object *sourceObj, const Coord3D *sourcePos,
		Int wslot, Int specificBarrelToUse, Object *victimObj,
		ObjectID victimID, const Coord3D *victimPos,
		const WeaponBonus &bonus, Bool isProjectileDetonation,
		Weapon *firingWeapon, ObjectID *projectileID);

	void *m_vptr;
	unsigned char m_pad04[0x2c];
	unsigned char m_field30;
	unsigned char m_disableScatterForTargetsOnWall;
	unsigned char m_pad32[0x26];
	Real m_weaponSpeed;
	unsigned char m_pad5c[0x18];
	Real m_weaponRecoil;
	unsigned char m_pad78[0x1c];
	const FXList *m_fireFX;
	unsigned char m_pad98[0x4e4 - 0x98];
	unsigned char m_damageDealtAtSelfPosition;
	unsigned char m_pad4e5[0x4fd - 0x4e5];
	unsigned char m_playFXWhenStealthed;
	unsigned char m_pad4fe[0x514 - 0x4fe];
	Real m_infantryInaccuracyDist;
	unsigned char m_pad518[0x520 - 0x518];
	Real m_hitPercentage;
	Real m_hitPassengerPercentage;
	unsigned char m_pad528[0x538 - 0x528];
	Rva001E9380Node *m_nuggetList;
};

void WeaponTemplate::rva001e9380(const Object *sourceObj,
	const Coord3D *sourcePos, Int wslot, Int specificBarrelToUse,
	Object *victimObj, ObjectID victimID, const Coord3D *victimPos,
	const WeaponBonus &, Bool isProjectileDetonation,
	Weapon *firingWeapon, ObjectID *)
{
	register WeaponTemplate *self = this;
	if (sourceObj == 0 || (victimObj == 0 && victimPos == 0))
		return;

	Real distanceSquared;
	TBridgeAttackInfo bridge;
	Coord3D sneakyPosition;
	const Coord3D *targetPosition = victimPos;

	if (victimObj != 0)
	{
		targetPosition = &victimObj->m_position;
		Coord3D sneakyOffset;
		AIUpdateInterface *ai = victimObj->getAI();
		if (ai != 0)
		{
			if (ai->getSneakyTargetingOffset(&sneakyOffset))
			{
				sneakyPosition = *targetPosition;
				sneakyPosition.x += sneakyOffset.x;
				sneakyPosition.y += sneakyOffset.y;
				sneakyPosition.z += sneakyOffset.z;
				targetPosition = &sneakyPosition;
				victimObj = 0;
				distanceSquared = rva001e9380DistanceToPoint(sourceObj,
					targetPosition);
			}
		}

		if (victimObj != 0)
		{
			if (rva001e9380IsKindOf(victimObj, 0x16))
			{
				BFME_TERRAIN_LOGIC->getBridgeAttackPoints(victimObj, &bridge);
				Real first = rva001e9380DistanceToPoint(sourceObj,
					&bridge.attackPoint1);
				Real second = rva001e9380DistanceToPoint(sourceObj,
					&bridge.attackPoint2);
				distanceSquared = first;
				targetPosition = &bridge.attackPoint1;
				if (first > second)
				{
					distanceSquared = second;
					targetPosition = &bridge.attackPoint2;
				}
			}
			else
			{
				distanceSquared = rva001e9380DistanceToObject(sourceObj,
					victimObj);
			}
		}
	}
	else
	{
		distanceSquared = rva001e9380DistanceToPoint(sourceObj,
			targetPosition);
	}

	if (!isProjectileDetonation && firingWeapon != 0 &&
		firingWeapon->m_rangeFrame <= BFME_GAME_LOGIC_FRAME)
	{
		Real attackRange = firingWeapon->getAttackRange(sourceObj,
			targetPosition->z - sourceObj->m_position.z);
		if (distanceSquared > attackRange * attackRange)
			return;
		if (!firingWeapon->isGoalPosWithinAttackRange(sourceObj,
			&sourceObj->m_position, victimObj, targetPosition, 0))
			return;
		Real minimumRange = self->getMinimumAttackRange();
		if (distanceSquared < minimumRange * minimumRange)
			return;
	}

	Drawable *drawable = sourceObj->getDrawable();
	if (drawable != 0)
	{
		Coord3D aimPosition;
		if (victimObj != 0)
			self->getAimPosition(&aimPosition, sourceObj, victimObj, 1);
		else
			aimPosition = *targetPosition;

		Real recoilAngle = self->m_weaponRecoil;
		Real direction = BFME_ZERO_RANGE;
		if (recoilAngle != BFME_ZERO_RANGE)
			direction = (Real)atan2(targetPosition->y - sourceObj->m_position.y,
				targetPosition->x - sourceObj->m_position.x);

		const FXList *fx = self->m_fireFX;
		if (BFME_GAME_LOGIC_FRAME < firingWeapon->m_suspendFXFrame)
			fx = 0;

		Bool handled = false;
		if (!rva001e9380IsLocallyControlled(sourceObj) &&
			rva001e9380IsStealthedAndUndetected(sourceObj) &&
			!self->m_playFXWhenStealthed)
			handled = true;
		else
			handled = drawable->handleWeaponFireFX(wslot,
				specificBarrelToUse, fx, self->m_weaponSpeed, recoilAngle,
				direction, &aimPosition, BFME_ZERO_RANGE);

		if (!handled && fx != 0)
			bfmeLinkRelation((void *)fx, const_cast<Object *>(sourceObj),
				(Int)victimObj);
	}

	Coord3D damagePosition = *targetPosition;
	Bool applyScatter = false;
	Object *damageObject = victimObj;
	if (self->m_damageDealtAtSelfPosition)
	{
		damagePosition = sourceObj->m_position;
		damageObject = 0;
	}

	if (self->m_infantryInaccuracyDist > BFME_ZERO_RANGE && damageObject != 0 &&
		rva001e9380IsKindOf(damageObject, 8))
	{
		if (self->m_disableScatterForTargetsOnWall &&
			rva001e9380WallQuery(&damageObject->m_position))
		{
			applyScatter = false;
		}
		else if (self->m_hitPercentage < BFME_DEFAULT_BU &&
			GetGameLogicRandomValueReal(BFME_ZERO_RANGE, 1.0f,
				BFME_RANDOM_FILE, 0x536) > self->m_hitPercentage)
		{
			applyScatter = true;
		}
	}

	if (!applyScatter && damageObject != 0 &&
		self->m_hitPassengerPercentage > BFME_ZERO_RANGE)
	{
		Rva001E9380Query200Base *passengerQuery = damageObject->m_query200;
		if (passengerQuery != 0)
		{
			Real height = passengerQuery->queryHeight();
			if (height > BFME_ZERO_RANGE &&
				GetGameLogicRandomValueReal(BFME_ZERO_RANGE, 1.0f,
					BFME_RANDOM_FILE, 0x53c) < self->m_hitPassengerPercentage)
				applyScatter = true;
		}
	}

	if (!applyScatter && damageObject != 0)
	{
		Rva001E9380Query1fcBase *passenger = damageObject->m_query1fc;
		if (passenger != 0)
		{
			if (passenger->queryPassenger() == 0 && self->m_hitPassengerPercentage > BFME_ZERO_RANGE &&
				GetGameLogicRandomValueReal(BFME_ZERO_RANGE, 1.0f,
					BFME_RANDOM_FILE, 0x546) < self->m_hitPassengerPercentage)
				applyScatter = true;
		}
	}

	if (self->m_field30 && self->m_nuggetList != 0)
	{
		Rva001E9380Node *node = self->m_nuggetList->m_next;
		Coord3D nuggetPosition;
		while (node != self->m_nuggetList)
		{
			Rva001E9380Nugget *nugget =
				reinterpret_cast<Rva001E9380Nugget *>(node->m_value);
			if (nugget != 0)
			{
				if (applyScatter)
				{
					Coord3D *built = rva001e9380BuildNuggetPosition(
						reinterpret_cast<Rva001E7C30Host *>(nugget),
						sourceObj, damageObject, &nuggetPosition);
					if (built != 0)
						damagePosition = *built;
					if (nugget->v02(firingWeapon, &damagePosition))
						nugget->v06(firingWeapon, &damagePosition);
				}
				else if (damageObject != 0)
				{
					if (nugget->v01(firingWeapon, damageObject))
						nugget->v05(firingWeapon, damageObject);
				}
			}
			node = node->m_next;
		}
	}
}

// ?d_0018e660@@YAXXZ
// partial score=0.18 date=2026-09-25
// cl: /DNDEBUG /MD /EHs-c-
// Retail 0018E660 update with the BFME state and object offsets.

#include <math.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	float x;
	float y;
	float z;

	float length() const;
};

enum KindOfType
{
	KINDOF_IMMOBILE = 2,
	KINDOF_BRIDGE = 22
};

enum WeaponSlotType
{
	WEAPONSLOT_0 = 0
};

enum AbleToAttackType
{
	ATTACK_CONTINUED_TARGET = 2,
	ATTACK_CONTINUED_TARGET_FORCED = 3
};

enum CommandSourceType
{
	CMD_FROM_AI = 0
};

enum CanAttackResult
{
	ATTACKRESULT_POSSIBLE = 2,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 3
};

enum TurretTargetType
{
	TARGET_NONE,
	TARGET_OBJECT,
	TARGET_POSITION
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object;
class Team;
class StateMachine;

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
	float bfmeRelativeAngleTo(const Coord3D *position) const;

protected:
	void *m_vtable;
	void *m_template;
};

class Weapon;

class Object : public Thing
{
public:
	Bool isAbleToAttack() const;
	CanAttackResult getAbleToAttackSpecificObject(
		AbleToAttackType attackType, const Object *target,
		CommandSourceType commandSource) const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot);

	class AIUpdateInterface *getAIUpdateInterface()
	{
		return m_ai;
	}

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	Int getID() const
	{
		return m_id;
	}

	Team *getTeam() const
	{
		return m_team;
	}

	GeometryInfo *getGeometryInfo()
	{
		return reinterpret_cast<GeometryInfo *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0xac);
	}

private:
	char m_pad008[0x30];
	Coord3D m_position;
	char m_pad044[0x30];
	Int m_id;
	char m_pad078[0x18c];
	class AIUpdateInterface *m_ai;
	char m_pad208[0x34];
	Team *m_team;
};

class StateMachine
{
public:
	Object *getGoalObject();
};

class AIUpdateInterface
{
#define AI_EMPTY_SLOT(n) virtual void aiSlot##n();
	AI_EMPTY_SLOT(0) AI_EMPTY_SLOT(1) AI_EMPTY_SLOT(2) AI_EMPTY_SLOT(3)
	AI_EMPTY_SLOT(4) AI_EMPTY_SLOT(5) AI_EMPTY_SLOT(6) AI_EMPTY_SLOT(7)
	AI_EMPTY_SLOT(8) AI_EMPTY_SLOT(9) AI_EMPTY_SLOT(10) AI_EMPTY_SLOT(11)
	AI_EMPTY_SLOT(12) AI_EMPTY_SLOT(13) AI_EMPTY_SLOT(14) AI_EMPTY_SLOT(15)
	AI_EMPTY_SLOT(16) AI_EMPTY_SLOT(17) AI_EMPTY_SLOT(18) AI_EMPTY_SLOT(19)
	AI_EMPTY_SLOT(20) AI_EMPTY_SLOT(21) AI_EMPTY_SLOT(22) AI_EMPTY_SLOT(23)
	AI_EMPTY_SLOT(24) AI_EMPTY_SLOT(25) AI_EMPTY_SLOT(26) AI_EMPTY_SLOT(27)
	AI_EMPTY_SLOT(28) AI_EMPTY_SLOT(29) AI_EMPTY_SLOT(30) AI_EMPTY_SLOT(31)
	AI_EMPTY_SLOT(32) AI_EMPTY_SLOT(33) AI_EMPTY_SLOT(34) AI_EMPTY_SLOT(35)
	AI_EMPTY_SLOT(36) AI_EMPTY_SLOT(37) AI_EMPTY_SLOT(38) AI_EMPTY_SLOT(39)
	AI_EMPTY_SLOT(40) AI_EMPTY_SLOT(41) AI_EMPTY_SLOT(42) AI_EMPTY_SLOT(43)
	AI_EMPTY_SLOT(44) AI_EMPTY_SLOT(45) AI_EMPTY_SLOT(46) AI_EMPTY_SLOT(47)
	AI_EMPTY_SLOT(48) AI_EMPTY_SLOT(49) AI_EMPTY_SLOT(50) AI_EMPTY_SLOT(51)
	AI_EMPTY_SLOT(52) AI_EMPTY_SLOT(53) AI_EMPTY_SLOT(54) AI_EMPTY_SLOT(55)
	AI_EMPTY_SLOT(56) AI_EMPTY_SLOT(57) AI_EMPTY_SLOT(58) AI_EMPTY_SLOT(59)
	AI_EMPTY_SLOT(60) AI_EMPTY_SLOT(61) AI_EMPTY_SLOT(62) AI_EMPTY_SLOT(63)
	AI_EMPTY_SLOT(64) AI_EMPTY_SLOT(65) AI_EMPTY_SLOT(66) AI_EMPTY_SLOT(67)
	AI_EMPTY_SLOT(68) AI_EMPTY_SLOT(69) AI_EMPTY_SLOT(70) AI_EMPTY_SLOT(71)
	AI_EMPTY_SLOT(72) AI_EMPTY_SLOT(73) AI_EMPTY_SLOT(74) AI_EMPTY_SLOT(75)
	AI_EMPTY_SLOT(76) AI_EMPTY_SLOT(77) AI_EMPTY_SLOT(78) AI_EMPTY_SLOT(79)
	AI_EMPTY_SLOT(80) AI_EMPTY_SLOT(81) AI_EMPTY_SLOT(82) AI_EMPTY_SLOT(83)
	AI_EMPTY_SLOT(84) AI_EMPTY_SLOT(85) AI_EMPTY_SLOT(86) AI_EMPTY_SLOT(87)
	AI_EMPTY_SLOT(88) AI_EMPTY_SLOT(89) AI_EMPTY_SLOT(90) AI_EMPTY_SLOT(91)
	AI_EMPTY_SLOT(92) AI_EMPTY_SLOT(93) AI_EMPTY_SLOT(94) AI_EMPTY_SLOT(95)
	AI_EMPTY_SLOT(96) AI_EMPTY_SLOT(97) AI_EMPTY_SLOT(98) AI_EMPTY_SLOT(99)
	AI_EMPTY_SLOT(100) AI_EMPTY_SLOT(101) AI_EMPTY_SLOT(102) AI_EMPTY_SLOT(103)
	AI_EMPTY_SLOT(104) AI_EMPTY_SLOT(105) AI_EMPTY_SLOT(106) AI_EMPTY_SLOT(107)
	AI_EMPTY_SLOT(108) AI_EMPTY_SLOT(109) AI_EMPTY_SLOT(110) AI_EMPTY_SLOT(111)
	AI_EMPTY_SLOT(112) AI_EMPTY_SLOT(113) AI_EMPTY_SLOT(114)
#undef AI_EMPTY_SLOT
	public:

	virtual void addTargeter(Int id, Bool add);
	virtual Bool isTemporarilyPreventingAimSuccess() const;
	virtual void aiSlot117();
	virtual void aiSlot118();
	virtual void aiSlot119();
	virtual void aiSlot120();
	virtual void aiSlot121();
	virtual void aiSlot122();
	virtual Bool isDoingGroundMovement() const;
	virtual void aiSlot124();
	virtual void aiSlot125();
	virtual void aiSlot126();
	virtual void aiSlot127();
	virtual CommandSourceType getLastCommandSource() const;

	Object *getGoalObject() const
	{
		StateMachine *machine = *reinterpret_cast<StateMachine * const *>(
			reinterpret_cast<const char *>(this) + 0x30);
		return machine->getGoalObject();
	}
};

class TurretStateMachine
{
public:
	class TurretAI *getTurretAI() const
	{
		return *reinterpret_cast<class TurretAI * const *>(
			reinterpret_cast<const char *>(this) + 0x44);
	}

private:
	void *m_vtable;
	char m_pad004[0x40];
	class TurretAI *m_turretAI;
};

class TurretAIData
{
public:
	Real getSweep(WeaponSlotType slot) const
	{
		return reinterpret_cast<const Real *>(this)[4 + static_cast<Int>(slot)];
	}

	Real getFirePitch() const { return reinterpret_cast<const Real *>(this)[12]; }
	Real getMinPitch() const { return reinterpret_cast<const Real *>(this)[13]; }
	Real getGroundUnitPitch() const { return reinterpret_cast<const Real *>(this)[14]; }
	Bool allowsPitch() const
	{
		return *reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(this) + 0x56);
	}
};

class TurretAI
{
public:
	Object *getOwner()
	{
		return m_owner;
	}

	const TurretAIData *getData() const
	{
		return m_data;
	}

	Real getTurretAngle() const
	{
		return m_angle;
	}

	Bool isForceAttacking() const
	{
		return m_isForceAttacking;
	}

	Bool friend_getPositiveSweep() const
	{
		return m_positiveSweep;
	}

	void friend_setPositiveSweep(Bool positive)
	{
		m_positiveSweep = positive;
	}

	Bool friend_getTargetWasSetByIdleMood() const
	{
		return m_targetWasSetByIdleMood;
	}

	Team *friend_getVictimInitialTeam() const
	{
		return m_victimInitialTeam;
	}

	Bool friend_isSweepEnabled() const;
	Bool friend_turnTowardsAngle(Real angle, Real rate, Real threshold);
	Bool friend_turnTowardsPitch(Real pitch, Real rate);
	void setTurretTargetObject(Object *object, Bool forceAttacking);
	void apply(Object *object, Real angle);

private:
	void *m_vtable;
	char m_pad004[4];
	const TurretAIData *m_data;
	char m_pad00c[4];
	Object *m_owner;
	char m_pad014[4];
	Real m_angle;
	Real m_pitch;
	char m_pad020[0x74];
	Team *m_victimInitialTeam;
	char m_pad098[0x0e];
	Bool m_positiveSweep;
	char m_pad0a7[3];
	Bool m_isForceAttacking;
	Bool m_targetWasSetByIdleMood;
};

// The member call uses the target's two-argument stack shape; the body is the
// proven BFME float helper at 001E2AF0.
#pragma comment(linker, "/alternatename:?getAttackRange@Weapon@@QBEMPBVObject@@PBUCoord3D@@@Z=?bfmeGoEFCa@@YGXPAUBfmeAEFC@@PAUBfmeBEFC@@@Z")
class Weapon
{
public:
	Real getAttackRange(const Object *source, const Coord3D *position) const;
	Bool isWithinAttackRange(const Object *source, const Object *target, Int extra) const;
	Bool isWithinAttackRange(const Object *source, const Coord3D *position, Int extra) const;
};

#pragma comment(linker, "/alternatename:?apply@TurretAI@@QAEXPAVObject@@M@Z=?apply@Rva0018E210Owner@@SGXPAVObject@@M@Z")

class BFMETurretTargetAccessor
{
public:
	TurretTargetType friend_getTurretTarget(Object *&object, Coord3D &position) const;
};

class BfmeFourSlotOwner
{
public:
	Bool bfmeAnyAccepts(Int value);
};

struct TBridgeAttackInfo
{
	Coord3D attackPoint1;
	Coord3D attackPoint2;
};

class TerrainLogic
{
public:
	void getBridgeAttackPoints(const Object *bridge, TBridgeAttackInfo *info);
};

class BfmeBoundaryObject3D
{
public:
	Real bfmeBoundaryDistanceSquared3D(const Coord3D *first, const Coord3D *second) const;
};

class Gen_00148990
{
public:
	Coord3D bfmeDelta(const Coord3D *point) const;
};

extern TerrainLogic *TheTerrainLogic;
extern const Real BfmeZeroRange;
extern const Real g_bfmeK1253;
extern Real g_bfmeDefaultBU;
extern Real normalizeAngle(Real angle);
extern "C" Real __cdecl asinf(Real value);

class TurretAIAimTurretState
{
public:
	virtual StateReturnType update();

private:
	char m_pad[0x18];
	TurretStateMachine *m_machine;

	TurretAI *getTurretAI() const
	{
		return m_machine->getTurretAI();
	}
};

StateReturnType TurretAIAimTurretState::update()
{
	TurretAI *turret = getTurretAI();
	Object *obj = turret->getOwner();
	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (!ai)
		return STATE_FAILURE;
	Object *enemy;
	AIUpdateInterface *enemyAI = 0;
	Coord3D enemyPosition;
	TurretTargetType targetType =
		reinterpret_cast<const BFMETurretTargetAccessor *>(turret)->
		friend_getTurretTarget(enemy, enemyPosition);
	Object *enemyForDistanceCheckOnly = enemy;
	Bool preventing = false;
	Bool nothingInRange = false;

	switch (targetType)
	{
	case TARGET_NONE:
		return STATE_FAILURE;

	case TARGET_OBJECT:
	{
		Bool isPrimaryEnemy = enemy && enemy == ai->getGoalObject();
		Bool ableToAttackTarget = obj->isAbleToAttack();
		if (ableToAttackTarget)
		{
			CanAttackResult result = obj->getAbleToAttackSpecificObject(
				turret->isForceAttacking() ? ATTACK_CONTINUED_TARGET_FORCED : ATTACK_CONTINUED_TARGET,
				enemy, ai->getLastCommandSource());
			ableToAttackTarget = result == ATTACKRESULT_POSSIBLE ||
				result == ATTACKRESULT_POSSIBLE_AFTER_MOVING;
		}

		nothingInRange = !reinterpret_cast<BfmeFourSlotOwner *>(turret)->
			bfmeAnyAccepts(reinterpret_cast<Int>(enemy));
		if (enemy == 0 || !ableToAttackTarget ||
			(!isPrimaryEnemy && nothingInRange) ||
			enemy->getTeam() != turret->friend_getVictimInitialTeam())
		{
			if (turret->friend_getTargetWasSetByIdleMood())
				turret->setTurretTargetObject(0, false);
			return STATE_FAILURE;
		}

		if (enemy->isKindOf(KINDOF_BRIDGE))
		{
			TBridgeAttackInfo info;
			TheTerrainLogic->getBridgeAttackPoints(enemy, &info);
			Real distSqr = reinterpret_cast<const BfmeBoundaryObject3D *>(obj)->
				bfmeBoundaryDistanceSquared3D(
					reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(obj) + 0x38),
					&info.attackPoint1);
			if (distSqr > reinterpret_cast<const BfmeBoundaryObject3D *>(obj)->
				bfmeBoundaryDistanceSquared3D(
					reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(obj) + 0x38),
					&info.attackPoint2))
				enemyPosition = info.attackPoint2;
			else
				enemyPosition = info.attackPoint1;
		}
		else
		{
			enemyPosition = *enemy->getPosition();
		}

		enemyAI = enemy->getAIUpdateInterface();
		if (enemyAI)
			enemyAI->addTargeter(obj->getID(), true);
		preventing = enemyAI && enemyAI->isTemporarilyPreventingAimSuccess();
		enemy = 0;
		break;
	}

	case TARGET_POSITION:
		break;
	}

	WeaponSlotType slot;
	Weapon *curWeapon = obj->getCurrentWeapon(&slot);
	if (!curWeapon)
		return STATE_FAILURE;

	Real turnSpeedModifier = 1.0f;
	Real relAngle = obj->bfmeRelativeAngleTo(&enemyPosition);
	turret->apply(obj, relAngle);
	Real aimAngle = relAngle;
	Real sweep = turret->getData()->getSweep(slot);
	if (sweep > 0.0f && turret->friend_isSweepEnabled())
	{
		if (turret->friend_getPositiveSweep())
			aimAngle += sweep;
		else
			aimAngle -= sweep;
	}

	const Real REL_THRESH = 0.035f;
	Bool turnAlignedToNemesis = turret->friend_turnTowardsAngle(
		aimAngle, turnSpeedModifier, REL_THRESH);

	if (sweep > 0.0f)
	{
		if (turnAlignedToNemesis)
			turret->friend_setPositiveSweep(!turret->friend_getPositiveSweep());
		Real angleDiff = normalizeAngle(relAngle - turret->getTurretAngle());
		turnAlignedToNemesis = fabs(angleDiff) < sweep;
	}

	Bool pitchAlignedToNemesis = true;
	if (turret->getData()->allowsPitch())
	{
		Real desiredPitch = 0.0f;
		if (turret->getData()->getFirePitch() > BfmeZeroRange)
			desiredPitch = turret->getData()->getFirePitch();
		else
		{
			Coord3D v = reinterpret_cast<const Gen_00148990 *>(obj)->
				bfmeDelta(&enemyPosition);
			v.z -= obj->getGeometryInfo()->getMaxHeightAbovePosition() * g_bfmeK1253;
			Real actualPitch = asinf(v.z / v.length());
			desiredPitch = actualPitch;
			if (desiredPitch < turret->getData()->getMinPitch())
				desiredPitch = turret->getData()->getMinPitch();

			if (turret->getData()->getGroundUnitPitch() > 0.0f)
			{
				Bool adjust = false;
				if (!enemy)
					adjust = true;
				if (enemy && enemy->isKindOf(KINDOF_IMMOBILE))
					adjust = true;
				if (enemyAI && enemyAI->isDoingGroundMovement())
					adjust = true;
				if (adjust)
				{
					Real range = curWeapon->getAttackRange(obj, &v);
					Real dist = v.length();
					if (range < g_bfmeDefaultBU)
						range = 1.0f;
					Real groundPitch = turret->getData()->getGroundUnitPitch() * (dist / range);
					desiredPitch = actualPitch + groundPitch;
					if (desiredPitch < turret->getData()->getMinPitch())
						desiredPitch = turret->getData()->getMinPitch();
				}
			}
		}
		pitchAlignedToNemesis = turret->friend_turnTowardsPitch(desiredPitch, 1.0f);
	}

	if (turnAlignedToNemesis && pitchAlignedToNemesis &&
		((enemyForDistanceCheckOnly && curWeapon->isWithinAttackRange(obj, enemyForDistanceCheckOnly, 0)) ||
		 (!enemyForDistanceCheckOnly && curWeapon->isWithinAttackRange(obj, &enemyPosition, 0))))
	{
		if (preventing || nothingInRange)
			return STATE_CONTINUE;
		return STATE_SUCCESS;
	}

	return STATE_CONTINUE;
}

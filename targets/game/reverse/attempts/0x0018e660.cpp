// ?update@TurretAIAimTurretState@@UAE?AW4StateReturnType@@XZ
// partial score=0.25 date=2026-09-28
// cl: /O2 /DNDEBUG /MD
//
// Retail 0x0018E660 (1196 B, thiscall, ret 0): the BFME
// TurretAIAimTurretState::update (Zero Hour twin, same order of tests).  BFME
// measures the bridge attack points with the 3D boundary distance, hands the
// relative angle to a state helper (0x0018E210, turret-angle model
// conditions), dropped the v.length() > 0 guard and the INTER_TURRET_DELAY
// branch.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length() const;
};

// BFME placeholder spellings the matched helpers carry.
struct BfmeBoundaryPoint3D;
class BfmeVec3DG : public Coord3D
{
};

enum KindOfType
{
	KINDOF_IMMOBILE = 2,
	KINDOF_BRIDGE = 22
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum AbleToAttackType
{
	ATTACK_CONTINUED_TARGET = 2,
	ATTACK_CONTINUED_TARGET_FORCED = 3
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum CanAttackResult
{
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
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

class Team;
class Weapon;
class AIUpdateInterface;

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class StateMachine
{
public:
	class Object *getGoalObject();
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
	Real bfmeRelativeAngleTo(const Coord3D *position) const;

	const Coord3D *getPosition() const { return &m_position; }

protected:
	char m_pad000[0x38];
	Coord3D m_position;
};

class Object : public Thing
{
public:
	Bool isAbleToAttack() const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType,
		const Object *target, CommandSourceType commandSource) const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot);

	UnsignedInt getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Team *getTeam() const { return m_team; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }

private:
	char m_pad044[0x74 - 0x44];
	UnsignedInt m_id;
	char m_pad078[0xac - 0x78];
	GeometryInfo m_geometryInfo;
	char m_pad0ad[0x204 - 0xad];
	AIUpdateInterface *m_ai;
	char m_pad208[0x23c - 0x208];
	Team *m_team;
};

class BfmeBoundaryObject3D
{
public:
	Real bfmeBoundaryDistanceSquared3D(const BfmeBoundaryPoint3D *first,
		const BfmeBoundaryPoint3D *second) const;
};

class Gen_00148990
{
public:
	BfmeVec3DG bfmeDelta(const BfmeVec3DG *point) const;
};

class AIUpdateInterface
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00C();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01C();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02C();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03C();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04C();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05C();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06C();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07C();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08C();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09C();
	virtual void slot0A0();
	virtual void slot0A4();
	virtual void slot0A8();
	virtual void slot0AC();
	virtual void slot0B0();
	virtual void slot0B4();
	virtual void slot0B8();
	virtual void slot0BC();
	virtual void slot0C0();
	virtual void slot0C4();
	virtual void slot0C8();
	virtual void slot0CC();
	virtual void slot0D0();
	virtual void slot0D4();
	virtual void slot0D8();
	virtual void slot0DC();
	virtual void slot0E0();
	virtual void slot0E4();
	virtual void slot0E8();
	virtual void slot0EC();
	virtual void slot0F0();
	virtual void slot0F4();
	virtual void slot0F8();
	virtual void slot0FC();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10C();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11C();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12C();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13C();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual void slot14C();
	virtual void slot150();
	virtual void slot154();
	virtual void slot158();
	virtual void slot15C();
	virtual void slot160();
	virtual void slot164();
	virtual void slot168();
	virtual void slot16C();
	virtual void slot170();
	virtual void slot174();
	virtual void slot178();
	virtual void slot17C();
	virtual void slot180();
	virtual void slot184();
	virtual void slot188();
	virtual void slot18C();
	virtual void slot190();
	virtual void slot194();
	virtual void slot198();
	virtual void slot19C();
	virtual void slot1A0();
	virtual void slot1A4();
	virtual void slot1A8();
	virtual void slot1AC();
	virtual void slot1B0();
	virtual void slot1B4();
	virtual void slot1B8();
	virtual void slot1BC();
	virtual void slot1C0();
	virtual void slot1C4();
	virtual void slot1C8();
	virtual void addTargeter(UnsignedInt id, Bool add);
	virtual Bool isTemporarilyPreventingAimSuccess() const;
	virtual void slot1D4();
	virtual void slot1D8();
	virtual void slot1DC();
	virtual void slot1E0();
	virtual void slot1E4();
	virtual void slot1E8();
	virtual Bool isDoingGroundMovement() const;
	virtual void slot1F0();
	virtual void slot1F4();
	virtual void slot1F8();
	virtual void slot1FC();
	virtual CommandSourceType getLastCommandSource() const;

	Object *getGoalObject() { return m_stateMachine->getGoalObject(); }

	char m_pad004[0x30 - 4];
	StateMachine *m_stateMachine;
};

class TurretAIData
{
public:
	char m_pad00[0x10];
	Real m_turretFireAngleSweep[4];
	Real m_turretSweepSpeedModifier[4];
	Real m_firePitch;
	Real m_minPitch;
	Real m_groundUnitPitch;
	char m_pad3c[0x56 - 0x3c];
	Bool m_isAllowsPitch;
};

class TurretAI
{
public:
	Object *getOwner() { return m_owner; }
	Real getTurretAngle() const { return m_angle; }
	Bool isForceAttacking() const { return m_isForceAttacking; }
	Bool isAllowsPitch() const { return m_data->m_isAllowsPitch; }
	Real getFirePitch() const { return m_data->m_firePitch; }
	Real getMinPitch() const { return m_data->m_minPitch; }
	Real getGroundUnitPitch() const { return m_data->m_groundUnitPitch; }
	Real getTurretFireAngleSweepForWeaponSlot(WeaponSlotType slot) const { return m_data->m_turretFireAngleSweep[slot]; }
	Real getTurretSweepSpeedModifierForWeaponSlot(WeaponSlotType slot) const { return m_data->m_turretSweepSpeedModifier[slot]; }
	Bool friend_getPositiveSweep() const { return m_positiveSweep; }
	void friend_setPositiveSweep(Bool b) { m_positiveSweep = b; }
	Bool friend_getTargetWasSetByIdleMood() const { return m_targetWasSetByIdleMood; }
	Team *friend_getVictimInitialTeam() const { return m_victimInitialTeam; }

	Bool friend_isSweepEnabled() const;
	Bool friend_turnTowardsAngle(Real desiredAngle, Real rateModifier, Real relThresh);
	Bool friend_turnTowardsPitch(Real pitch, Real rateModifier);
	void setTurretTargetObject(Object *victim, Bool forceAttacking);

private:
	void *m_vtable;
	char m_pad004[4];
	const TurretAIData *m_data;
	char m_pad00c[4];
	Object *m_owner;
	char m_pad014[4];
	Real m_angle;
	char m_pad01c[0x94 - 0x1c];
	Team *m_victimInitialTeam;
	char m_pad098[0xa6 - 0x98];
	Bool m_positiveSweep;
	char m_pad0a7[0xaa - 0xa7];
	Bool m_isForceAttacking;
	Bool m_targetWasSetByIdleMood;
};

// Matched TurretAI helpers whose ledger names carry BFME placeholder owners.
class BFMETurretTargetAccessor
{
public:
	TurretTargetType friend_getTurretTarget(Object *&obj, Coord3D &pos) const;
};

class BfmeFourSlotOwner
{
public:
	Bool bfmeAnyAccepts(Int victim);
};

class Weapon
{
public:
	Real getAttackRange(const Object *source, const Coord3D *pos) const;
	Bool isWithinAttackRange(const Object *source, const Object *target, Int reserved) const;
	Bool isWithinAttackRange(const Object *source, const Coord3D *pos, Int reserved) const;
};

struct TBridgeAttackInfo
{
	Coord3D attackPoint1;
	Coord3D attackPoint2;
};

struct Rva003FD060TerrainLogic;
class TerrainLogic
{
public:
	void getBridgeAttackPoints(const Object *bridge, TBridgeAttackInfo *info);
};
extern TerrainLogic *TheTerrainLogic;

Real normalizeAngle(Real angle);
extern "C" float __cdecl asinf(float value);
extern "C" double __cdecl fabs(double value);
#pragma intrinsic(fabs)

class TurretStateMachine
{
public:
	TurretAI *getTurretAI() const { return m_turretAI; }

private:
	char m_pad00[0x44];
	TurretAI *m_turretAI;
};

class TurretAIAimTurretState
{
public:
	virtual StateReturnType update();
	void rva0018E210(Object *obj, Real angle);

protected:
	TurretAI *getTurretAI() { return m_machine->getTurretAI(); }

	char m_pad004[0x1c - 4];
	TurretStateMachine *m_machine;
};

StateReturnType TurretAIAimTurretState::update()
{
	TurretAI *turret = getTurretAI();
	Object *obj = turret->getOwner();
	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (!ai)
		return STATE_FAILURE;

	Object *victim;
	AIUpdateInterface *enemyAI = 0;
	Coord3D enemyPosition;
	Bool preventing = false;
	TurretTargetType targetType = ((const BFMETurretTargetAccessor *)turret)->friend_getTurretTarget(victim, enemyPosition);
	Object *enemy = victim;
	Object *enemyForDistanceCheckOnly = enemy;

	Bool nothingInRange = false;
	switch (targetType)
	{
		case TARGET_NONE:
			return STATE_FAILURE;

		case TARGET_OBJECT:
		{
			Bool isPrimaryEnemy = (enemy && enemy == ai->getGoalObject());
			Bool ableToAttackTarget = obj->isAbleToAttack();
			if (ableToAttackTarget)
			{
				CanAttackResult result = obj->getAbleToAttackSpecificObject(
					turret->isForceAttacking() ? ATTACK_CONTINUED_TARGET_FORCED : ATTACK_CONTINUED_TARGET,
					enemy, ai->getLastCommandSource());
				ableToAttackTarget = result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING;
			}

			nothingInRange = !((BfmeFourSlotOwner *)turret)->bfmeAnyAccepts((Int)enemy);
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
				Real distSqr = ((const BfmeBoundaryObject3D *)obj)->bfmeBoundaryDistanceSquared3D(
					(const BfmeBoundaryPoint3D *)obj->getPosition(), (const BfmeBoundaryPoint3D *)&info.attackPoint1);
				if (distSqr > ((const BfmeBoundaryObject3D *)obj)->bfmeBoundaryDistanceSquared3D(
					(const BfmeBoundaryPoint3D *)obj->getPosition(), (const BfmeBoundaryPoint3D *)&info.attackPoint2))
					enemyPosition = info.attackPoint2;
				else
					enemyPosition = info.attackPoint1;
			}
			else
			{
				enemyPosition = *enemy->getPosition();
			}

			enemyAI = enemy ? enemy->getAI() : 0;
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
	rva0018E210(obj, relAngle);

	Real aimAngle = relAngle;
	Real sweep = turret->getTurretFireAngleSweepForWeaponSlot(slot);
	if (sweep > 0.0f && turret->friend_isSweepEnabled())
	{
		if (turret->friend_getPositiveSweep())
			aimAngle += sweep;
		else
			aimAngle -= sweep;

		turnSpeedModifier = turret->getTurretSweepSpeedModifierForWeaponSlot(slot);
	}

	const Real REL_THRESH = 0.035f;
	Bool turnAlignedToNemesis = turret->friend_turnTowardsAngle(aimAngle, turnSpeedModifier, REL_THRESH);

	if (sweep > 0.0f)
	{
		if (turnAlignedToNemesis)
			turret->friend_setPositiveSweep(!turret->friend_getPositiveSweep());

		Real angleDiff = normalizeAngle(relAngle - turret->getTurretAngle());
		turnAlignedToNemesis = (fabs(angleDiff) < sweep);
	}

	Bool pitchAlignedToNemesis = true;
	if (turret->isAllowsPitch())
	{
		Real desiredPitch = 0;
		if (turret->getFirePitch() > 0)
		{
			desiredPitch = turret->getFirePitch();
		}
		else
		{
			BfmeVec3DG v = ((const Gen_00148990 *)obj)->bfmeDelta(static_cast<const BfmeVec3DG *>(&enemyPosition));
			v.z -= obj->getGeometryInfo().getMaxHeightAbovePosition() / 2;

			Real actualPitch = asinf(v.z / v.length());
			desiredPitch = actualPitch;
			if (desiredPitch < turret->getMinPitch())
				desiredPitch = turret->getMinPitch();
			if (turret->getGroundUnitPitch() > 0)
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
					Real range = curWeapon->getAttackRange(obj, &enemyPosition);
					Real dist = v.length();
					if (range < 1)
						range = 1;
					Real groundPitch = turret->getGroundUnitPitch() * (dist / range);
					desiredPitch = actualPitch + groundPitch;
					if (desiredPitch < turret->getMinPitch())
						desiredPitch = turret->getMinPitch();
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

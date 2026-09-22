// ?d_0017ba90@@YAXXZ
// partial score=0.27 date=2026-09-22
// Candidate reconstruction for the shared AIAttackAimAtTargetState update body.
// The address-derived owner is retained until the method identity is independently landed.

#include <math.h>

typedef int Int;
typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WhichTurretType
{
	TURRET_INVALID = -1
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum KindOfType
{
	KINDOF_3B = 0x3b,
	KINDOF_88 = 0x88,
	KINDOF_95 = 0x95
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Player;
class WeaponTemplate;
class Weapon;
class Object;

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class StateMachine
{
public:
	unsigned char m_unreconstructed_000[0x10];
	Object *m_owner;
	unsigned char m_unreconstructed_014[0x10];
	Coord3D m_goalPosition;

	Object *getGoalObject();
};

class Locomotor
{
public:
	Real getMaxTurnRate(Object *object) const;
};

class AIUpdateInterface : public BfmeVirtualSlots<114>
{
public:
	virtual void addTargeter(Int id, Bool add) = 0;
	virtual Bool isTemporarilyPreventingAimSuccess() const = 0;
	virtual void unusedAt1d4() = 0;
	virtual void setLocomotorGoalPositionExplicit(const Coord3D *) = 0;
	virtual void unusedAt1dc() = 0;
	virtual void unusedAt1e0() = 0;
	virtual void setLocomotorGoalOrientation(Real) = 0;

	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType, Object *, Bool);
	void setTurretTargetPosition(WhichTurretType, const Coord3D *);
	Real getTurretTurnRate(WhichTurretType) const;
};

class Object
{
public:
	void *m_vtable;
	WeaponTemplate *m_template;
	unsigned char m_unreconstructed_008[0x30];
	Coord3D m_position;
	Real m_orientation;
	unsigned char m_unreconstructed_048[0x2c];
	Int m_id;
	unsigned char m_unreconstructed_078[0x1c];
	unsigned int m_status94;
	unsigned int m_status98;
	unsigned char m_unreconstructed_09c[0x108];
	unsigned char m_status1a4;
	unsigned char m_unreconstructed_1a5[0x5f];
	AIUpdateInterface *m_ai;
	unsigned char m_unreconstructed_208[0x13c];
	unsigned char m_status344;

	Bool hasAnyWeapon();
	Weapon *getCurrentWeapon(WeaponSlotType);
	Player *getControllingPlayer() const;
	Locomotor *getCurLocomotor() const;
	Bool isKindOf(KindOfType) const;
	Bool getWorldspaceBestContactPoint(Coord3D *, const Coord3D *,
		const char *, Int, Int, Bool) const;
	Real bfmeRelativeAngleTo(const Coord3D *) const;
};

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const Object *) const;
};

class ThingTemplate
{
public:
	Bool isKindOf(KindOfType) const;
};

class WeaponTemplate
{
public:
	unsigned char m_unreconstructed_000[0x20];
	Real m_aimDelta;
	Real m_range;

	Bool isContactWeapon() const;
	Bool isLeechRangeWeapon() const;
};

class Weapon
{
public:
	void *m_vtable;
	WeaponTemplate *m_template;

	Bool isWithinAttackRange(const Object *, const Coord3D *, Int) const;
};

class Gen00039BD5
{
public:
	unsigned char m_unreconstructed_000[0x1c];
	StateMachine *m_machine;
	unsigned char m_unreconstructed_020[0x04];
	Bool m_isAttackingObject;
	Bool m_canTurnInPlace;
	Bool m_setLocomotor;
	Bool m_isForceAttacking;

	StateReturnType handle(Int index);
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")
#pragma comment(linker, "/alternatename:?hasAnyWeapon@Object@@QAE_NXZ=?j_00048b80@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentWeapon@Object@@QAEPAVWeapon@@W4WeaponSlotType@@@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurLocomotor@Object@@QBEPAVLocomotor@@XZ=?j_00021017@@YAXXZ")
#pragma comment(linker, "/alternatename:?isStealthedAndUndetected@BFMEObjectStealthQuery@@QBE_NPBVObject@@@Z=?j_00003b1b@@YAXXZ")
#pragma comment(linker, "/alternatename:?getWhichTurretForCurWeapon@AIUpdateInterface@@QBE?AW4WhichTurretType@@XZ=?j_000346a3@@YAXXZ")
#pragma comment(linker, "/alternatename:?setTurretTargetObject@AIUpdateInterface@@QAEXW4WhichTurretType@@PAVObject@@_N@Z=?j_0001a0e1@@YAXXZ")
#pragma comment(linker, "/alternatename:?setTurretTargetPosition@AIUpdateInterface@@QAEXW4WhichTurretType@@PBUCoord3D@@@Z=?j_000331bd@@YAXXZ")
#pragma comment(linker, "/alternatename:?getTurretTurnRate@AIUpdateInterface@@QBEMW4WhichTurretType@@@Z=?j_0003cc18@@YAXXZ")
#pragma comment(linker, "/alternatename:?getMaxTurnRate@Locomotor@@QBEMPAVObject@@@Z=?j_00024ea6@@YAXXZ")
#pragma comment(linker, "/alternatename:?getWorldspaceBestContactPoint@Object@@QBE_NPATCoord3D@@PBT1@PBDHH_N@Z=?j_00034e91@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeRelativeAngleTo@Object@@QBEMPBTCoord3D@@@Z=?j_00049413@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Object@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?isContactWeapon@WeaponTemplate@@QBE_NXZ=?j_0000b8ac@@YAXXZ")
#pragma comment(linker, "/alternatename:?isLeechRangeWeapon@WeaponTemplate@@QBE_NXZ=?j_00028f74@@YAXXZ")
#pragma comment(linker, "/alternatename:?isWithinAttackRange@Weapon@@QBE_NPBVObject@@PBUCoord3D@@H@Z=?j_0002e951@@YAXXZ")
#pragma comment(linker, "/alternatename:?normalizeAngle@@YAMM@Z=?j_0000991c@@YAXXZ")

extern Real normalizeAngle(Real);

#define BFME_ZERO_RANGE (*(const Real *)0x01075350)
#define BFME_TURN_THRESHOLD (*(const Real *)0x01095F98)

StateReturnType Gen00039BD5::handle(Int index)
{
	Object *source = m_machine->m_owner;
	AIUpdateInterface *sourceAI = source->m_ai;

	if (!source->hasAnyWeapon())
		return STATE_FAILURE;

	Object *victim = m_machine->getGoalObject();
	Weapon *weapon = source->getCurrentWeapon(PRIMARY_WEAPON);

	if (m_isAttackingObject && victim)
	{
		if ((victim->m_status344 & 1) != 0 ||
			(victim->m_status94 & 0x20000) != 0 ||
			((BFMEObjectStealthQuery *)victim)->isStealthedAndUndetected(
				(const Object *)source->getControllingPlayer()))
			return STATE_FAILURE;
	}

	WhichTurretType turret = sourceAI->getWhichTurretForCurWeapon();
	if (turret != TURRET_INVALID)
	{
		if (m_isAttackingObject)
			sourceAI->setTurretTargetObject(turret, victim, m_isForceAttacking);
		else
			sourceAI->setTurretTargetPosition(turret, &m_machine->m_goalPosition);

		if (sourceAI->getTurretTurnRate(turret) != BFME_ZERO_RANGE)
			return STATE_CONTINUE;
	}

	Real aimDelta = weapon ? weapon->m_template->m_aimDelta : BFME_ZERO_RANGE;
	if (aimDelta < 0.035f)
		aimDelta = 0.035f;

	Real turnRate = BFME_ZERO_RANGE;
	if (source->getCurLocomotor())
		turnRate = source->getCurLocomotor()->getMaxTurnRate(source);
	if (aimDelta < BFME_TURN_THRESHOLD)
		aimDelta = 0.3f;

	if ((source->m_status98 & 0x400) != 0)
		return STATE_CONTINUE;

	Coord3D targetPosition = m_machine->m_goalPosition;
	if (m_isAttackingObject && victim)
	{
		Bool gotContact = false;
		if (!victim->isKindOf(KINDOF_3B) && victim->isKindOf(KINDOF_88))
		{
			gotContact = victim->m_template->isContactWeapon();
			if (!gotContact)
				gotContact = victim->m_template->isLeechRangeWeapon();
		}

		if (!gotContact && !victim->isKindOf(KINDOF_95))
		{
			gotContact = victim->getWorldspaceBestContactPoint(
				&targetPosition, &source->m_position,
				(const char *)0x0109A0AC, 0x2a, 0, false);
		}

		if (!gotContact)
			targetPosition = victim->m_position;
	}

	Real relativeAngle = source->bfmeRelativeAngleTo(&targetPosition);
	if (weapon && weapon->m_template->m_range != BFME_ZERO_RANGE)
	{
		relativeAngle = normalizeAngle(relativeAngle - weapon->m_template->m_range);
	}

	if (m_canTurnInPlace)
	{
		if (fabs(relativeAngle) > aimDelta && index != 0)
		{
			sourceAI->setLocomotorGoalOrientation(source->m_orientation + relativeAngle);
			m_setLocomotor = true;
		}
	}
	else
	{
		sourceAI->setLocomotorGoalPositionExplicit(&targetPosition);
	}

	if (index != 0)
		return STATE_CONTINUE;

	if (fabs(relativeAngle) < aimDelta)
	{
		AIUpdateInterface *victimAI = victim ? victim->m_ai : 0;
		if (victimAI)
			victimAI->addTargeter(source->m_id, true);
		if (victimAI && victimAI->isTemporarilyPreventingAimSuccess())
			return STATE_CONTINUE;
		return STATE_SUCCESS;
	}

	if ((source->m_status1a4 & 8) != 0)
	{
		weapon = source->getCurrentWeapon(PRIMARY_WEAPON);
		const Coord3D *position = m_isAttackingObject && victim ?
			&victim->m_position : &m_machine->m_goalPosition;
		if (!weapon || !weapon->isWithinAttackRange(source, position, 0))
			return STATE_FAILURE;
	}

	return STATE_CONTINUE;
}

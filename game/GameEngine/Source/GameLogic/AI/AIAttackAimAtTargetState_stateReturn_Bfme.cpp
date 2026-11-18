// ?stateReturn@Gen00039BD5@@QAE?AW4StateReturnType@@_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0017BA90 (897 B, ret 4 at +0x37E, INT3 padding from +0x381): the
// AIAttackAimAtTargetState per-frame worker.  Matched onEnter 0x00183E40 calls
// it with 1 through ILT 0x00039BD5, and vtable 0x01097C60 slot 6's forwarder
// 0x001840D0 calls it with 0.  Rewritten cold from retail on the ZH
// AIAttackAimAtTargetState::update skeleton; the class name stays
// address-derived, as in the onEnter TU.
// PARAMETER IS Bool: retail re-reads `byte ptr [esp+0x34]` at every use, while
// an Int parameter is cached in edi (Int measured 893 B with 239 diffs).  The
// onEnter TU still declares the ...@H@Z spelling and needs the same correction
// whenever it is revisited; both callers push the same immediate.
// LAYOUT: the Ram-contact false arm must precede the contact call.  Spelling
// its guard `(...) == false` with the false arm first is the one form MSVC 7.1
// leaves in retail's order -- `!`, De Morgan, ternary and arm-swap spellings
// all canonicalize back to then-first.  Coord3D = member-wise copy ctor +
// IMPLICIT operator=; the aim delta is assigned under `if (weapon)`; the angle
// offset goes through a named local.  The Zero Hour "no else here!" block
// encloses REL_THRESH through the aim-success test; with targetPos declared
// inside it, retail's load-all victim position copy follows.
#include <math.h>

// class-gate: allow Coord3D the canonical bare header drops the member-wise
// copy constructor; adopting it moves 458 bytes (896/897 B), so this view needs
// the local ctor.
#include "../../../Include/Common/ScalarTypes.h"



#include "../../../Include/Common/Enums/StateReturnType.h"
enum WhichTurretType { TURRET_INVALID = -1 };
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum KindOfType { KINDOF_BFME_3B = 0x3b, KINDOF_BFME_88 = 0x88, KINDOF_BFME_95 = 0x95 };

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
	void set(const Coord3D *p) { x = p->x; y = p->y; z = p->z; }
	Real x, y, z;
};

class Player;
class Object;

template<int N>
class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template<> class VirtualSlots<0> {};

class StateMachine
{
public:
	Object *getGoalObject();

	unsigned char m_unreconstructed_000[0x10];
	Object *m_owner;
	unsigned char m_unreconstructed_014[0x10];
	Coord3D m_goalPosition;
};

class Locomotor
{
public:
	Real getMaxTurnRate(Object *obj) const;
};

class AIUpdateInterface : public VirtualSlots<115>
{
public:
	virtual void addTargeter(Int id, Bool add) = 0;
	virtual Bool isTemporarilyPreventingAimSuccess() = 0;
	virtual void vslot1D4() = 0;
	virtual void setLocomotorGoalPositionExplicit(const Coord3D &pos) = 0;
	virtual void vslot1DC() = 0;
	virtual void vslot1E0() = 0;
	virtual void setLocomotorGoalOrientation(Real angle) = 0;

	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType tur, Object *victim, Bool force);
	void setTurretTargetPosition(WhichTurretType tur, const Coord3D *pos);
};

// Placeholder-named callees, used through views on the receiver they take.
class Gen_0026EB40 { public: Real bfmeValue(Int turret) const; };      // turret turn rate
class Rva001BE100 { public: Bool has(); };                            // hasAnyWeapon
class Rva001BE010 { public: Int get(); };                             // current locomotor
class Gen_001e1760 { public: Bool m(); };
class Rva001E1770ByteField { public: unsigned char get() const; };
class BFMEObjectStealthQuery { public: Bool isStealthedAndUndetected(const Object *) const; };

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
	Real bfmeRelativeAngleTo(const Coord3D *pos) const;
};

class WeaponTemplate
{
public:
	unsigned char m_unreconstructed_000[0x20];
	Real m_aimDelta;
	Real m_field24;
};

class Weapon
{
public:
	Real getAimDelta() const { return m_template->m_aimDelta; }
	Bool isWithinAttackRange(const Object *source, const Coord3D *pos, Int flags) const;

	void *m_vtable;
	WeaponTemplate *m_template;
};

class Object : public Thing
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Player *getControllingPlayer() const;
	Bool getWorldspaceBestContactPoint(Coord3D *result, const Coord3D *from, const char *bone,
		Int a, Int b, Bool c) const;
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Bool isDisabledByType(Int type) const { return (m_disabledMask & (1 << type)) != 0; }
	AIUpdateInterface *getAI() { return m_ai; }
	const Coord3D *getPosition() const { return &m_position; }
	Real getOrientation() const { return m_orientation; }
	Int getID() const { return m_id; }

	void *m_vtable;
	char m_pad04[0x34];
	Coord3D m_position;
	Real m_orientation;
	char m_pad48[0x2c];
	Int m_id;
	char m_pad78[0x1c];
	unsigned int m_status94;
	unsigned int m_status98;
	char m_pad9C[0x108];
	unsigned char m_disabledMask;
	char m_pad1A5[0x5f];
	AIUpdateInterface *m_ai;
	char m_pad208[0x13c];
	unsigned char m_privateStatus;
};

extern Real normalizeAngle(Real angle);

enum { DISABLED_HELD = 3 };

// The AIAttackAimAtTargetState layout of the matched onEnter TU; the member
// name is the value-returning placeholder that onEnter links at ILT 0x00039BD5.
class Gen00039BD5
{
public:
	StateReturnType stateReturn(Bool firstTime);

	unsigned char m_unreconstructed_000[0x1c];
	StateMachine *m_machine;
	unsigned char m_unreconstructed_020[0x04];
	Bool m_isAttackingObject;
	Bool m_canTurnInPlace;
	Bool m_setLocomotor;
	Bool m_isForceAttacking;
};

StateReturnType Gen00039BD5::stateReturn(Bool firstTime)
{
	Object *source = m_machine->m_owner;
	AIUpdateInterface *sourceAI = source->getAI();

	if (!((Rva001BE100 *)source)->has())
		return STATE_FAILURE;

	Object *victim = m_machine->getGoalObject();
	Weapon *weapon = source->getCurrentWeapon(0);
	if (m_isAttackingObject)
	{
		if (!victim || victim->isEffectivelyDead() || (victim->m_status94 & 0x20000) != 0 ||
			((BFMEObjectStealthQuery *)victim)->isStealthedAndUndetected(
				(const Object *)source->getControllingPlayer()))
			return STATE_FAILURE;
	}

	WhichTurretType tur = sourceAI->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		if (m_isAttackingObject)
			sourceAI->setTurretTargetObject(tur, victim, m_isForceAttacking);
		else
			sourceAI->setTurretTargetPosition(tur, &m_machine->m_goalPosition);
		if (((Gen_0026EB40 *)sourceAI)->bfmeValue(tur) != 0.0f)
			return STATE_CONTINUE;
	}

	{
		const Real REL_THRESH = 0.035f;
		Real aimDelta = 0.0f;
		if (weapon)
			aimDelta = weapon->getAimDelta();
		if (aimDelta < REL_THRESH)
			aimDelta = REL_THRESH;

		Real turnRate = 0.0f;
		if (((Rva001BE010 *)source)->get())
			turnRate = ((Locomotor *)((Rva001BE010 *)source)->get())->getMaxTurnRate(source);

		if (source->isDisabledByType(DISABLED_HELD) && aimDelta < 0.3f)
			aimDelta = 0.3f;

		if ((source->m_status98 & 0x400) != 0)
			return STATE_SUCCESS;

		Coord3D targetPos = m_machine->m_goalPosition;
		if (m_isAttackingObject)
		{
			Bool gotContact;
			if ((weapon && (victim->isKindOf(KINDOF_BFME_3B) || victim->isKindOf(KINDOF_BFME_88)) &&
				(((Gen_001e1760 *)weapon->m_template)->m() ||
				 ((Rva001E1770ByteField *)weapon->m_template)->get())) == false)
				gotContact = false;
			else
				gotContact = victim->getWorldspaceBestContactPoint(&targetPos, source->getPosition(), "Ram", 0, 0x2a, false);
			if (!victim->isKindOf(KINDOF_BFME_95) && !gotContact)
				targetPos = *victim->getPosition();
		}

		Real relAngle = source->bfmeRelativeAngleTo(&targetPos);
		if (weapon && weapon->m_template->m_field24 > 0.0f)
		{
			Real offset = weapon->m_template->m_field24;
			relAngle = normalizeAngle(relAngle - offset);
		}

		if (m_canTurnInPlace)
		{
			if (fabs(relAngle) > aimDelta || firstTime)
			{
				sourceAI->setLocomotorGoalOrientation(source->getOrientation() + relAngle);
				m_setLocomotor = true;
			}
		}
		else
		{
			sourceAI->setLocomotorGoalPositionExplicit(targetPos);
		}

		if (firstTime)
			return STATE_CONTINUE;

		if (fabs(relAngle) < aimDelta || fabs(relAngle) < turnRate * 0.5f)
		{
			AIUpdateInterface *victimAI = victim ? victim->getAI() : 0;
			if (victimAI)
			{
				victimAI->addTargeter(source->getID(), true);
				if (victimAI->isTemporarilyPreventingAimSuccess())
					return STATE_CONTINUE;
			}
			return STATE_SUCCESS;
		}
	}

	if (source->isDisabledByType(DISABLED_HELD))
	{
		Weapon *heldWeapon = source->getCurrentWeapon(0);
		const Coord3D *pos = m_isAttackingObject ? victim->getPosition() : &m_machine->m_goalPosition;
		if (!heldWeapon || !heldWeapon->isWithinAttackRange(source, pos, 0))
			return STATE_FAILURE;
	}

	return STATE_CONTINUE;
}

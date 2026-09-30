// cl: /DNDEBUG /MD
// Retail 0x00174E10, 734 bytes: AIAttackApproachTargetState::onEnter (ZH AIStates.cpp twin).
// Identity: vftable 0x0109A4C0 slot 4 (ILT 0x00448A95); slots 5 and 17 are the landed onExit and computePath.
// The static helpers canPursue and rva0016B010 are compiled here for their private register ABI.

typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum KindOfType {};
enum WeaponSlotType {};
enum WhichTurretType { TURRET_INVALID = -1 };
enum PlayerType { PLAYER_HUMAN, PLAYER_COMPUTER };
enum CrushSquishTestType { TEST_CRUSH_ONLY, TEST_SQUISH_ONLY, TEST_CRUSH_OR_SQUISH };
enum { INVALID_STATE_ID = 999999 };

class Object;
class Weapon;
class State;
class CRCParameterCheck;
class BfmeOutOfWeaponRangeObject;

template <int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();
	BfmeOverridable *getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	UnsignedByte m_unreconstructed_000[4];
	BfmeOverridable *m_nextOverride;		// +0x04
};

class ThingTemplate : public BfmeOverridable
{
public:
	UnsignedByte m_unreconstructed_008[0xC8 - 0x08];
	UnsignedInt m_kindOfBits;				// +0xC8
};

enum { BFME_KINDOF_PROJECTILE_BIT = 0x02000000 };

// Retail Locomotor::setUsePreciseZPos(true) is an inline flag set.
class Locomotor
{
public:
	void setUsePreciseZPos(Bool set)
	{
		if (set)
			m_flags |= PRECISE_Z_POS;
	}

	enum { PRECISE_Z_POS = 0x00000008 };
	UnsignedByte m_unreconstructed_000[0x40];
	UnsignedInt m_flags;					// +0x40
};

class BfmeSub1CC_EC3
{
public:
	Real effectiveMaxSpeed(void *object);
};

class StateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(Object *object) = 0;

	int getCurrentStateID() const;
	Object *getGoalObject();
	Bool isGoalObjectDestroyed() const;

	UnsignedByte m_pad04[0x10 - 0x04];
	Object *m_owner;						// +0x10
	UnsignedByte m_pad14[0x1c - 0x14];
	State *m_currentState;					// +0x1c
	UnsignedByte m_pad20[0x24 - 0x20];
	Coord3D m_goalPosition;					// +0x24
};

// StateMachine vtable slot +0x38 (setGoalObject, as in AIAttackSquadState)
// viewed as a register-only call so the table temporary stays in EDX.
typedef void (__fastcall *StateMachineSetGoalObjectFn)(void *, void *, Object *);
struct StateMachineVtableView
{
	void *slots[14];
	StateMachineSetGoalObjectFn setGoalObject;
};

class State
{
public:
	virtual void slot00() = 0;

	int m_ID;
};

inline int StateMachine::getCurrentStateID() const
{
	return m_currentState ? m_currentState->m_ID : INVALID_STATE_ID;
}

class Rva001E1770ByteField { public: unsigned char get() const; };
class Rva001E1780ByteField { public: unsigned char get() const; };

class WeaponTemplate
{
public:
	UnsignedByte m_pad000[0x533];
	Bool m_byte533;							// +0x533
};

class Weapon
{
public:
	Bool isWithinAttackRange(const Object *source, const Object *target, int extra) const;

	void *m_vptr;
	WeaponTemplate *m_template;				// +0x04
};

class Player
{
public:
	PlayerType getPlayerType() const { return m_playerType; }

	UnsignedByte m_pad000[0x2c];
	PlayerType m_playerType;				// +0x2c
};

class AIUpdateModuleData
{
public:
	UnsignedByte m_pad000[0x28];
	Bool m_byte28;							// +0x28
};

class AIUpdateInterface : public BFMEVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement() const = 0;	// +0x1EC
	virtual void slot1f0() = 0;
	virtual void slot1f4() = 0;
	virtual void slot1f8() = 0;
	virtual void slot1fc() = 0;
	virtual int slot200() = 0;				// +0x200

	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType tur, Object *o, Bool isForceAttacking);
	void setTurretTargetPosition(WhichTurretType tur, const Coord3D *pos);
	Bool isQuickPathAvailable(const Coord3D *destination) const;
	Real getCurLocomotorSpeed();
	Locomotor *getCurLocomotor() { return m_curLocomotor; }

	AIUpdateModuleData *m_moduleData;		// +0x04
	UnsignedByte m_pad008[0x30 - 0x08];
	StateMachine *m_stateMachine;			// +0x30
	UnsignedByte m_pad034[0x1cc - 0x34];
	Locomotor *m_curLocomotor;				// +0x1cc
	UnsignedByte m_pad1d0[0x32f - 0x1d0];
	UnsignedByte byte_32f;					// +0x32f
	UnsignedByte m_pad330[0x33a - 0x330];
	Bool byte_33a;							// +0x33a
};

class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		if (!m_template)
			return 0;
		return (const ThingTemplate *)m_template->getFinalOverride();
	}
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }
	void *getPhysics() const { return m_physics; }

	Bool isMobile() const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0);
	void *find(int slot);
	Player *getControllingPlayer() const;
	Bool crushPolicy(Object *otherObject, CrushSquishTestType test) const;
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	const Coord3D *getUnitDirectionVector2D() const;
	Bool testStatus(int status) const;
	Bool isSignificantlyAboveTerrain() const;
	int getLayer() const;

	void *m_vptr;
	ThingTemplate *m_template;				// +0x04
	UnsignedByte m_pad008[0x38 - 0x08];
	Coord3D m_position;						// +0x38
	UnsignedByte m_pad044[0x94 - 0x44];
	UnsignedByte m_byte94;					// +0x94
	UnsignedByte m_pad095[0x98 - 0x95];
	UnsignedInt m_status98;					// +0x98
	UnsignedByte m_pad09c[0x1f5 - 0x9c];
	UnsignedByte byte_1f5;					// +0x1f5
	UnsignedByte m_pad1f6[0x204 - 0x1f6];
	AIUpdateInterface *m_ai;				// +0x204
	void *m_physics;						// +0x208
	UnsignedByte m_pad20c[0x214 - 0x20c];
	void *m_dword214;						// +0x214
};

class Pathfinder
{
public:
	Bool isAttackViewBlockedByObstacle(const Object *attacker, const Coord3D *attackerPos,
		const Object *victim, const Coord3D *victimPos);
};

class TAiData
{
public:
	UnsignedByte m_pad000[0x8c];
	Bool m_aiCrushesInfantry;				// +0x8c
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

	UnsignedByte m_pad000[0xc];
	Pathfinder *m_pathfinder;				// +0x0c
	UnsignedByte m_pad010[0x14 - 0x10];
	TAiData *m_aiData;						// +0x14
};

class GameLogic
{
public:
	UnsignedByte m_pad000[0x3c];
	UnsignedInt m_frame;					// +0x3c
};

extern Bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern GameLogic *TheBfmeGameLogic;
extern AI *TheAI;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);
bool rva0014ca60(BfmeOutOfWeaponRangeObject *source, BfmeOutOfWeaponRangeObject *victim);

extern void j_0000e7dc();

class ThiscallReceiverView {};
template<class MemberFunctionType> __forceinline MemberFunctionType makeThiscallMemberPointer(void (*raw)())
{
	union { void (*raw)(); MemberFunctionType member; } fn;
	fn.raw = raw;
	return fn.member;
}
#define CALL_THISCALL(MemberFunctionType, obj, fn) \
	(((ThiscallReceiverView *)(obj))->*makeThiscallMemberPointer<MemberFunctionType>(fn))

typedef Bool (ThiscallReceiverView::*WeaponIsTooCloseMethod)(Object *, Object *);

#define CRCDEBUG_LOG(msg) \
	if (Glo012F0239 && TheCRCParameterCheck) \
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, msg)

static UnsignedByte rva0016B010(Object *obj)
{
	Weapon *weapon = (Weapon *)obj->find(0);
	if (weapon && (((Rva001E1770ByteField *)weapon->m_template)->get() ||
			((Rva001E1780ByteField *)weapon->m_template)->get()))
		return 1;
	if (obj->getControllingPlayer()->m_playerType)
		return 1;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return 1;
	return ai->m_stateMachine->getCurrentStateID() == 0x3e || ai->slot200() != 2 ||
		ai->byte_32f || obj->byte_1f5;
}

static __declspec(noinline) Bool canPursue(Object *attacker, Weapon *weapon, Object *target)
{
	if (!target->getPhysics())
		return false;
	if ((attacker->m_byte94 & 0x20) && attacker->m_dword214)
		return false;
	AIUpdateInterface *ai = attacker->getAI();
	if (!ai)
		return false;

	WhichTurretType turretType = ai->getWhichTurretForCurWeapon();
	if (turretType == TURRET_INVALID)
		return false;

	if (TheAI->m_aiData->m_aiCrushesInfantry)
	{
		if (attacker->getControllingPlayer() &&
			(attacker->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER) &&
			attacker->crushPolicy(target, TEST_CRUSH_OR_SQUISH))
		{
			return true;
		}
	}

	if (CALL_THISCALL(WeaponIsTooCloseMethod, weapon, j_0000e7dc)(attacker, target))
		return false;

	Real ourMaxSpeed = attacker->getAI()->getCurLocomotorSpeed();
	Real targetPreferredSpeed = target->bfmeGetNonnegativePreferredLocomotorHeight();
	if (targetPreferredSpeed >= ourMaxSpeed)
		return false;
	if (targetPreferredSpeed < ourMaxSpeed * 0.1f)
		return false;
	Real dx = target->getPosition()->x - attacker->getPosition()->x;
	Real dy = target->getPosition()->y - attacker->getPosition()->y;
	const Coord3D *targetDirection = target->getUnitDirectionVector2D();
	Coord3D targetDirectionVector;
	targetDirectionVector.x = targetDirection->x;
	targetDirectionVector.y = targetDirection->y;
	if (dx*targetDirectionVector.x + dy*targetDirectionVector.y < 0)
		return false;
	return true;
}

class AIInternalMoveToState : public BFMEVirtualSlots<4>
{
public:
	virtual StateReturnType onEnter();
};

class AIAttackApproachTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

protected:
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual Bool computePath();				// +0x44

	StateMachine *getMachine() { return machine; }
	Object *getMachineOwner() { return machine->m_owner; }
	Object *getMachineGoalObject() { return machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() { return &machine->m_goalPosition; }
	void setAdjustsDestination(Bool b) { adjust4c = b; }

	UnsignedByte m_pad004[0x1c - 0x04];
	StateMachine *machine;					// +0x1c
	UnsignedByte pad20[0x4c - 0x20];
	Bool adjust4c;							// +0x4c
	UnsignedByte pad4d[0x50 - 0x4d];
	Coord3D previous50;						// +0x50
	Coord3D position5c;						// +0x5c
	int timestamp68;						// +0x68
	UnsignedInt wait6c;						// +0x6c
	Bool field70;							// +0x70
	Bool object71;							// +0x71
	Bool field72;							// +0x72
	Bool field73;							// +0x73
	Bool force74;							// +0x74
	Bool wait75;							// +0x75
};

StateReturnType AIAttackApproachTargetState::onEnter()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();
	if (source->getTemplate()->m_kindOfBits & BFME_KINDOF_PROJECTILE_BIT)
	{
		if (ai->getCurLocomotor())
			ai->getCurLocomotor()->setUsePreciseZPos(true);
	}

	position5c = *source->getPosition();

	if (getMachine()->isGoalObjectDestroyed())
		return STATE_SUCCESS;

	wait75 = false;
	if ((source->m_status98 & 8) || ai->byte_33a)
	{
		if (rva0014ca60((BfmeOutOfWeaponRangeObject *)source,
				(BfmeOutOfWeaponRangeObject *)getMachineGoalObject()))
			return STATE_SUCCESS;
		StateMachine *stateMachine = getMachine();
		StateMachineVtableView *machineVtable = *(StateMachineVtableView **)stateMachine;
		// Match the retail EDX vtable temporary on this virtual call.
		machineVtable->setGoalObject(stateMachine, machineVtable, 0);
		return STATE_FAILURE;
	}

	previous50.x = 0.0f;
	previous50.y = 0.0f;
	previous50.z = 0.0f;

	timestamp68 = -5;

	Weapon *weapon = source->getCurrentWeapon();
	Object *victim = getMachineGoalObject();
	if (victim)
	{
		if (!weapon)
			return STATE_FAILURE;
		if (weapon->isWithinAttackRange(source, victim, 0))
		{
			if (!ai->isDoingGroundMovement())
				return STATE_SUCCESS;
			if (victim->isSignificantlyAboveTerrain())
				return STATE_SUCCESS;
			if (!TheAI->pathfinder()->isAttackViewBlockedByObstacle(source, source->getPosition(),
					victim, victim->getPosition()))
				return STATE_SUCCESS;
		}
		if (!rva0016B010(source))
			return STATE_FAILURE;
		if (canPursue(source, weapon, victim))
			return STATE_SUCCESS;
		if (ai->m_moduleData->m_byte28 && source->getLayer() >= 17 &&
			!ai->isQuickPathAvailable(victim->getPosition()))
		{
			wait75 = true;
			wait6c = TheBfmeGameLogic->m_frame + 10;
			return STATE_CONTINUE;
		}
	}
	else
	{
		if (!weapon || !weapon->m_template->m_byte533)
			return STATE_FAILURE;
	}

	if (source->testStatus(37) && source->m_dword214)
		return STATE_FAILURE;

	Bool mobile = true;
	if (!source->isMobile())
		mobile = false;
	if (((BfmeSub1CC_EC3 *)ai->getCurLocomotor())->effectiveMaxSpeed(source) < 0.1f || !mobile)
	{
		wait75 = true;
		wait6c = TheBfmeGameLogic->m_frame + 10;
		return STATE_CONTINUE;
	}

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		if (object71)
			ai->setTurretTargetObject(tur, victim, force74);
		else
			ai->setTurretTargetPosition(tur, getMachineGoalPosition());
	}

	if (computePath() == false)
		return STATE_FAILURE;
	if (wait75)
		return STATE_CONTINUE;

	CRCDEBUG_LOG("CritterDesync: setAdjustDestination(FALSE) 21");
	setAdjustsDestination(false);
	StateReturnType ret = AIInternalMoveToState::onEnter();
	CRCDEBUG_LOG("CritterDesync: setAdjustDestination(TRUE) 22");
	setAdjustsDestination(true);
	return ret;
}

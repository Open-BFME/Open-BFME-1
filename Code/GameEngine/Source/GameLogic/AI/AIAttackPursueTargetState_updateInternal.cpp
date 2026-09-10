// cl: /DNDEBUG /MD /EHsc
// readable body of ?updateInternal@AIAttackPursueTargetState@@AAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// Retail 0x00176250, reached through the ILT at 0x00014EF2 from the matched
// AIAttackPursueTargetState::update at 0x001764E0.  BFME keeps the Zero Hour
// body and adds a CritterDesync log before computePath plus a locomotor test
// after the desired-speed call.  The narrow class views below carry the
// recovered BFME offsets without touching the shared headers.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

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

// Retail tests one bit of the status dword at Object+0x94.  The shared
// ObjectStatusBits numbering is not the BFME numbering, so the recovered mask
// is spelled directly.
enum { BFME_OBJECT_STATUS_UNPURSUABLE = 0x00040000 };
enum CrushSquishTestType
{
	TEST_CRUSH_OR_SQUISH = 2
};

const Real FAST_AS_POSSIBLE = 999999.0f;

extern const Real BfmeZeroRange;

class Object;
class Player;
class Weapon;
class BfmeOutOfWeaponRangeObject;

template <Int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

class Locomotor
{
public:
	Real getPreferredHeight() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public BFMEVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement() const = 0;    // vtable +0x1EC
	virtual void unusedAt1F0(char (*)[1]) = 0;
	virtual void unusedAt1F4(char (*)[2]) = 0;
	virtual void unusedAt1F8(char (*)[3]) = 0;
	virtual void unusedAt1FC(char (*)[4]) = 0;
	virtual void unusedAt200(char (*)[5]) = 0;
	virtual void notifyVictimIsDead() = 0;             // vtable +0x204

	void setDesiredSpeed(Real speed);

	Locomotor *getCurLocomotor() const
	{
		return *(Locomotor **)((char *)this + 0x1CC);
	}
};

// The victim setter and the turret pair sit at their own recovered thunks, so
// they are reached through the views the ledger already pins for them.
class BfmeAIUpdateVictimThunk
{
public:
	void clearCurrentVictim(const Object *victim);
};

class Rva001764E0AIUpdate
{
public:
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType turret, Object *target, Bool forceAttacking);
};

class Pathfinder
{
public:
	Bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *sourcePos,
		const Object *victim, const Coord3D *victimPos);
};

class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

private:
	UnsignedByte m_unreconstructed_000[0x0c];
	Pathfinder *m_pathfinder;                          // retail this+0x0C
};

extern AI *TheAI;

class Weapon
{
public:
	Bool isGoalPosWithinAttackRange(const Object *source, const Coord3D *goalPos,
		const Object *victim, const Coord3D *victimPos, Int forceAttacking) const;
};

class BfmeOutOfWeaponRangeWeapon
{
public:
	Bool isWithinAttackRange(const BfmeOutOfWeaponRangeObject *source,
		const BfmeOutOfWeaponRangeObject *victim, Int forceAttacking) const;
};

class BfmeObjectCall
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool queryRva001CAEE0(const Player *player) const;
	Bool isSignificantlyAboveTerrain() const;
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Bool crushPolicy(Object *other, CrushSquishTestType test) const;

	UnsignedByte m_unreconstructed_000[0x38];
	Coord3D m_position;                                // retail Object+0x38
	UnsignedByte m_unreconstructed_044[0x94 - 0x44];
	UnsignedInt m_status;                              // retail Object+0x94
	UnsignedByte m_unreconstructed_098[0x204 - 0x98];
	AIUpdateInterface *m_ai;                           // retail Object+0x204
	void *m_physics;                                   // retail Object+0x208
};

class StateMachine
{
public:
	Bool isGoalObjectDestroyed() const;
	Object *getGoalObject();

	UnsignedByte m_unreconstructed_000[0x10];
	Object *m_owner;                                   // retail this+0x10
};

extern UnsignedByte g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a();

typedef void (__cdecl *BfmePursueCritterDesyncLog)(void *, const char *);

static void bfmePursueLog(const char *message)
{
	if (g_012F0239 && g_012ED4FC)
		((BfmePursueCritterDesyncLog)j_0003a17a)(g_012ED4FC, message);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public BFMEVirtualSlots<17>
{
public:
	virtual Bool computePath();                        // vtable +0x44
	virtual StateReturnType update();
};

class AIAttackPursueTargetState : public AIInternalMoveToState
{
private:
	StateReturnType updateInternal();

	UnsignedByte m_unreconstructed_004[0x1C - 0x04];
	StateMachine *m_machine;                           // retail this+0x1C
	UnsignedByte m_unreconstructed_020[0x62 - 0x20];
	Bool m_stopIfInRange;                              // retail this+0x62
	Bool m_isInitialApproach;                          // retail this+0x63
	Bool m_isForceAttacking;                           // retail this+0x64
};

StateReturnType AIAttackPursueTargetState::updateInternal()
{
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	if (m_machine->isGoalObjectDestroyed())
	{
		ai->notifyVictimIsDead();
		((BfmeAIUpdateVictimThunk *)ai)->clearCurrentVictim(0);
		return STATE_FAILURE;
	}
	m_stopIfInRange = false;

	Object *source = m_machine->m_owner;
	StateReturnType code = STATE_FAILURE;
	Object *victim = m_machine->getGoalObject();
	if (victim)
	{
		if (victim->m_status & BFME_OBJECT_STATUS_UNPURSUABLE)
			return STATE_FAILURE;

		if (victim->queryRva001CAEE0(((BfmeObjectCall *)source)->getControllingPlayer()))
			return STATE_FAILURE;

		((BfmeAIUpdateVictimThunk *)ai)->clearCurrentVictim(victim);

		bfmePursueLog("CritterDesync: ComputePath14");

		if (computePath() == false)
			return STATE_FAILURE;

		code = AIInternalMoveToState::update();
		if (code != STATE_CONTINUE)
			return STATE_SUCCESS;

		Weapon *weapon = source->getCurrentWeapon(0);
		if (!weapon)
			return STATE_FAILURE;

		WhichTurretType tur = ((Rva001764E0AIUpdate *)ai)->getWhichTurretForCurWeapon();
		if (tur == TURRET_INVALID)
			return STATE_SUCCESS;

		Bool viewBlocked = false;
		if (ai->isDoingGroundMovement() && !victim->isSignificantlyAboveTerrain())
		{
			viewBlocked = TheAI->pathfinder()->isAttackViewBlockedByObstacle(source,
				&source->m_position, victim, &victim->m_position);
		}
		if (!viewBlocked && victim->m_physics
			&& ((BfmeOutOfWeaponRangeWeapon *)weapon)->isWithinAttackRange(
				(const BfmeOutOfWeaponRangeObject *)source,
				(const BfmeOutOfWeaponRangeObject *)victim, 0))
		{
			((Rva001764E0AIUpdate *)ai)->setTurretTargetObject(tur, victim, m_isForceAttacking);
			m_isInitialApproach = false;
			Real victimSpeed = victim->bfmeGetNonnegativePreferredLocomotorHeight();
			if (weapon->isGoalPosWithinAttackRange(source, &source->m_position, victim,
				&victim->m_position, 0))
			{
				victimSpeed *= 0.95f;
			}
			if (source->crushPolicy(victim, TEST_CRUSH_OR_SQUISH))
			{
				victimSpeed = FAST_AS_POSSIBLE;
			}
			ai->setDesiredSpeed(victimSpeed);
			Locomotor *locomotor = ai->getCurLocomotor();
			if (locomotor && locomotor->getPreferredHeight() == BfmeZeroRange)
				return STATE_SUCCESS;
		}
		else
		{
			ai->setDesiredSpeed(FAST_AS_POSSIBLE);
		}
	}
	return code;
}

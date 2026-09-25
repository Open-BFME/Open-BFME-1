// ?computePath@AIAttackPursueTargetState@@UAE_NXZ
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00175E90, 384 bytes. BFME pursue-state reconstruction from the
// landed AI donor helpers, the vtable slot and the decoded retail body.

typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum KindOfType {};
enum PathfindLayerEnum {};
enum WeaponSlotType {};
enum ObjectID { INVALID_ID = 0 };
enum WhichTurretType { TURRET_INVALID = -1 };
enum PlayerType { PLAYER_HUMAN, PLAYER_COMPUTER };
enum CrushSquishTestType { TEST_CRUSH_ONLY, TEST_SQUISH_ONLY, TEST_CRUSH_OR_SQUISH };
typedef float Real;

class Object;
class Weapon;
class CRCParameterCheck;

class LocomotorSet {};

class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForCurWeapon() const;
	Real getCurLocomotorSpeed();
	void ignoreObstacle(Object *obstacle);
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	void requestAttackPath(ObjectID targetObjectId, const Coord3D *targetPosition);

	char m_pad000[0x140];
	void *m_path;
	char m_pad144[0x1a8 - 0x144];
	LocomotorSet m_locomotorSet;
	char m_pad1a9[0x31e - 0x1a9];
	Bool m_waitingForPath;
	char m_pad31f[0x326 - 0x31f];
	Bool m_isBlockedAndStuck;
};

class Thing
{
public:
	Bool isKindOf(KindOfType t) const;
	const Coord3D *getUnitDirectionVector2D() const;
};

class Player
{
public:
	PlayerType getPlayerType() const { return m_playerType; }

	char m_pad000[0x2c];
	PlayerType m_playerType;
};

class Object : public Thing
{
public:
	Bool isMobile() const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0);
	Player *getControllingPlayer() const;
	Bool crushPolicy(Object *otherObject, CrushSquishTestType test) const;
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	void *getPhysics() const { return m_physics; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }

	char m_pad000[0x38];
	Coord3D m_position;
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;
	char m_pad078[0x94 - 0x78];
	unsigned char m_byte94;
	char m_pad095[0x204 - 0x95];
	AIUpdateInterface *m_ai;
	void *m_physics;
	char m_pad20c[0x214 - 0x20c];
	void *m_dword214;
};

class Rva00027BC9Object : public Object
{
public:
	void getPosition(Coord3D *out);
};

class Weapon
{
public:
	char m_pad000[4];
	void *m_template;
};

class StateMachine
{
public:
	Object *getGoalObject();

	char m_pad000[0x10];
	Object *m_owner;
	char m_pad014[0x24 - 0x14];
	Coord3D m_goalPosition;
};

class Pathfinder
{
public:
	Bool adjustDestination(Object *object, const LocomotorSet &locomotorSet,
		Coord3D *destination, const Coord3D *groupDestination);
	void updateGoal(Object *object, const Coord3D *newGoalPosition,
		PathfindLayerEnum layer, const char *file, int line);
};

class TAiData
{
public:
	char m_pad000[0x8c];
	Bool m_aiCrushesInfantry;
};

class AI
{
public:
	char m_pad000[0xc];
	Pathfinder *m_pathfinder;
	char m_pad010[0x14 - 0x10];
	TAiData *m_aiData;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object, const Coord3D *position);
};

class GameLogic
{
public:
	char m_pad000[0x3c];
	unsigned int m_frame;
};

extern Bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern GameLogic *TheBfmeGameLogic;
extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);
Bool bfmeMeleeHordeTargetInvalid(Object *attacker, Object *target);

extern void j_0000142e();
extern void j_0000b8ac();
extern void j_0000ebab();
extern void j_0001041a();
extern void j_00032b46();
extern void j_0000e7dc();

class Rva00182360Receiver {};
template<class T> __forceinline T Rva00182360Member(void (*raw)())
{
	union { void (*raw)(); T member; } fn;
	fn.raw = raw;
	return fn.member;
}
#define CALL(T, obj, fn) (((Rva00182360Receiver *)(obj))->*Rva00182360Member<T>(fn))

typedef Bool (Rva00182360Receiver::*IsContactWeapon)();
typedef void (Rva00182360Receiver::*SetPathExtraDistance)(Real);
typedef Bool (Rva00182360Receiver::*IsTooClose)(Object *, Object *);
typedef Bool (Rva00182360Receiver::*Rva0026F330)();
typedef Bool (Rva00182360Receiver::*Rva0016EE00)(Coord3D *, Object *);
typedef Bool (Rva00182360Receiver::*Rva003F5E20)(Object *, const Coord3D *, Weapon *, Bool);

#define CRCDEBUG_LOG(msg) \
	if (Glo012F0239 && TheCRCParameterCheck) \
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, msg)

static __declspec(noinline) Bool isSamePosition(const Coord3D *ourPos,
	const Coord3D *prevTargetPos, const Coord3D *curTargetPos)
{
	Coord3D diff;
	diff.x = curTargetPos->x - prevTargetPos->x;
	diff.y = curTargetPos->y - prevTargetPos->y;
	Coord3D toTarget;
	toTarget.x = curTargetPos->x - ourPos->x;
	toTarget.y = curTargetPos->y - ourPos->y;
	const float TOLERANCE_FACTOR = 1.0f / (10.0f * 10.0f);
	float toleranceSqr = (toTarget.x*toTarget.x+toTarget.y*toTarget.y) * TOLERANCE_FACTOR;
	if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
		return false;
	return true;
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

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur == TURRET_INVALID)
		return false;

	if (TheAI->m_aiData->m_aiCrushesInfantry)
	{
		if (attacker->getControllingPlayer() &&
			(attacker->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER) &&
			attacker->crushPolicy(target, TEST_CRUSH_OR_SQUISH))
			return true;
	}

	if (CALL(IsTooClose, weapon, j_0000e7dc)(attacker, target))
		return false;

	Real ourMaxSpeed = attacker->getAI()->getCurLocomotorSpeed();
	Real victimSpeed = target->bfmeGetNonnegativePreferredLocomotorHeight();
	if (victimSpeed >= ourMaxSpeed)
		return false;
	if (victimSpeed < ourMaxSpeed * 0.1f)
		return false;
	Real dx = target->getPosition()->x - attacker->getPosition()->x;
	Real dy = target->getPosition()->y - attacker->getPosition()->y;
	const Coord3D *dir = target->getUnitDirectionVector2D();
	Coord3D victimVector;
	victimVector.x = dir->x;
	victimVector.y = dir->y;
	if (dx*victimVector.x + dy*victimVector.y < 0)
		return false;
	return true;
}

template<int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BFMEVirtualSlots<0>
{
};

class AIInternalMoveToState : public BFMEVirtualSlots<17>
{
public:
	virtual Bool computePath();
	virtual int update();
};

class AIAttackPursueTargetState : public AIInternalMoveToState
{
public:
	virtual Bool computePath();

private:
	char m_pad004[0x1c - 0x04];
	StateMachine *m_machine;
	char m_pad020[4];
	Coord3D m_goalPosition;
	char m_pad030[0x4c - 0x30];
	Bool m_waitingForPathSet;
	Bool m_isWaitingForPathCache;
	char m_pad04e[0x50 - 0x4e];
	Coord3D m_prevVictimPos;
	unsigned int m_approachTimestamp;
	char m_pad060[0x62 - 0x60];
	Bool m_stopIfInRange;
	Bool m_isInitialApproach;
	Bool m_isForceAttacking;
};

Bool AIAttackPursueTargetState::computePath()
{
	CRCDEBUG_LOG("CritterDesync: ComputePath12");

	Bool forceRepath = false;
	if (m_machine->m_owner->isMobile() == false)
		return false;

	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	if (ai->m_isBlockedAndStuck)
		return false;
	if (m_isWaitingForPathCache)
		return true;

	if (!ai->m_path && !ai->m_waitingForPath)
		forceRepath = true;

	if (!forceRepath && TheBfmeGameLogic->m_frame - m_approachTimestamp < 5)
		return true;

	m_approachTimestamp = TheBfmeGameLogic->m_frame;
	if (m_machine->getGoalObject())
	{
		Object *source = m_machine->m_owner;
		if (!forceRepath && isSamePosition(&source->m_position, &m_prevVictimPos,
			m_machine->getGoalObject()->getPosition()))
			return true;

		Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return false;
		if (!canPursue(source, weapon, m_machine->getGoalObject()))
			return false;

		Object *victim = m_machine->getGoalObject();
		m_prevVictimPos = *victim->getPosition();
		CRCDEBUG_LOG("CritterDesync: setAdjustDestination(TRUE) 26");
		m_goalPosition = m_prevVictimPos;
		m_waitingForPathSet = true;
		ai->requestPath(&m_goalPosition, false);
		m_isWaitingForPathCache = ai->m_waitingForPath;
		m_stopIfInRange = false;
		return true;
	}

	return false;
}

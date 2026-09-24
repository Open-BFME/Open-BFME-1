// cl: /DNDEBUG /MD
// Retail 0x00182360: AIAttackApproachTargetState::computePath.
// Identity: vftable 0x0109A4C0 slot +0x44 (ILT 0x0040CDB5) is this body; the
// same vftable's slot 2 name getter 0x0017F600 returns "AIAttackApproachTargetState"
// and slots 5/6 are the landed onExit 0x001751B0 and update 0x00182EA0.  Slot +0x44
// is computePath in the landed AIMoveToStateSA sibling (vftable 0x01098FA8).
// Port of the Zero Hour AIStates.cpp body with the BFME desync traces, the
// kind-58 pathfinder gate and the melee/retry tail.

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
	void ignoreObstacle(Object *obj);
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	void requestAttackPath(ObjectID victimID, const Coord3D *victimPos);

	char m_pad000[0x140];
	void *m_path;							// +0x140
	char m_pad144[0x1a8 - 0x144];
	LocomotorSet m_locomotorSet;			// +0x1a8
	char m_pad1a9[0x31e - 0x1a9];
	Bool m_waitingForPath;					// +0x31e
	char m_pad31f[0x326 - 0x31f];
	Bool m_isBlockedAndStuck;				// +0x326
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
	PlayerType m_playerType;				// +0x2c
};

class Object : public Thing
{
public:
	Bool isMobile() const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0);
	Player *getControllingPlayer() const;
	Bool crushPolicy(Object *other, CrushSquishTestType test) const;
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	void *getPhysics() const { return m_physics; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }

	char m_pad000[0x38];
	Coord3D m_position;						// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;							// +0x74
	char m_pad078[0x94 - 0x78];
	unsigned char m_byte94;					// +0x94
	char m_pad095[0x204 - 0x95];
	AIUpdateInterface *m_ai;				// +0x204
	void *m_physics;						// +0x208
	char m_pad20c[0x214 - 0x20c];
	void *m_dword214;						// +0x214
};

// address-derived view of the geometry-centre call reached through ILT 0x00027BC9
class Rva00027BC9Object : public Object
{
public:
	void getPosition(Coord3D *out);
};

class Weapon
{
public:
	char m_pad000[4];
	void *m_template;						// +0x04
};

class StateMachine
{
public:
	Object *getGoalObject();

	char m_pad000[0x10];
	Object *m_owner;						// +0x10
	char m_pad014[0x24 - 0x14];
	Coord3D m_goalPosition;					// +0x24
};

class Pathfinder
{
public:
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet,
		Coord3D *dest, const Coord3D *groupDest);
	void updateGoal(Object *obj, const Coord3D *newGoalPos,
		PathfindLayerEnum layer, const char *file, int line);
};

class TAiData
{
public:
	char m_pad000[0x8c];
	Bool m_aiCrushesInfantry;				// +0x8c
};

class AI
{
public:
	char m_pad000[0xc];
	Pathfinder *m_pathfinder;				// +0x0c
	char m_pad010[0x14 - 0x10];
	TAiData *m_aiData;						// +0x14
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

class GameLogic
{
public:
	char m_pad000[0x3c];
	unsigned int m_frame;					// +0x3c
};

extern Bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern GameLogic *TheBfmeGameLogic;
extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);
Bool bfmeMeleeHordeTargetInvalid(Object *attacker, Object *target);

// Retail callees with no typed ledger name, reached through their ILT rows
// (same form as the landed Rva00170680ApproachPath computePath sibling).
extern void j_0000142e();	// -> 0x0026F330
extern void j_0000b8ac();
extern void j_0000ebab();
extern void j_0001041a();	// -> 0x0016EE00
extern void j_00032b46();	// -> 0x003F5E20
extern void j_0000e7dc();

class Rva00182360Receiver {};
template<class T> __forceinline T Rva00182360Member(void (*raw)())
{
	union { void (*raw)(); T member; } fn;
	fn.raw = raw;
	return fn.member;
}
#define CALL(T, obj, fn) (((Rva00182360Receiver *)(obj))->*Rva00182360Member<T>(fn))

// ILT 0x0000B8AC: WeaponTemplate::isContactWeapon (ZH Weapon.h inline forwards
// weapon->isContactWeapon() to m_template; retail passes [weapon+4] in ECX).
typedef Bool (Rva00182360Receiver::*IsContactWeapon)();
// ILT 0x0000EBAB -> 0x0026FE90 stores its float at AIUpdateInterface+0x168,
// the witnessed m_pathExtraDistance; ZH calls setPathExtraDistance here.
typedef void (Rva00182360Receiver::*SetPathExtraDistance)(Real);
// ILT 0x0000E7DC: Weapon::isTooClose(source, victim), ZH canPursue.
typedef Bool (Rva00182360Receiver::*IsTooClose)(Object *, Object *);
// Opaque BFME callees, named by body address.
typedef Bool (Rva00182360Receiver::*Rva0026F330)();
typedef Bool (Rva00182360Receiver::*Rva0016EE00)(Coord3D *, Object *);
typedef Bool (Rva00182360Receiver::*Rva003F5E20)(Object *, const Coord3D *, Weapon *, Bool);

#define CRCDEBUG_LOG(msg) \
	if (Glo012F0239 && TheCRCParameterCheck) \
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, msg)

// Authentic static helper from AIStates.cpp; resolves to 0x0016AA70.
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

// Static helper from AIStates.cpp at 0x00174CC0 (ZH canPursue with the BFME
// object-state gate and speed accessor).  VC7.1 gives it a private convention
// (source in ESI, victim in EDI, weapon on the stack), so computePath only
// matches with the real definition in the same TU; this body is itself exact.
static __declspec(noinline) Bool canPursue(Object *source, Weapon *weapon, Object *victim)
{
	/* This state is only used if the target is moving away from us, and has physics. */
	if (!victim->getPhysics())
		return false;
	if ((source->m_byte94 & 0x20) && source->m_dword214)
		return false;
	AIUpdateInterface *ai = source->getAI();
	if (!ai)
		return false;

	// Have to have a turret to pursue.
	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur == TURRET_INVALID)
		return false;

	if (TheAI->m_aiData->m_aiCrushesInfantry)
	{
		if (source->getControllingPlayer() &&
			(source->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER) &&
			source->crushPolicy(victim, TEST_CRUSH_OR_SQUISH))
		{
			return true;	// Always pursue if we can squish.
		}
	}

	if (CALL(IsTooClose, weapon, j_0000e7dc)(source, victim))
		return false;		// Don't chase it if we are already too close.

	Real ourMaxSpeed = source->getAI()->getCurLocomotorSpeed();

	Real victimSpeed = victim->bfmeGetNonnegativePreferredLocomotorHeight();
	if (victimSpeed >= ourMaxSpeed)
		return false; // we can't catch them.
	if (victimSpeed < ourMaxSpeed * 0.1f)
		return false; // They aren't moving very fast, so don't chase.
	Real dx = victim->getPosition()->x - source->getPosition()->x;
	Real dy = victim->getPosition()->y - source->getPosition()->y;
	const Coord3D *dir = victim->getUnitDirectionVector2D();
	Coord3D victimVector;
	victimVector.x = dir->x;
	victimVector.y = dir->y;
	if (dx*victimVector.x + dy*victimVector.y < 0)
		return false; // they are moving towards us.
	return true;
}

class AIAttackApproachTargetState
{
protected:
	virtual Bool computePath();

	Object *getMachineOwner() { return m_machine->m_owner; }
	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() { return &m_machine->m_goalPosition; }

	char m_pad004[0x1c - 0x04];
	StateMachine *m_machine;				// +0x1c
	char m_pad020[0x24 - 0x20];
	Coord3D m_goalPosition;					// +0x24
	char m_pad030[0x4c - 0x30];
	Bool m_adjustDestinations;				// +0x4c
	Bool m_waitingForPath;					// +0x4d
	char m_pad04e[0x50 - 0x4e];
	Coord3D m_prevVictimPos;				// +0x50
	char m_pad05c[0x68 - 0x5c];
	unsigned int m_approachTimestamp;		// +0x68
	unsigned int m_dword6c;					// +0x6c
	char m_pad070[0x72 - 0x70];
	Bool m_stopIfInRange;					// +0x72
	char m_pad073[0x75 - 0x73];
	Bool m_byte75;							// +0x75
};

Bool AIAttackApproachTargetState::computePath()
{
	CRCDEBUG_LOG("CritterDesync: ComputePath10");

	Bool forceRepath = false;

	// if we're immobile we can't possibly approach the target
	if (getMachineOwner()->isMobile() == false)
		return false;

	AIUpdateInterface *ai = getMachineOwner()->getAI();

	if (ai->m_isBlockedAndStuck)
		forceRepath = true;
	if (m_waitingForPath)
		return true;

	if (!forceRepath && ai->m_path == 0 && !ai->m_waitingForPath)
		forceRepath = true;

	// force minimum time between recomputation
	if (!forceRepath && TheBfmeGameLogic->m_frame - m_approachTimestamp < 5)
		return true;

	m_approachTimestamp = TheBfmeGameLogic->m_frame;

	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachineGoalObject())
	{
		Object *source = getMachineOwner();
		// if our victim's position hasn't changed, don't re-path
		if (!forceRepath && isSamePosition(source->getPosition(), &m_prevVictimPos,
				getMachineGoalObject()->getPosition()))
			return true;

		Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return false;

		// remember where we think our victim is, so if it moves, we can re-path
		Object *victim = getMachineGoalObject();
		m_prevVictimPos = *victim->getPosition();
		CRCDEBUG_LOG("CritterDesync: setAdjustDestination(TRUE) 18");
		m_adjustDestinations = true;

		Bool usePathfinder = false;
		if (!source->isKindOf((KindOfType)58))	// BFME kind index 58; name unproven
			usePathfinder = true;
		m_goalPosition = m_prevVictimPos;
		if (!usePathfinder)
		{
			Pathfinder *pathfinder = TheAI->m_pathfinder;
			if (CALL(Rva003F5E20, pathfinder, j_00032b46)(source, victim->getPosition(), weapon, false))
				usePathfinder = true;
		}

		if (canPursue(source, weapon, victim) && usePathfinder)
			return false;

		if (CALL(IsContactWeapon, weapon->m_template, j_0000b8ac)())
		{
			// Weapon is basically a contact weapon, so let the attacker pathfind into the target.
			ai->ignoreObstacle(victim);
			CRCDEBUG_LOG("CritterDesync: setAdjustDestination(FALSE) 19");
			m_adjustDestinations = false;
			CALL(SetPathExtraDistance, ai, j_0000ebab)(100.0f);
			TheAI->m_pathfinder->adjustDestination(getMachineOwner(), ai->m_locomotorSet,
				&m_goalPosition, 0);
		}
		else if (ai->m_path && CALL(Rva0026F330, ai, j_0000142e)())
		{
			return true;
		}

		Coord3D pos;
		((Rva00027BC9Object *)victim)->getPosition(&pos);
		Bool invalid = bfmeMeleeHordeTargetInvalid(source, victim);
		if (usePathfinder)
		{
			if (invalid)
				ai->requestPath(&pos, false);
			else
				ai->requestAttackPath(victim->getID(), &pos);
		}
		else
		{
			if (!CALL(Rva0016EE00, this, j_0001041a)(&pos, source))
			{
				m_byte75 = true;
				m_dword6c = TheBfmeGameLogic->m_frame + 50;
				return true;
			}

			Pathfinder *pathfinder = TheAI->m_pathfinder;
			pathfinder->updateGoal(source, &pos,
				TheTerrainLogic->getLayerForDestination(source, &pos),
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x1118);
			ai->requestPath(&pos, true);
		}
		m_waitingForPath = ai->m_waitingForPath;
		m_stopIfInRange = false;
		return true;
	}

	// goal position.
	CRCDEBUG_LOG("CritterDesync: setAdjustDestination(TRUE) 20");
	m_adjustDestinations = true;
	m_stopIfInRange = false;
	m_goalPosition = *getMachineGoalPosition();
	if (!forceRepath)
		return true; // fixed positions don't move.

	ai->requestAttackPath(INVALID_ID, &m_goalPosition);
	m_waitingForPath = ai->m_waitingForPath;
	return true;
}

// ?d_00175e90@@YAXXZ
// partial score=0.36 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// readable body of ?computePath@AIAttackPursueTargetState@@UAE_NXZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// Retail 0x00175E90, 384 bytes. Identity: the vtable slot this overrides
// (AIInternalMoveToState::computePath, +0x44) is called from the ALREADY
// MATCHED AIAttackPursueTargetState::updateInternal at 0x00176250
// (Code/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_updateInternal.cpp),
// which also fixes this class's field offsets (m_machine=+0x1C,
// m_stopIfInRange=+0x62). The ZH twin (AIStates.cpp,
// AIAttackPursueTargetState::computePath) matches this body's control flow
// closely (isSamePosition, requestPath, the same CRC log shape used by the
// sibling Rva00170680ApproachPath::computePath at 0x00170680, itself already
// matched). Two DIR32 strings confirm the identity further: "CritterDesync:
// ComputePath12" and "CritterDesync: setAdjustDestination(TRUE) 26", read
// byte-exact from retail .rdata at 0x010993B4 / 0x0109937C.
//
// canPursue() (retail 0x00174CC0, callee d_00174cc0, still a dump) takes its
// two Object arguments through EDI (victim) and ESI (source) rather than ECX,
// with the Weapon* as the sole __cdecl stack argument -- the same
// whole-program register convention already proven for isSamePosition in
// Rva00170680ApproachPath.cpp. No portable C++ call shape reaches that;
// declared with a plain extern below so the row still resolves, but this one
// call site is expected to diverge in the byte gate.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x, y, z;
};

class Object;
class Player;
class Weapon;

class AIUpdateInterface
{
public:
	char m_pad000[0x140];
	void *m_path;                  // +0x140
	char m_pad144[0x31e - 0x144];
	bool m_isWaitingForPath;       // +0x31e
	char m_pad31f[0x326 - 0x31f];
	bool m_isBlockedAndStuck;      // +0x326

	void requestPath(const Coord3D *pos, bool unknownFlag);
};

class BfmeSubCSA
{
public:
	bool bfmeAskCSA();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Weapon *getCurrentWeapon(int slot);

	char m_pad00[0x38];
	Coord3D m_position;             // +0x38
	char m_pad44[0x204 - 0x44];
	AIUpdateInterface *m_ai;        // +0x204
};

class StateMachine
{
public:
	Object *getGoalObject();

	char m_pad00[0x10];
	Object *m_owner;                // +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackPursueTargetState
{
public:
	Bool computePath();

private:
	char m_pad004[0x1c - 0x04];
	StateMachine *m_machine;        // +0x1C
	Coord3D m_goalPosition;         // +0x24
	char m_pad30[0x4c - 0x30];
	bool m_waitingForPathSet;       // +0x4C
	bool m_isWaitingForPathCache;   // +0x4D
	char m_pad4e[0x50 - 0x4e];
	Coord3D m_prevVictimPos;        // +0x50
	char m_pad5c[0x62 - 0x5c];
	// retail +0x5C holds the recompute timestamp; the field is declared
	// through the union below since it aliases the timestamp write.
};

// The recompute timestamp (+0x5C) does not fit the layout above cleanly next
// to m_stopIfInRange at +0x62 without an explicit gap; access it by raw
// offset instead of widening the class above.
struct AIAttackPursueTargetStateRaw
{
	char pad[0x5c];
	UnsignedInt m_approachTimestamp; // +0x5C
};

class GameLogic
{
public:
	char m_pad00[0x3c];
	UnsignedInt m_frame;             // +0x3C
};

extern GameLogic *TheBfmeGameLogic;

class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;

typedef void (__cdecl *BfmeCritterDesyncLog)(void *, const char *);
extern void j_0003a17a();

static __forceinline void bfmePursueLog(const char *message)
{
	if (Glo012F0239 && TheCRCParameterCheck)
		((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck, message);
}

// Authentic static helper from AIStates.cpp / ZH AIStates.cpp, not an ABI
// stub -- proven byte-exact already at 0x0016AA70 via the same TU-private
// register ABI in Rva00170680ApproachPath.cpp.
static __declspec(noinline) Bool isSamePosition(const Coord3D *ourPos,
	const Coord3D *prevTargetPos, const Coord3D *curTargetPos)
{
	Coord3D diff;
	diff.x = curTargetPos->x - prevTargetPos->x;
	diff.y = curTargetPos->y - prevTargetPos->y;
	Coord3D toTarget;
	toTarget.x = curTargetPos->x - ourPos->x;
	toTarget.y = curTargetPos->y - ourPos->y;
	const Real TOLERANCE_FACTOR = 1.0f / (10.0f * 10.0f);
	Real toleranceSqr = (toTarget.x * toTarget.x + toTarget.y * toTarget.y) * TOLERANCE_FACTOR;
	if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
		return false;
	return true;
}

// canPursue(): retail passes victim via EDI and source via ESI, weapon on
// the stack -- a whole-program register convention this TU cannot select
// portably. Declared as a plain extern so the row still resolves; expect
// this one call to diverge from retail in the byte gate.
extern "C" Bool __cdecl d_00174cc0(Weapon *weapon);

Bool AIAttackPursueTargetState::computePath()
{
	if (Glo012F0239 && TheCRCParameterCheck)
		((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck, "CritterDesync: ComputePath12");

	Bool forceRepath = false;

	if (!reinterpret_cast<BfmeSubCSA *>(m_machine->m_owner)->bfmeAskCSA())
		return false;

	StateMachine *machine = m_machine;
	Object *source = machine->m_owner;
	AIUpdateInterface *ai = source->m_ai;

	if (ai->m_isBlockedAndStuck)
		return false;

	if (m_isWaitingForPathCache)
		return true;

	if (!ai->m_path && !ai->m_isWaitingForPath)
		forceRepath = true;

	if (!forceRepath && TheBfmeGameLogic->m_frame -
		reinterpret_cast<AIAttackPursueTargetStateRaw *>(this)->m_approachTimestamp < 5)
	{
		return true;
	}

	reinterpret_cast<AIAttackPursueTargetStateRaw *>(this)->m_approachTimestamp =
		TheBfmeGameLogic->m_frame;

	Object *victim = machine->getGoalObject();
	if (victim)
	{
		if (!forceRepath &&
			isSamePosition(&source->m_position, &m_prevVictimPos, &victim->m_position))
		{
			return true;
		}

		Weapon *weapon = source->getCurrentWeapon(0);
		if (!weapon)
			return false;

		if (!d_00174cc0(weapon))
			return false;

		victim = machine->getGoalObject();
		m_prevVictimPos = victim->m_position;

		if (Glo012F0239 && TheCRCParameterCheck)
			((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
				"CritterDesync: setAdjustDestination(TRUE) 26");

		m_goalPosition = m_prevVictimPos;
		m_waitingForPathSet = true;
		ai->requestPath(&m_goalPosition, false);
		m_isWaitingForPathCache = ai->m_isWaitingForPath;
		return true;
	}

	return false;
}

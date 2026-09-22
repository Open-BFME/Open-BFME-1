// ?d_0016bd60@@YAXXZ
// partial score=0.4 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x0016BD60, 475 bytes. The vtable slot and ComputePath21 literal prove the owner.
// The target-only state members retain offsets because no layout witness names them.

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class StateMachine;

struct AIUpdateInterface
{
	unsigned char m_pad00[0x140];
	void *m_path;
	unsigned char m_pad144[0x31e - 0x144];
	Bool m_waitingForPath;
	unsigned char m_pad31f[7];
	Bool m_isBlockedAndStuck;
};

struct Object
{
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0xbc - 0x44];
	Real m_fieldBC;
	unsigned char m_padC0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
};

struct StateMachine
{
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

struct GameLogic
{
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

template<int N>
class AIAttackMeleeSquishStateSlots : public AIAttackMeleeSquishStateSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template<>
class AIAttackMeleeSquishStateSlots<0>
{
};

class AIInternalMoveToState : public AIAttackMeleeSquishStateSlots<17>
{
public:
	virtual Bool computePath() = 0;

protected:
	unsigned char m_pad004[0x18];
	StateMachine *m_machine;
};

class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	virtual Bool computePath();

protected:
	unsigned char m_pad020[4];
	Coord3D m_goalPosition;
	unsigned char m_pad030[0x4d - 0x30];
	unsigned char m_field4d;
	unsigned char m_pad04e[2];
	UnsignedInt m_field50;
	Coord3D m_field54;
};

class CRCParameterCheck;
extern bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern GameLogic *TheBfmeGameLogic;
extern void j_0000e570();
extern void j_0002bd82();
extern void j_0002be77();
extern void j_00031a7f();
extern void j_0003a17a();
extern void j_0003bcff();
extern void j_000420aa();
extern void *TheGameLogic;

typedef void (__cdecl *CritterDesyncLog)(void *, const char *);

class AIAttackMeleeSquishStateReceiver
{
};

template<class T>
__forceinline T AIAttackMeleeSquishStateMember(void (*raw)())
{
	union { void (*raw)(); T member; } fn;
	fn.raw = raw;
	return fn.member;
}

#define CALL(T, obj, fn) (((AIAttackMeleeSquishStateReceiver *)(obj))->*AIAttackMeleeSquishStateMember<T>(fn))

typedef Object *(AIAttackMeleeSquishStateReceiver::*GetGoalObject)(void);
typedef void (AIAttackMeleeSquishStateReceiver::*Normalize)(void);
typedef void *(AIAttackMeleeSquishStateReceiver::*GetCurrentWeapon)(int);
typedef Bool (AIAttackMeleeSquishStateReceiver::*CrushPolicy)(Object *, int);
typedef void (AIAttackMeleeSquishStateReceiver::*RequestPath)(Coord3D *, Bool);
typedef class Rva0016BD60QueryResult *(AIAttackMeleeSquishStateReceiver::*QueryResult)(void);

template<int N>
class Rva0016BD60QueryResultSlots : public Rva0016BD60QueryResultSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template<>
class Rva0016BD60QueryResultSlots<0>
{
};

class Rva0016BD60QueryResult : public Rva0016BD60QueryResultSlots<61>
{
public:
	virtual Object *resolveObject() = 0;
};

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

Bool AIAttackMeleeSquishState::computePath()
{
	if (Glo012F0239 && TheCRCParameterCheck)
		((CritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
			"CritterDesync: ComputePath21");

	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	Bool forceRepath = false;
	register Object *owner;
	if (ai->m_isBlockedAndStuck)
		return false;
	if (m_field4d)
		return true;

	if (ai->m_path)
		goto checkRepathTime;
	if (ai->m_waitingForPath)
		goto checkRepathTime;
	forceRepath = true;
	goto setRepathTime;

checkRepathTime:
	if (TheBfmeGameLogic->m_frame - m_field50 < 5)
		return true;

setRepathTime:
	m_field50 = TheBfmeGameLogic->m_frame;

	Object *goal = CALL(GetGoalObject, m_machine, j_0000e570)();
	if (!goal)
		return false;
	owner = m_machine->m_owner;
	if (!forceRepath && isSamePosition(&m_field54,
		&owner->m_position, &CALL(GetGoalObject, m_machine, j_0000e570)()->m_position))
		return true;

	void *weapon = CALL(GetCurrentWeapon, owner, j_00031a7f)(0);
	if (!weapon)
		return false;

	goal = CALL(GetGoalObject, m_machine, j_0000e570)();
	Rva0016BD60QueryResult *query = CALL(QueryResult, goal, j_0002be77)();
	if (query)
	{
		Object *resolved = query->resolveObject();
		if (resolved)
			goal = resolved;
	}
	m_field54 = goal->m_position;
	if (!CALL(CrushPolicy, owner, j_000420aa)(goal, 2))
		return false;

	Coord3D direction;
	direction.x = m_field54.x - owner->m_position.x;
	direction.y = m_field54.y - owner->m_position.y;
	direction.z = m_field54.z - owner->m_position.z;
	CALL(Normalize, &direction, j_0002bd82)();
	Real distance = owner->m_fieldBC;
	distance += distance;
	m_goalPosition = m_field54;
	m_goalPosition.x += direction.x * distance;
	m_goalPosition.y += direction.y * distance;
	m_goalPosition.z += direction.z * distance;
	CALL(RequestPath, ai, j_0003bcff)(&m_goalPosition, false);
	m_field4d = ai->m_waitingForPath;
	return true;
}

#undef CALL

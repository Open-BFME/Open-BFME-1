// ?computePath@AIAttackMeleeSquishState@@MAE_NXZ
// cl: /DNDEBUG /MD /EHsc
// Retail 0x0016BD60, 475 bytes. Vtable 0x0109A738 (ctor 0x0017F860) slot 17 holds its thunk 0x00431584.

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

enum WeaponSlotType {};
enum CrushSquishTestType { TEST_CRUSH_ONLY, TEST_SQUISH_ONLY, TEST_CRUSH_OR_SQUISH };

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void normalize();
	void set(const Coord3D *other) { x = other->x; y = other->y; z = other->z; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
	void scale(Real scale) { x *= scale; y *= scale; z *= scale; }
};

class Object;
class Weapon;
class CRCParameterCheck;

class AIUpdateInterface
{
public:
	void requestPath(Coord3D *destination, Bool isFinalGoal);

	unsigned char m_pad00[0x140];
	void *m_path;
	unsigned char m_pad144[0x31e - 0x144];
	Bool m_waitingForPath;
	unsigned char m_pad31f[7];
	Bool m_isBlockedAndStuck;
};

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

class Rva001CF980Result : public Rva0016BD60QueryResult {};

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0);
	Rva001CF980Result *queryAt001CF980();
	Bool crushPolicy(Object *otherObject, CrushSquishTestType test) const;
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }

	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0xbc - 0x44];
	Real m_fieldBC;
	unsigned char m_padC0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	Object *getGoalObject();

	unsigned char m_pad00[0x10];
	Object *m_owner;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern Bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern GameLogic *TheGameLogic;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);

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
	const Real TOLERANCE_FACTOR = 1.0f / (10.0f * 10.0f);
	Real toleranceSqr = (toTarget.x * toTarget.x + toTarget.y * toTarget.y) * TOLERANCE_FACTOR;
	if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
		return false;
	return true;
}

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
protected:
	virtual Bool computePath() = 0;

	unsigned char m_pad004[0x18];
	StateMachine *m_machine;
};

class AIAttackMeleeSquishState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();

	unsigned char m_pad020[4];
	Coord3D m_goalPosition;
	unsigned char m_pad030[0x4d - 0x30];
	unsigned char m_field4d;
	unsigned char m_pad04e[2];
	UnsignedInt m_field50;
	Coord3D m_field54;
};

Bool AIAttackMeleeSquishState::computePath()
{
	CRCDEBUG_LOG("CritterDesync: ComputePath21");

	AIUpdateInterface *ai = m_machine->m_owner->getAI();
	Bool forceRepath = false;
	if (ai->m_isBlockedAndStuck)
		return false;
	if (m_field4d)
		return true;

	if (!ai->m_path && !ai->m_waitingForPath)
		forceRepath = true;

	if (!forceRepath && TheGameLogic->m_frame - m_field50 < 5)
		return true;

	m_field50 = TheGameLogic->m_frame;
	if (m_machine->getGoalObject())
	{
		Object *source = m_machine->m_owner;
		if (!forceRepath && isSamePosition(source->getPosition(), &m_field54,
			m_machine->getGoalObject()->getPosition()))
			return true;

		Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return false;

		Object *victim = m_machine->getGoalObject();
		Rva001CF980Result *query = victim->queryAt001CF980();
		if (query)
		{
			Object *resolved = query->resolveObject();
			if (resolved)
				victim = resolved;
		}
		m_field54 = *victim->getPosition();
		if (source->crushPolicy(victim, TEST_CRUSH_OR_SQUISH))
		{
			// Scoped so direction is dead at the requestPath call.
			{
				Coord3D direction;
				direction.set(&m_field54);
				direction.sub(source->getPosition());
				direction.normalize();
				Real distance = source->m_fieldBC + source->m_fieldBC;
				direction.scale(distance);
				m_goalPosition = m_field54;
				m_goalPosition.add(&direction);
			}
			ai->requestPath(&m_goalPosition, false);
			m_field4d = ai->m_waitingForPath;
			return true;
		}
	}

	return false;
}

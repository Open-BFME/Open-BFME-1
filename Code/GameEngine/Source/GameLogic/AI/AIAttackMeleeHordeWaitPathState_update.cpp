// cl: /DNDEBUG /MD /EHsc
// AIAttackMeleeHordeWaitPathState::update at retail 0x00175C80.
// The constructor at 0x00171120 passes AIAttackMeleeHordeWaitPathState to the
// state base and clears the two fields used below.  The adjacent onEnter body
// at 0x00175C00 confirms the state-machine field layout.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -1,
	STATE_SUCCESS = -2
};

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_MELEE_HORDE_TARGET = 92
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ObjectID
{
	OBJECT_ID_NONE = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Module;

class StateMachine
{
public:
	Bool isGoalObjectDestroyed() const;
	Object *getGoalObject();

	unsigned char m_pad000[0x10];
	Object *m_owner;
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	Module *findModule(NameKeyType key) const;
};

class BfmeAttackQuery
{
public:
	Bool bfmeCanAttackTarget(const Object *source, const Coord3D *sourcePosition,
		const Object *target, const void *unused) const;
};

class Pathfinder
{
public:
	Bool slowDoesPathExist(Object *source, const Coord3D *sourcePosition,
		const Coord3D *targetPosition, ObjectID objectID);
};

class AI
{
public:
	unsigned char m_pad000[0x0c];
	BfmeAttackQuery *m_attackQuery;

	BfmeAttackQuery *attackQuery() const
	{
		return m_attackQuery;
	}

	Pathfinder *pathfinder() const
	{
		return reinterpret_cast<Pathfinder *>(m_attackQuery);
	}
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GameLogic
{
public:
	unsigned char m_pad000[0x3c];
	UnsignedInt m_frame;
};

extern AI *TheAI;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;
extern void j_00048112();

class AIAttackMeleeHordeWaitPathState
{
public:
	virtual StateReturnType update();

private:
	unsigned char m_pad004[0x18];
	StateMachine *m_machine;
	unsigned char m_pad020[4];
	UnsignedInt m_waitUntil;
	int m_retryCount;
};

StateReturnType AIAttackMeleeHordeWaitPathState::update()
{
	Object *source = m_machine->m_owner;
	switch (m_machine->isGoalObjectDestroyed())
	{
	default:
		return STATE_FAILURE;
	case 0:
	{
		Object *target = m_machine->getGoalObject();
		if (target == 0)
			return STATE_FAILURE;

		UnsignedInt frame = TheGameLogic->m_frame;
		if (m_waitUntil > frame)
			return STATE_CONTINUE;

		Bool canAttack = false;
		if (target->isKindOf(KINDOF_STRUCTURE))
			canAttack = TheAI->attackQuery()->bfmeCanAttackTarget(
				source, source->getPosition(), target, 0);

		if (target->isKindOf(KINDOF_MELEE_HORDE_TARGET))
		{
			static NameKeyType siegeDeploySpecialPowerKey =
				TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
			Module *module = target->findModule(siegeDeploySpecialPowerKey);
			if (module != 0 && ((Bool (__fastcall *)(Module *))j_00048112)(module))
				goto success;
		}

		if (canAttack)
			goto success;
		if (TheAI->pathfinder()->slowDoesPathExist(
				source, source->getPosition(), target->getPosition(), OBJECT_ID_NONE))
			goto success;
		goto retry;

		success:
		__asm { }
		return STATE_SUCCESS;

		retry:
		m_waitUntil = TheGameLogic->m_frame + 7;
		return ++m_retryCount <= 5 ? STATE_CONTINUE : STATE_FAILURE;
	}
	}
}

// cl: /DNDEBUG /MD
// Byte candidate for retail 0x0017DB30; owning class remains unknown.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum ObjectID
{
	INVALID_ID = 0
};

enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0
};

#include "../command_source_type.h"

enum CanEnterType
{
	CHECK_CAPACITY = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

class StateMachine
{
public:
	Object *getGoalObject();
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(int);
	virtual StateReturnType update();

protected:
	unsigned char m_unreconstructed_004[ 0x18 ];
	StateMachine *m_machine;
	unsigned char m_unreconstructed_020[ 4 ];
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_030[ 0x1c ];
	unsigned char m_adjustDestinations;
};

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

class BFMEAIUpdateCommandSource : public BFMEVirtualSlots<128>
{
public:
	virtual CommandSourceType getLastCommandSource() const = 0;
};

class BFMEActionManager
{
public:
	bool canEnterObject(const Object *, const Object *, CommandSourceType,
		CanEnterType, bool *);
};

class BFMEContainPosition : public BFMEVirtualSlots<81>
{
public:
	virtual const Coord3D *getContainedObjectPosition() = 0;
};

class BFMEEnterContain : public BFMEVirtualSlots<13>
{
public:
	virtual void onObjectWantsToEnterOrExit(Object *, ObjectEnterExitType) = 0;
};

class AIUpdateInterface
{
public:
	void ignoreObstacle(Object *obstacle);
};

class Object
{
};

class Rva0017DB30State : public AIInternalMoveToState
{
public:
	StateReturnType onEnter();

private:
	ObjectID m_entryToClear;
	ObjectID m_currentVictimID;
};

struct BFMEObjectAI
{
	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface **)((char *)this + 0x204);
	}
};

extern BFMEActionManager *TheActionManager;
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0000e570();
extern void j_000261a2();
extern void j_0003a17a();

typedef Object *(__fastcall *BFMEGetGoalObject)(StateMachine *);
typedef Object *(__fastcall *BFMEGetCurrentVictim)(AIUpdateInterface *);
typedef void (__cdecl *BFMECritterDesyncLog)(void *, const char *);

// ?d_0017db30@@YAXXZ present-unmatched

StateReturnType Rva0017DB30State::onEnter()
{
	ObjectID zero = (ObjectID)0;
	m_entryToClear = zero;
	Object *obj = *(Object **)((char *)m_machine + 0x10);
	Object *goal = ((BFMEGetGoalObject)j_0000e570)(m_machine);
	AIUpdateInterface *ai = ((BFMEObjectAI *)obj)->getAI();
	Object *victim = ((BFMEGetCurrentVictim)j_000261a2)(ai);
	Object *nullObject = (Object *)zero;
	if (victim != nullObject)
		m_currentVictimID = *(ObjectID *)((char *)victim + 0x74);
	else
		m_currentVictimID = zero;

	if (goal)
	{
		if (!TheActionManager->canEnterObject(
			obj, goal,
			((BFMEAIUpdateCommandSource *)((BFMEObjectAI *)obj)->getAI())->getLastCommandSource(),
			(CanEnterType)zero, (bool *)zero))
			return STATE_FAILURE;

		BFMEContainPosition *contain = *(BFMEContainPosition **)((char *)goal + 0x1fc);
		if (contain)
		{
			m_goalPosition = *contain->getContainedObjectPosition();
			((BFMEEnterContain *)contain)->onObjectWantsToEnterOrExit(obj, WANTS_TO_ENTER);
			m_entryToClear = *(ObjectID *)((char *)goal + 0x74);
		}
		else
		{
			m_goalPosition = *(Coord3D *)((char *)goal + 0x38);
		}
	}
	else
	{
		return STATE_FAILURE;
	}

	ai->ignoreObstacle(((BFMEGetGoalObject)j_0000e570)(m_machine));
	void *locomotor = *(void **)((char *)ai + 0x1cc);
	if (locomotor)
		*(unsigned int *)((char *)locomotor + 0x40) |= 2;
	if (g_012F0239 && g_012ED4FC)
		((BFMECritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(FALSE) 59");
	m_adjustDestinations = 0;
	return AIInternalMoveToState::onEnter();
}

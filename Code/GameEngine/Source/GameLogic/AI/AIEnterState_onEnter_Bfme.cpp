// cl: /DNDEBUG /MD
// Retail 0x0017D8C0: BFME AIEnterState entry path.

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

enum CommandSourceType
{
	CMD_FROM_AI = 0
};

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
	void ignoreObstacle(Object *);
};

class Object
{
};

class AIEnterState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	ObjectID m_entryToClear;
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
extern void j_0003a17a();

typedef Object *(__fastcall *BFMEGetGoalObject)(StateMachine *);
typedef void (__cdecl *BFMECritterDesyncLog)(void *, const char *);

StateReturnType AIEnterState::onEnter()
{
	m_entryToClear = (ObjectID)0;
	Object *obj = *(Object **)((char *)m_machine + 0x10);
	Object *goal = ((BFMEGetGoalObject)j_0000e570)(m_machine);
	if (goal)
	{
		if( !TheActionManager->canEnterObject(
			obj, goal,
			((BFMEAIUpdateCommandSource *)((BFMEObjectAI *)obj)->getAI())->getLastCommandSource(),
			CHECK_CAPACITY, 0 ) )
			return STATE_FAILURE;

		BFMEContainPosition *contain = *(BFMEContainPosition **)((char *)goal + 0x1fc);
		if( contain )
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

	AIUpdateInterface *ai = ((BFMEObjectAI *)obj)->getAI();
	ai->ignoreObstacle(((BFMEGetGoalObject)j_0000e570)(m_machine));
	void *locomotor = *(void **)((char *)ai + 0x1cc);
	if (locomotor)
		*(unsigned int *)((char *)locomotor + 0x40) |= 2;
	if (g_012F0239 && g_012ED4FC)
		((BFMECritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(FALSE) 57");
	m_adjustDestinations = 0;
	return AIInternalMoveToState::onEnter();
}

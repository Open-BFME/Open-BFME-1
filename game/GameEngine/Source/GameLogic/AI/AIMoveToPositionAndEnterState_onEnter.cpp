// cl: /DNDEBUG /MD /EHsc

enum StateReturnType
{
};
typedef unsigned char UnsignedByte;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class StateMachine;
class Object;
class AIUpdateInterface
{
public:
	void setDesiredSpeed(float speed);
};
class AIGroup;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
// Declared only to spell the callee ?onEnter@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ
// (0x00021E27, its retail thunk, defined in AIInternalMoveToStateThunks.cpp).
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

struct BfmeMoveStateFields
{
	UnsignedByte m_padding00[0x1c];
	StateMachine *m_machine;
	UnsignedByte m_padding20[4];
	Coord3D m_goalPosition;
	UnsignedByte m_padding30[0x1c];
	UnsignedByte m_adjustDestinations;
};

extern UnsignedByte g_012F0239;
extern void *g_012ED4FC;
extern void j_0000e570();
extern void j_00012f17();
extern void j_000300bc();
extern void j_0003a17a();

typedef void (__cdecl *CritterDesyncLog)(void *, const char *);
typedef Object *(__fastcall *GetGoalObject)(StateMachine *);
typedef AIGroup *(__fastcall *GetGroup)(AIUpdateInterface *);
typedef float (__fastcall *GetSpeed)(AIGroup *);
typedef const Coord3D *(__fastcall *GetContainedObjectPosition)(void *);

class AIMoveToPositionAndEnterState
{
public:
	virtual StateReturnType onEnter();
};

// ?onEnter@AIMoveToPositionAndEnterState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveToPositionAndEnterState::onEnter()
{
	BfmeMoveStateFields *self = (BfmeMoveStateFields *)this;
	if (g_012F0239 && g_012ED4FC)
	{
		((CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(FALSE) 61");
	}

	self->m_adjustDestinations = 0;
	Object *goal = ((GetGoalObject)j_0000e570)(self->m_machine);
	void *contain = *(void **)((UnsignedByte *)goal + 0x1fc);
	const Coord3D *position = ((GetContainedObjectPosition)
		(*(void ***)contain)[0x148 / sizeof(void *)])(contain);
	self->m_goalPosition = *position;
	StateReturnType ret = ((AIInternalMoveToState *)self)->AIInternalMoveToState::onEnter();

	Object *owner = *(Object **)((UnsignedByte *)self->m_machine + 0x10);
	if (*(void **)((UnsignedByte *)owner + 0x31c))
	{
		AIUpdateInterface *ai = *(AIUpdateInterface **)((UnsignedByte *)owner + 0x204);
		AIGroup *group = ((GetGroup)j_00012f17)(ai);
		if (group)
		{
			ai->setDesiredSpeed(((GetSpeed)j_000300bc)(group));
		}
	}
	return ret;
}

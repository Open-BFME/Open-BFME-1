// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail 0x00172180: BFME AIIdleState initialises its idle movement goal.

typedef unsigned char Bool;
typedef float Real;

class Object;
class BfmeIdleGoalResult;
class Pathfinder;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;
	virtual void slot097() = 0;
	virtual void slot098() = 0;
	virtual void slot099() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual void slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115() = 0;
	virtual void slot116() = 0;
	virtual void slot117() = 0;
	virtual void slot118() = 0;
	virtual void slot119() = 0;
	virtual void slot120() = 0;
	virtual void slot121() = 0;
	virtual void setLocomotorGoalNone() = 0;
	virtual Bool isDoingGroundMovement() const = 0;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	unsigned char m_padding000[0x38];
	Coord3D m_position;
	unsigned char m_padding044[0x50];
	unsigned char m_status;
	unsigned char m_padding095[0x204 - 0x95];
	AIUpdateInterface *m_ai;
	unsigned char m_padding208[0x214 - 0x208];
	Object *m_containedBy;
};

class BfmeAIUpdateVictimThunk
{
public:
	void clearCurrentVictim(const Object *victim);
};

class StateMachine
{
public:
	unsigned char m_padding000[0x10];
	Object *m_owner;
};

class AIIdleState
{
	unsigned char m_padding000[0x1c];
	StateMachine *m_machine;
	unsigned char m_padding020[7];
	Bool m_inited;

	void doInitIdleState();
};

class Pathfinder
{
public:
	void removeGoal(Object *obj);
	void updateGoal(Object *obj, const Coord3D *pos, int layer, const char *file, int line);
};

class AI
{
public:
	unsigned char m_padding000[0x0c];
	Pathfinder *m_pathfinder;
};

class BfmeIdleGoal
{
public:
	virtual void unused(char (*)[0]) = 0;
};

template<int N>
class BfmeIdleGoalSlots : public BfmeIdleGoalSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeIdleGoalSlots<0>
{
};

class BfmeIdleGoalResult : public BfmeIdleGoalSlots<118>
{
public:
	virtual void notifyIdle() = 0;
};

extern AI *TheAI;
extern const Real BfmeZeroRange;

#pragma comment(linker, "/alternatename:?removeGoal@Pathfinder@@QAEXPAVObject@@@Z=?j_00015d02@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@HPBDH@Z=?j_000294e2@@YAXXZ")
extern void j_0002be77();
extern void j_0003a391();
typedef BfmeIdleGoalResult *(__fastcall *GetIdleGoal)(Object *);
typedef int (__fastcall *GetLayer)(Object *);

void AIIdleState::doInitIdleState()
{
	if (!m_inited)
		return;

	m_inited = false;
	Object *obj = m_machine->m_owner;
	AIUpdateInterface *ai = obj->m_ai;
	Bool updateGoal = true;

	if ((obj->m_status & 0x20) != 0)
	{
		Object *containedBy = obj->m_containedBy;
		updateGoal = false;
		if (containedBy)
		{
			AIUpdateInterface *containedAI = containedBy->m_ai;
			if (containedAI)
				updateGoal = containedAI->isIdle();
		}
	}

	BfmeIdleGoalResult *idleGoal = ((GetIdleGoal)j_0002be77)(obj);
	if (idleGoal)
	{
		idleGoal->notifyIdle();
		updateGoal = false;
		TheAI->m_pathfinder->removeGoal(obj);
	}

	if (ai->isIdle() && ai->isDoingGroundMovement() && updateGoal)
	{
		Coord3D goalPos = { obj->m_position.x, obj->m_position.y,
			obj->m_position.z };
		if (goalPos.x != BfmeZeroRange || goalPos.y != BfmeZeroRange ||
			goalPos.z != BfmeZeroRange)
		{
			Pathfinder *pathfinder = TheAI->m_pathfinder;
#line 1995 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp"
			pathfinder->updateGoal(obj, &goalPos,
				((GetLayer)j_0003a391)(obj), __FILE__, __LINE__);
		}
	}

	ai->setLocomotorGoalNone();
	reinterpret_cast<BfmeAIUpdateVictimThunk *>(ai)->clearCurrentVictim(0);
}

// ?rva002BDBF0@GiantBirdFollowPathState@@QAE_NXZ
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /MD
//
// GiantBirdFollowPathState::tryAdvance, retail RVA 0x002BDBF0 (312 bytes).
// The owning state's constructor at 0x002BDB30 passes the literal
// "GiantBirdFollowPathState" and installs vtable 0x010C7778; its onEnter
// calls this helper through the retail ILT at 0x00024884.  The path member
// is the independently matched Rva0016F770Path::getPoint body at 0x0016F770
// (retail ILT 0x0001840D), and the goal sink is the matched 0x0000795A
// StateMachine ABI slice.

typedef float Real;
typedef int Int;

struct Rva0016F770Coord3D
{
	Real x;
	Real y;
	Real z;
};

typedef Rva0016F770Coord3D Coord3D;

// Matched at retail 0x0016F770; the path data is the AI member at +0x30.
class Rva0016F770Path
{
public:
	Rva0016F770Coord3D *getPoint(Int index);
};

class Object;

// The sink is the same four-argument thiscall ABI used by the proven
// GiantBird goal-routing body.  Its actual retail body is 0x0000795A.
class Rva002BC260GoalOwner
{
public:
	void run(void *position, void *goalData, void *unused, void *source);
};

#define g_Rva012F02D4 (*(Int *)0x012F02D4)

class TerrainLogic
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const = 0;
};

extern TerrainLogic *TheTerrainLogic;

// BFME's AIUpdateInterface fields used by the Giant Bird state.  These
// offsets are also consumed by the ctor-proven onEnter/onExit siblings.
class GiantBirdAIUpdate
{
public:
	unsigned char m_beforePath[0x30];
	Rva0016F770Path *m_path;
	unsigned char m_beforeLocomotor[0x198];
	void *m_locomotor;
	unsigned char m_beforeFlags[0x220];
	unsigned int m_locomotorFlags3f0;
	unsigned char m_beforeGoalHeight[0x84];
	Real m_goalHeight478;
	unsigned char m_beforePathReset[0x0c];
	unsigned char m_pathReset488;
	Rva0016F770Path *getPath() { return m_path; }
};

class Object
{
public:
	unsigned char m_beforeAI[0x204];
	GiantBirdAIUpdate *m_aiUpdate;
};

class StateMachine
{
public:
	unsigned char m_beforeOwner[0x10];
	Object *m_owner;
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class AIFollowPathState
{
public:
	virtual StateReturnType onEnter();
	Object *getMachineOwner() { return m_machine->m_owner; }

	protected:
	Int m_id;
	Int m_successStateID;
	Int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
	};

class GiantBirdFollowPathState : public AIFollowPathState
{
	public:
	bool tryAdvance();

	private:
	unsigned char m_gap20[0x3c];
	Int m_counter;
};

bool GiantBirdFollowPathState::tryAdvance()
{
	Object *owner = getMachineOwner();
	if (owner == 0)
		return false;
	GiantBirdAIUpdate *ai = owner->m_aiUpdate;
	if (ai == 0)
		return false;
	if (ai->m_locomotor == 0)
		return false;

	Int index = m_counter++;
	Coord3D *current = ai->getPath()->getPoint(index);
	if (current == 0)
	{
		if (ai->m_pathReset488 == 0)
			return false;
		m_counter = 1;
		current = ai->getPath()->getPoint(0);
		if (current == 0)
			return false;
	}

	Coord3D goal;
	Coord3D nextGoal;
	Coord3D *nextGoalPointer;
	Coord3D *next = ai->getPath()->getPoint(m_counter);
	if (next != 0)
	{
		ai->m_locomotorFlags3f0 |= 0x80;
		nextGoal.x = next->x;
		nextGoal.y = next->y;
		nextGoal.z = next->z;
		nextGoalPointer = &nextGoal;
		Real height = ai->m_goalHeight478;
		nextGoal.z = TheTerrainLogic->getGroundHeight(
			nextGoal.x, nextGoal.y, 0) + height;
	}
	else
	{
		ai->m_locomotorFlags3f0 &= 0xffffff7f;
		nextGoalPointer = next;
	}
	goal.x = current->x;
	goal.y = current->y;
	goal.z = current->z;
	Real height = ai->m_goalHeight478;
	goal.z = TheTerrainLogic->getGroundHeight(goal.x, goal.y, 0) + height;
	((Rva002BC260GoalOwner *)ai)->run(&goal,
		&g_Rva012F02D4, nextGoalPointer, (void *)(nextGoalPointer == 0));
	return true;
}

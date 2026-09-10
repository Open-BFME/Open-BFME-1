// cl: /DNDEBUG /MD
//
// GiantBirdFollowPathState::onEnter, retail RVA 0x002BDB80, 78 bytes.
// The constructor at 0x002BDB30 passes the literal state name and installs
// vtable 0x010C7778; the matched onExit at 0x002BDF10 and update at
// 0x002BDDC0 establish the same state layout.  The call below is the state
// helper's retail ILT at 0x00024884, which jumps to 0x002BDBF0.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object
{
public:
	unsigned char m_beforeAI[0x204];
	class GiantBirdAIUpdate *m_aiUpdate;
	unsigned char m_beforeFlags[0x344 - 0x208];
	unsigned char m_flags344;
};

class StateMachine
{
public:
	unsigned char m_beforeOwner[0x10];
	Object *m_owner;
};

typedef float Real;

struct Rva0016F770Coord3D
{
	Real x;
	Real y;
	Real z;
};

typedef Rva0016F770Coord3D Coord3D;

class Rva0016F770Path
{
public:
	Rva0016F770Coord3D *getPoint(int index);
};

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

class Rva002BC260GoalOwner
{
public:
	// Goal setup2BC260 forwards this slot to149470; +40 there reads
	// only byte[esp+88], the sixth argument. Upper bits are not a pointer.
	void run(void *position, void *goalData, void *unused, unsigned char source);
};

#define g_Rva012F02D4 (*(int *)0x012F02D4)

class GiantBirdAIUpdate
{
public:
	unsigned char m_beforePath[0x30];
	class Rva0016F770Path *m_path;
	unsigned char m_beforeLocomotor[0x198];
	void *m_locomotor;
	unsigned char m_beforeFlags[0x220];
	unsigned int m_flags3f0;
	unsigned char m_beforeByte[0x30];
	bool m_byte424;
	unsigned char m_beforeGoalHeight[0x53];
	float m_goalHeight478;
	unsigned char m_beforePathReset[0x0c];
	unsigned char m_pathReset488;

	class Rva0016F770Path *getPath()
	{
		return m_path;
	}

	__forceinline bool isContinueEnabled() const
	{
		return m_byte424 != 0;
	}
};

class GiantBirdFollowPathState
{
public:
	virtual StateReturnType onEnter();
	__declspec(noinline) bool rva002BDBF0();

private:
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
	unsigned char m_gap20[0x5c - 0x20];
	int m_counter;
};

// ?rva002BDBF0@GiantBirdFollowPathState@@QAE_NXZ
__declspec(noinline) bool GiantBirdFollowPathState::rva002BDBF0()
{
	Object *owner = m_machine->m_owner;
	if (owner == 0)
		return false;

	GiantBirdAIUpdate *ai = owner->m_aiUpdate;
	if (ai == 0)
		return false;
	if (ai->m_locomotor == 0)
		return false;

	int index = m_counter++;
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

	struct Goals
	{
		Coord3D goal;
		Coord3D next;
	} goals;
	Coord3D *nextGoalPointer;
	int nextIndex = m_counter;
	Coord3D *next = ai->getPath()->getPoint(nextIndex);
	nextGoalPointer = next;
	if (nextGoalPointer != 0)
	{
		ai->m_flags3f0 |= 0x80;
		goals.next = *nextGoalPointer;
		nextGoalPointer = &goals.next;
		Real height = ai->m_goalHeight478;
		goals.next.z = TheTerrainLogic->getGroundHeight(
			goals.next.x, goals.next.y, 0) + height;
	}
	else
	{
		ai->m_flags3f0 &= 0xffffff7f;
	}

	goals.goal.x = current->x;
	goals.goal.y = current->y;
	goals.goal.z = current->z;
	Real height = ai->m_goalHeight478;
	goals.goal.z = TheTerrainLogic->getGroundHeight(
		goals.goal.x, goals.goal.y, 0) + height;
	((Rva002BC260GoalOwner *)ai)->run(&goals.goal,
		&g_Rva012F02D4, nextGoalPointer, nextGoalPointer == 0);
	return true;
}

StateReturnType GiantBirdFollowPathState::onEnter()
{
	m_counter = 0;
	Object *object = m_machine->m_owner;
	GiantBirdAIUpdate *ai = object->m_aiUpdate;
	if (ai == 0)
		goto failure;
	if ((object->m_flags344 & 1) != 0)
		goto failure;
	if (!rva002BDBF0())
		return STATE_SUCCESS;
	// Keep the shared failure block before the final flag-setting tail; this
	// is the retail branch layout emitted by MSVC 7.1 for this state.
	goto checkByte;
failure:
	return STATE_FAILURE;

checkByte:
	if (ai->isContinueEnabled() == 0)
		goto failure;
	ai->m_flags3f0 |= 0x80;
	return STATE_CONTINUE;
}

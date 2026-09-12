// cl: /DNDEBUG /MD
//
// GiantBirdFollowWaypointPathState::update, retail RVA 0x002BF250.
// The state vtable at 0x010C79E0 stores thunk 0x000178D7 in slot 6, and that
// thunk jumps to this body.  The state routes its current goal, snaps the
// owner to the goal when the flight distance or pending waypoint requires it,
// then lets the shared waypoint helper decide whether movement continues.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

extern float BfmeZeroRange;

struct Rva0016F770Coord3D
{
	float x;
	float y;
	float z;
};

class Rva0016F770Path
{
public:
	Rva0016F770Coord3D *getPoint(int index);
};

typedef Rva0016F770Coord3D GiantBirdWaypointCoord3D;

class Rva002BCB60Owner
{
public:
	void route(void *mode, Coord3D *position, int source);

	char m_gap00[0x46c];
	unsigned char m_pending46c;
	char m_gap46d[3];
	float m_height470;
	char m_gap474[4];
	int m_goalMode478;
	Coord3D m_goalPosition47c;
};

class GiantBirdAIUpdate
{
public:
	unsigned char m_beforePath[0x30];
	Rva0016F770Path *m_path;
	unsigned char m_beforeLocomotor[0x198];
	void *m_locomotor;
	unsigned char m_beforeFlags[0x220];
	unsigned int m_flags3f0;
	unsigned char m_beforeGoalHeight[0x84];
	float m_goalHeight478;
	unsigned char m_beforePathReset[0x0c];
	unsigned char m_pathReset488;

	Rva0016F770Path *getPath()
	{
		return m_path;
	}
};

class Rva002BC260GoalOwner
{
public:
	void run(void *position, void *goalData, void *unused, unsigned char source);
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
	virtual float getGroundHeight(float x, float y, Rva0016F770Coord3D *normal) const = 0;
};

extern TerrainLogic *TheTerrainLogic;

#define g_Rva012F02D4 (*(int *)0x012F02D4)

class Thing
{
public:
	void setPosition(const Coord3D *position);
};

class Object
{
public:
	char m_gap00[0x38];
	Coord3D m_position;
	char m_gap44[0x1c0];
	Rva002BCB60Owner *m_ai;
	char m_gap208[0x13c];
	unsigned char m_privateStatus;
};

class StateMachine
{
public:
	char m_gap00[0x10];
	Object *m_owner;
};

class GiantBirdFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter() = 0;
	virtual void onExit(int status) = 0;
	virtual StateReturnType update();

	char m_gap04[0x18];
	StateMachine *m_machine;
	char m_gap20[4];
	int m_counter;

	__declspec(noinline) bool updateWaypointGoal();
};

bool GiantBirdFollowWaypointPathState::updateWaypointGoal()
{
	Object *owner = m_machine->m_owner;
	if (owner == 0)
		return false;

	GiantBirdAIUpdate *ai = (GiantBirdAIUpdate *)owner->m_ai;
	if (ai == 0)
		return false;
	if (ai->m_locomotor == 0)
		return false;

	int index = m_counter++;
	GiantBirdWaypointCoord3D *current = ai->getPath()->getPoint(index);
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
		GiantBirdWaypointCoord3D goal;
		GiantBirdWaypointCoord3D next;
	} goals;
	GiantBirdWaypointCoord3D *nextGoalPointer;
	int nextIndex = m_counter;
	GiantBirdWaypointCoord3D *next = ai->getPath()->getPoint(nextIndex);
	nextGoalPointer = next;
	if (nextGoalPointer != 0)
	{
		ai->m_flags3f0 |= 0x80;
		goals.next = *nextGoalPointer;
		nextGoalPointer = &goals.next;
		float height = ai->m_goalHeight478;
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
	float height = ai->m_goalHeight478;
	goals.goal.z = TheTerrainLogic->getGroundHeight(
		goals.goal.x, goals.goal.y, 0) + height;
	((Rva002BC260GoalOwner *)ai)->run(&goals.goal,
		&g_Rva012F02D4, nextGoalPointer, nextGoalPointer == 0);
	return true;
}

StateReturnType GiantBirdFollowWaypointPathState::update()
{
	Object *object = m_machine->m_owner;
	if ((object->m_privateStatus & 1) != 0)
		return STATE_FAILURE;

	Rva002BCB60Owner *ai = object->m_ai;
	if (ai == 0)
		return STATE_FAILURE;

	ai->route((void *)ai->m_goalMode478, &ai->m_goalPosition47c, 0);
	float height = ai->m_height470;
	Coord3D goal = ai->m_goalPosition47c;
	float dx = object->m_position.x - goal.x;
	float dy = object->m_position.y - goal.y;
	float dz = object->m_position.z - goal.z;
	unsigned char farFromGoal = (unsigned char)(dx * dx + dy * dy + dz * dz < height * height);
	int pending = ai->m_pending46c;

	if (pending != BfmeZeroRange || farFromGoal)
	{
		((Thing *)object)->setPosition(&goal);
		if (!updateWaypointGoal())
			return STATE_SUCCESS;
		if (*(unsigned char *)((char *)ai + 0x424) == 0)
			return STATE_FAILURE;
	}

	return STATE_CONTINUE;
}

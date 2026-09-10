// cl: /DNDEBUG /MD
//
// GiantBirdFollowPathState::update, retail RVA 0x002BDDC0, 261 bytes.
// The constructor at 0x002BDB30 installs vtable 0x010C7778.  Its slot 5 is
// the independently matched GiantBirdFollowPathState::onExit at 0x002BDF10;
// slot 6 is ILT 0x0001A50A, which jumps to this complete body.  The helper
// called after snapping the owner is an address-qualified helper of the same state at
// 0x002BDBF0 through ILT 0x00024884.

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

extern const float BfmeZeroRange;

class Rva002BCB60Owner
{
public:
	void route(void *mode, Coord3D *position, int source);

	char m_gap00[0x424];
	unsigned char m_continue424;
	char m_gap425[0x47];
	unsigned char m_pending46c;
	char m_gap46d[3];
	float m_goalRange470;
	char m_gap474[4];
	void *m_goalMode478;
	Coord3D m_goalPosition47c;
};

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
	unsigned char m_flags344;
};

class StateMachine
{
public:
	char m_gap00[0x10];
	Object *m_owner;
};

class GiantBirdFollowPathState
{
public:
	virtual StateReturnType update();

	char m_gap04[0x18];
	StateMachine *m_machine;

	bool rva002BDBF0();
};

typedef char GiantBirdCoordSize[(sizeof(Coord3D) == 12) ? 1 : -1];

StateReturnType GiantBirdFollowPathState::update()
{
	Object *object = m_machine->m_owner;
	if ((object->m_flags344 & 1) != 0)
		return STATE_FAILURE;

	Rva002BCB60Owner *ai = object->m_ai;
	if (ai == 0)
		return STATE_FAILURE;

	ai->route(ai->m_goalMode478, &ai->m_goalPosition47c, 0);
	float goalRange = ai->m_goalRange470;
	Coord3D goal = ai->m_goalPosition47c;
	float dx = object->m_position.x - goal.x;
	float dy = object->m_position.y - goal.y;
	float dz = object->m_position.z - goal.z;
	unsigned char withinGoalRange = (unsigned char)(dx * dx + dy * dy + dz * dz < goalRange * goalRange);
	int pending = ai->m_pending46c;

	if (pending != BfmeZeroRange || withinGoalRange)
	{
		((Thing *)object)->setPosition(&goal);
		if (!rva002BDBF0())
			return STATE_SUCCESS;
		if (ai->m_continue424 == 0)
			return STATE_FAILURE;
	}

	return STATE_CONTINUE;
}

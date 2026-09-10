// ?update@AIGiantBirdFollowThruState@@UAE?AW4StateReturnType@@XZ
// partial score=0.97 date=2026-09-10
// cl: /DNDEBUG /MD
//
// AIGiantBirdFollowThruState::update, retail RVA 0x002BECD0.
// The constructor at 0x002BEC00 installs vtable 0x010C7968.  Its slot 6
// contains thunk 0x00042F41, which jumps to this 347-byte body; the matched
// onExit at 0x002BEE90 occupies slot 5.  The body is the follow-through
// state update and uses the shared Giant Bird goal-routing layout.

typedef unsigned int UnsignedInt;

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

class BfmeVec3EJ
{
	float x;
	float y;
	float z;
};

class Rva002BCB60Owner
{
public:
	void route(void *mode, Coord3D *position, int source);

	char m_beforeTargetID3f8[0x3f8];
	int m_targetID3f8;
	char m_beforeContinue424[0x424 - 0x3fc];
	unsigned char m_continue424;
	char m_beforePending46c[0x46c - 0x425];
	unsigned char m_pending46c;
	char m_beforeGoalRange470[3];
	float m_goalRange470;
	char m_beforeGoalMode478[4];
	void *m_goalMode478;
	Coord3D m_goalPosition47c;
	char m_beforeTargetID48c[4];
	int m_targetID48c;
};

class Gen_000E5A50
{
public:
	float bfmeDistanceSquared(const BfmeVec3EJ *point) const;
};

class Object
{
public:
	virtual void unused00() = 0;

	void notifyModelConditionChanged();

	char m_beforePosition38[0x34];
	Coord3D m_position38;
	char m_beforeFlags114[0xd0];
	UnsignedInt m_flags114;
	UnsignedInt m_flags118;
	UnsignedInt m_flags11c;
	UnsignedInt m_flags120;
	char m_beforeAI204[0xe0];
	Rva002BCB60Owner *m_ai204;
	char m_beforeFlags344[0x13c];
	unsigned char m_flags344;
};

class Thing
{
public:
	void setPosition(const Coord3D *position);
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class StateMachine
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void updateStateMachine() = 0;
	virtual void start() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void setState(int id) = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2c() = 0;
	virtual void unused30() = 0;
	virtual void unused34() = 0;
	virtual void setGoalObject(const Object *object) = 0;

	char m_beforeOwner10[0x0c];
	Object *m_owner10;
};

class AIGiantBirdFollowThruState
{
public:
	virtual StateReturnType update();

	char m_beforeMachine1c[0x18];
	StateMachine *m_machine1c;
	char m_beforeCounter28[8];
	int m_counter28;
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define BfmeZeroRange (*(const float *)0x01075350)

StateReturnType AIGiantBirdFollowThruState::update()
{
	Object *object = m_machine1c->m_owner10;
	if ((object->m_flags344 & 1) != 0)
		return STATE_FAILURE;

	if ((object->m_flags120 & 0x20000) != 0)
	{
		object->m_flags120 &= 0xfffdffff;
		object->notifyModelConditionChanged();
	}

	++m_counter28;
	if (m_counter28 > 40)
		return STATE_FAILURE;

	Rva002BCB60Owner *ai = object->m_ai204;
	if (ai == 0)
		return STATE_FAILURE;

	ai->route((void *)0x40a00000, 0, 1);
	if (ai->m_continue424 == 0)
		return STATE_FAILURE;

	float goalRange = ai->m_goalRange470;
	Coord3D goal;
	goal.x = ai->m_goalPosition47c.x;
	goal.y = ai->m_goalPosition47c.y;
	goal.z = ai->m_goalPosition47c.z;
	unsigned char withinGoalRange = (unsigned char)(
		((Gen_000E5A50 *)object)->bfmeDistanceSquared((const BfmeVec3EJ *)&goal) <
		goalRange * goalRange);
	unsigned char pending = ai->m_pending46c;

	if (pending == BfmeZeroRange && withinGoalRange == 0)
		return STATE_CONTINUE;

	((Thing *)object)->setPosition(&goal);
	Object *target;
	const int &targetID = ai->m_targetID3f8;
	GameLogic *gameLogic = TheBfmeGameLogic;
	target = gameLogic->findObjectByID(targetID);
	if (target != 0 && (target->m_flags344 & 1) == 0)
		return STATE_FAILURE;

	Object *otherTarget = gameLogic->findObjectByID(ai->m_targetID48c);
	StateMachine *machine = m_machine1c;
	machine->setGoalObject(0);
	if (otherTarget == 0 || (otherTarget->m_flags344 & 1) != 0)
		return STATE_SUCCESS;

	return STATE_FAILURE;
}

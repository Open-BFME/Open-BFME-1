// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// AIGiantBirdFollowThruState::update, retail RVA 0x002BECD0, 347 bytes.
// The constructor at 0x002BEC00 installs vtable 0x010C7968.  Its slot 6
// contains thunk 0x00042F41, which jumps to this 347-byte body; the matched
// onExit at 0x002BEE90 occupies slot 5.  The body is the follow-through
// state update and uses the shared Giant Bird goal-routing layout.
//
// GameLogic::findObjectByID is an inline member in the Zero Hour header
// (GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h), and BFME kept
// the hash_map body that header still carries commented out (see the matched
// Code/GameEngine/Source/GameLogic/System/GameLogicFindObjectByID.cpp).  The
// compiler does not inline it here but sees that it writes no memory, so
// retail keeps TheGameLogic in EDI across the first lookup and reuses it for
// the second, loading the victim ID before the global.  That only reproduces
// when the inline body is visible in this TU.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

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
	unsigned char m_privateStatus;
};

class Thing
{
public:
	void setPosition(const Coord3D *position);
};

typedef int ObjectID;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

private:
	char m_slice_pad[0xB0];		// retail this+0x00 .. +0xAF, untouched
	ObjectPtrHash m_objHash;	// bucket vector _M_start lands at this+0xB4
};

inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;

	ObjectPtrHash::iterator it = m_objHash.find(id);
	if (it == m_objHash.end())
		return 0;

	return (*it).second;
}

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
	Object *m_owner;
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

extern GameLogic *TheGameLogic;
extern const float BfmeZeroRange;

StateReturnType AIGiantBirdFollowThruState::update()
{
	Object *object = m_machine1c->m_owner;
	if ((object->m_privateStatus & 1) != 0)
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
	Object *target = TheGameLogic->findObjectByID(ai->m_targetID3f8);
	if (target != 0 && (target->m_privateStatus & 1) == 0)
		return STATE_FAILURE;

	Object *otherTarget = TheGameLogic->findObjectByID(ai->m_targetID48c);
	StateMachine *machine = m_machine1c;
	machine->setGoalObject(0);
	if (otherTarget == 0 || (otherTarget->m_privateStatus & 1) != 0)
		return STATE_SUCCESS;

	return STATE_FAILURE;
}

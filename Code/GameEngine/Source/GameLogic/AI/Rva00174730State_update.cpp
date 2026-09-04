// cl: /DNDEBUG /MD
//
// Retail 0x00174730: the path-ready move-state update.  The state-machine
// helper supplies the goal object before the path-ready branch is considered;
// a pending path leaves the state in STATE_CONTINUE, while an already-cleared
// check delegates to the internal move update.

typedef unsigned char Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

struct Rva00174730PathNode
{
	unsigned char m_pad00[0x0c];
	Coord3D m_position;
};

struct Rva00174730Path
{
	unsigned char m_pad00[8];
	Rva00174730PathNode *m_lastNode;
};

struct Rva00174730AIUpdate
{
	unsigned char m_pad00[0x140];
	Rva00174730Path *m_path;
	unsigned char m_pad144[0x31e - 0x144];
	Bool m_waitingForPath;
};

struct Rva00174730Object
{
	unsigned char m_pad00[0x204];
	Rva00174730AIUpdate *m_ai;
};

class Object
{
};

struct Rva00174730StateMachine
{
	unsigned char m_pad00[0x10];
	Rva00174730Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType update();

protected:
	unsigned char m_pad04[0x18];
	Rva00174730StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	unsigned char m_pad30[0x1c];
	unsigned char m_adjustDestinations;
	unsigned char m_pad4d[7];
	unsigned char m_checkForPath;
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a();
extern void j_0000e570();

typedef void (__cdecl *Rva00174730CritterDesyncLog)(void *, const char *);
typedef Object *(__fastcall *Rva00174730GetObject)(Rva00174730StateMachine *);

class Rva00174730State : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

static void rva00174730_log(const char *message)
{
	if (g_012F0239 && g_012ED4FC)
		((Rva00174730CritterDesyncLog)j_0003a17a)(g_012ED4FC, message);
}

StateReturnType Rva00174730State::update()
{
	Rva00174730StateMachine *machine = m_machine;
	Rva00174730Object *owner = machine->m_owner;
	Object *goal = ((Rva00174730GetObject)j_0000e570)(machine);
	Rva00174730AIUpdate *ai = m_machine->m_owner->m_ai;
	if (!goal || !ai)
		return STATE_FAILURE;

	if (m_checkForPath)
	{
		Rva00174730AIUpdate *ownerAI = owner->m_ai;
		Rva00174730Path *path = ownerAI->m_path;
		if (!path || ownerAI->m_waitingForPath)
			return STATE_CONTINUE;

		m_goalPosition = *(Coord3D *)((char *)path->m_lastNode + 0x0c);
		rva00174730_log("CritterDesync: setAdjustDestination(FALSE) 15");
		m_adjustDestinations = 0;
		m_checkForPath = 0;
		return STATE_CONTINUE;
	}
	return AIInternalMoveToState::update();
}

// cl: /DNDEBUG /MD
// Retail 0x00173C70 and 0x00173E50: two path-ready move-state updates.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

struct Rva00173C70PathNode
{
	char m_unknown[0x0c];
	Coord3D m_position;
};

struct Rva00173C70Path
{
	char m_unknown[8];
	Rva00173C70PathNode *m_lastNode;
};

struct Rva00173C70AIUpdate
{
	char m_unknown[0x140];
	Rva00173C70Path *m_path;
	char m_gap144[0x31e - 0x144];
	unsigned char m_waitingForPath;
};

struct Rva00173C70Object
{
	char m_unknown[0x204];
	Rva00173C70AIUpdate *m_ai;

	Rva00173C70AIUpdate *getAI()
	{
		return m_ai;
	}
};

struct Rva00173C70StateMachine
{
	char m_unknown[0x10];
	Rva00173C70Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);
typedef void (__cdecl *Rva00173C70CritterDesyncLog)(void *, const char *);

class Rva00173C70State : public AIInternalMoveToState
{
	char m_unknown[0x18];
	Rva00173C70StateMachine *m_machine;
	char m_gap20[4];
	Coord3D m_goalPosition;
	char m_gap30[0x1c];
	unsigned char m_adjustDestinations;
	char m_gap4d[7];
	unsigned char m_checkForPath;

public:
	virtual StateReturnType update();
};

class Rva00173E50State : public AIInternalMoveToState
{
	char m_unknown[0x18];
	Rva00173C70StateMachine *m_machine;
	char m_gap20[4];
	Coord3D m_goalPosition;
	char m_gap30[0x1c];
	unsigned char m_adjustDestinations;
	char m_gap4d[7];
	unsigned char m_checkForPath;

public:
	virtual StateReturnType update();
};

class Rva00173990State : public AIInternalMoveToState
{
	char m_unknown[0x18];
	Rva00173C70StateMachine *m_machine;
	char m_gap20[4];
	Coord3D m_goalPosition;
	char m_gap30[0x1c];
	unsigned char m_adjustDestinations;

public:
	virtual StateReturnType onEnter();
};

static void rva00173c70_log(const char *message)
{
	if (g_012F0239 && g_012ED4FC)
		((Rva00173C70CritterDesyncLog)j_0003a17a)(g_012ED4FC, message);
}

StateReturnType Rva00173C70State::update()
{
	if (m_checkForPath)
	{
		Rva00173C70Object *obj = m_machine->m_owner;
		Rva00173C70AIUpdate *ai = obj->m_ai;
		Rva00173C70Path *path = ai->m_path;
		if (path && !ai->m_waitingForPath)
		{
			m_goalPosition = *(Coord3D *)((char *)path->m_lastNode + 0x0c);
			rva00173c70_log("CritterDesync: setAdjustDestination(FALSE) 10");
			m_adjustDestinations = 0;
			m_checkForPath = 0;
		}
	}
	return AIInternalMoveToState::update();
}

StateReturnType Rva00173E50State::update()
{
	if (m_checkForPath)
	{
		Rva00173C70Object *obj = m_machine->m_owner;
		Rva00173C70AIUpdate *ai = obj->m_ai;
		Rva00173C70Path *path = ai->m_path;
		if (path && !ai->m_waitingForPath)
		{
			m_goalPosition = *(Coord3D *)((char *)path->m_lastNode + 0x0c);
			rva00173c70_log("CritterDesync: setAdjustDestination(FALSE) 12");
			m_adjustDestinations = 0;
			m_checkForPath = 0;
		}
	}
	return AIInternalMoveToState::update();
}

StateReturnType Rva00173990State::onEnter()
{
	if (g_012F0239 && g_012ED4FC)
		((Rva00173C70CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 6");

	Rva00173C70StateMachine *machine = m_machine;
	m_adjustDestinations = 1;
	Rva00173C70Object *obj = machine->m_owner;
	Rva00173C70Path *path = obj->getAI()->m_path;
	if (path == 0)
		return STATE_FAILURE;

	m_goalPosition = path->m_lastNode->m_position;
	return AIInternalMoveToState::onEnter();
}

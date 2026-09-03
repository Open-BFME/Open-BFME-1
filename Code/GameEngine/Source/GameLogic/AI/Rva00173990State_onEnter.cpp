// cl: /DNDEBUG /MD
// Retail 0x00173990: move-state entry using the current path endpoint.

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

struct Rva00173990PathNode
{
	char m_unknown[0x0c];
	Coord3D m_position;
};

struct Rva00173990Path
{
	char m_unknown[8];
	Rva00173990PathNode *m_lastNode;
};

struct Rva00173990AIUpdate
{
	char m_unknown[0x140];
	Rva00173990Path *m_path;

	Rva00173990Path *getPath()
	{
		return m_path;
	}
};

struct Rva00173990Object
{
	char m_unknown[0x204];
	Rva00173990AIUpdate *m_ai;

	Rva00173990AIUpdate *getAI()
	{
		return m_ai;
	}
};

struct Rva00173990StateMachine
{
	char m_unknown[0x10];
	Rva00173990Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);
typedef void (__cdecl *Rva00173990CritterDesyncLog)(void *, const char *);

class Rva00173990State : public AIInternalMoveToState
{
	char m_unknown[0x18];
	Rva00173990StateMachine *m_machine;
	char m_gap20[4];
	Coord3D m_goalPosition;
	char m_gap30[0x1c];
	unsigned char m_adjustDestinations;

public:
	Rva00173990Object *getMachineOwner()
	{
		return m_machine->m_owner;
	}

	void setAdjustsDestination(bool adjust)
	{
		m_adjustDestinations = adjust ? 1 : 0;
	}

	virtual StateReturnType onEnter();
};

StateReturnType Rva00173990State::onEnter()
{
	if (g_012F0239 && g_012ED4FC)
		((Rva00173990CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 6");

	setAdjustsDestination(true);
	Rva00173990AIUpdate *ai = getMachineOwner()->getAI();
	if (ai->getPath() == 0)
		return STATE_FAILURE;

	m_goalPosition = ai->getPath()->m_lastNode->m_position;
	return AIInternalMoveToState::onEnter();
}

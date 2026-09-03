// cl: /DNDEBUG /MD
// Retail 0x00173900: the AIMoveToStateSA path/goal update.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class GameLogic
{
	unsigned char m_unreconstructed_000[0x3c];

public:
	unsigned int m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class Object
{
	unsigned char m_unreconstructed_000[0x38];

public:
	Coord3D m_position;

	unsigned char m_unreconstructed_044[0x114 - 0x44];

public:
	unsigned int m_statusFlags;
	void notifyModelConditionChanged();
};

struct Rva00173900StateMachine
{
	unsigned char m_unreconstructed_000[0x10];
	Object *m_owner;
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

extern void j_0000e570();
typedef Object *(__fastcall *Rva00173900GetGoalObject)(Rva00173900StateMachine *machine);

class Rva00173620State : public AIInternalMoveToState
{
	unsigned char m_unreconstructed_004[0x18];
	Rva00173900StateMachine *m_machine;
	unsigned char m_unreconstructed_020[4];
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_030[0x20];
	unsigned int m_okToRepathTimes;
	unsigned char m_checkForPath;

public:
	virtual StateReturnType update();
};

StateReturnType Rva00173620State::update()
{
	if (m_checkForPath)
	{
		if (TheBfmeGameLogic->m_frame > m_okToRepathTimes)
			return STATE_FAILURE;

		Object *owner = m_machine->m_owner;
		if (owner->m_statusFlags & 0x10000000)
		{
			owner->m_statusFlags &= 0xEFFFFFFF;
			owner->notifyModelConditionChanged();
		}
		return STATE_CONTINUE;
	}

	Object *goalObject = ((Rva00173900GetGoalObject)j_0000e570)(m_machine);
	if (goalObject)
		m_goalPosition = goalObject->m_position;
	return AIInternalMoveToState::update();
}

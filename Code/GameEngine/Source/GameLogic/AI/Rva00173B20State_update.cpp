// cl: /DNDEBUG /MD
// Retail 0x00173B20: the path-ready half of the move-and-tighten update.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct AIUpdateInterface
{
	char m_unknown[0x140];
	void *m_curLocomotor;
	char m_gap144[0x31e - 0x144];
	unsigned char m_waitingForPath;
};

struct Rva00173B20Object
{
	char m_unknown[0x204];
	AIUpdateInterface *m_ai;
};

struct Rva00173B20StateMachine
{
	char m_unknown[0x10];
	Rva00173B20Object *m_owner;
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);
typedef void (__cdecl *Rva00173B20CritterDesyncLog)(void *, const char *);

class Rva00173B20State : public AIInternalMoveToState
{
	char m_unknown[0x18];
	Rva00173B20StateMachine *m_machine;
	char m_gap20[0x2c];
	unsigned char m_adjustDestinations;
	char m_gap4d[7];
	unsigned char m_checkForPath;

public:
	virtual StateReturnType update();
};

StateReturnType Rva00173B20State::update()
{
	if (m_checkForPath)
	{
		Rva00173B20Object *obj = m_machine->m_owner;
		AIUpdateInterface *ai = obj->m_ai;
		if (ai->m_curLocomotor && !ai->m_waitingForPath)
		{
			if (g_012F0239 && g_012ED4FC)
				((Rva00173B20CritterDesyncLog)j_0003a17a)(g_012ED4FC,
					"CritterDesync: setAdjustDestination(TRUE) 8");
			m_adjustDestinations = 1;
			m_checkForPath = 0;
		}
	}
	return AIInternalMoveToState::update();
}

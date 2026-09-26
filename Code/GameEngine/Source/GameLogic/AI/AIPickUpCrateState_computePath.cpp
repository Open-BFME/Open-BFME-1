// cl: /DNDEBUG /MD
// BFME AIPickUpCrateState::computePath at retail 0x0016B380.

typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class AIUpdateInterface
{
public:
	void requestPath(Coord3D *goal, Bool adjustsDestination);

	char m_pad00[0x31e];
	Bool m_waitingForPath;
	char m_pad31f[7];
	Bool m_isBlockedAndStuck;
};

struct Object
{
	char m_pad00[0x204];
	AIUpdateInterface *m_ai;
};

struct StateMachine
{
	char m_pad00[0x10];
	Object *m_owner;
};

class AIPickUpCrateState
{
protected:
	virtual Bool computePath();

	char m_pad00[0x18];
	StateMachine *m_machine;
	char m_pad20[4];
	Coord3D m_goalPosition;
	char m_pad30[0x1d];
	Bool m_waitingForPath;
	Bool m_tryOneMoreRepath;
	char m_pad4f[1];
	int m_delayCounter;
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

typedef void (__cdecl *CritterDesyncLog)(void *, const char *);

Bool AIPickUpCrateState::computePath()
{
	if (g_012F0239 && g_012ED4FC)
	{
		((CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: ComputePath4");
	}

	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	if (ai->m_isBlockedAndStuck)
	{
		int delay = m_delayCounter;
		if (delay > 0)
		{
			m_delayCounter = --delay;
			ai->requestPath(&m_goalPosition, true);
			m_waitingForPath = ai->m_waitingForPath;
			return true;
		}
		return false;
	}
	return true;
}

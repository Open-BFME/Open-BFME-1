// cl: /DNDEBUG /MD
// Retail 0x001737C0: AIMoveToStateSA entry.  The constructor at 0x00173620
// installs vftable 0x01098FA8 and uses the runtime name AIMoveToStateSA;
// Rva00173900State is the already matched update for that same vftable.

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

class AIUpdateInterface;

// Object's id, position, and AI interface are the fields consumed by this
// entry path.  The offsets are also used by the matched AIMoveToState body.
class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0x30];
	int m_id;
	char m_pad78[0x18c];
	AIUpdateInterface *m_ai;
};

template <int N>
class Rva001737C0VirtualSlots : public Rva001737C0VirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]);
};

template <>
class Rva001737C0VirtualSlots<0>
{
};

class AIUpdateInterface : public Rva001737C0VirtualSlots<122>
{
public:
	int getIgnoredObstacleID();
	// The Object+0x204 receiver is the real AIUpdateInterface subobject.  The
	// body reached through retail ILT 0x00044774 reads this interface's
	// UpdateModule object at +0x08, so keep the helper on this view rather than
	// overlaying a different empty class onto the receiver.
	bool bfmeBlocksFormationRefresh();
	virtual void slot1e8();

	char m_pad04[0x160];
	int m_ignoredObstacleID;
};

class StateMachine
{
public:
	Object *getGoalObject();

	char m_pad00[0x10];
	Object *m_owner;
	char m_pad14[0x10];
	Coord3D m_goalPosition;
};

// The entry body only needs the base virtual call as a qualified call.  This
// is a TU-local view of the already-proven hierarchy, not a public-name guess:
// the 0x00173620 constructor calls the matched AIInternalMoveToState ctor
// thunk at 0x00032182, and this entry calls the matched base onEnter thunk at
// 0x00021E27.  The derived declaration below carries the retail state fields
// and their measured offsets.
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

class Rva00173620State : public AIInternalMoveToState
{
	char m_pad04[0x18];
	StateMachine *m_machine;
	char m_pad20[4];
	Coord3D m_goalPosition;
	char m_pad30[0x1c];
	unsigned char m_adjustDestinations;
	char m_pad4d[3];
	unsigned int m_okToRepathTimes;
	unsigned char m_checkForPath;

public:
	virtual StateReturnType onEnter();
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
// This is the existing 215-byte CRCParameterCheck logger body at 0x00065C80;
// the retail 0x0003A17A ILT reaches it.  Its cdecl varargs ABI is also used by
// the matched AIDock and CRCParameterCheck callers.
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *, const char *, ...);

StateReturnType Rva00173620State::onEnter()
{
	if (g_012F0239 && g_012ED4FC)
		bfmeRetailCritterDesyncLog(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 4");

	m_adjustDestinations = 1;
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	Object *goal = m_machine->getGoalObject();
	if (goal && ai)
	{
		goal = m_machine->getGoalObject();
		int goalID = goal->m_id;
		if (goalID == ai->getIgnoredObstacleID())
		{
			if (g_012F0239 && g_012ED4FC)
				bfmeRetailCritterDesyncLog(g_012ED4FC,
					"CritterDesync: setAdjustDestination(FALSE) 5");
			m_adjustDestinations = 0;
		}
	}

	if (m_machine->getGoalObject())
		m_goalPosition = m_machine->getGoalObject()->m_position;
	else
		m_goalPosition = m_machine->m_goalPosition;
	StateReturnType result = AIInternalMoveToState::onEnter();
	if (m_checkForPath && ai &&
		ai->bfmeBlocksFormationRefresh())
		ai->slot1e8();
	return result;
}

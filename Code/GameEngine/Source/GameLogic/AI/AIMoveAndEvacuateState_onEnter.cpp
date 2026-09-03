// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction for AIMoveAndEvacuateState::onEnter.

enum StateReturnType
{
	STATE_CONTINUE = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}
};

class StateMachine
{
public:
	Object *getGoalObject(void);
	const Coord3D *getGoalPosition(void) const
	{
		return &m_goalPosition;
	}
	void lock(const char *)
	{
		m_locked = 1;
	}

	unsigned char m_unreconstructed_00[0x10];
	Object * volatile m_owner;
	unsigned char m_unreconstructed_14[0x0c];
	int m_goalObjectId;
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_30[0x10];
	volatile unsigned char m_locked;
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

	StateMachine *getMachine(void) const
	{
		return m_machine;
	}
	void setAdjustsDestination(bool value)
	{
		m_adjustDestinations = value;
	}

protected:
	unsigned char m_unreconstructed_04[0x18];
	StateMachine *m_machine;
	unsigned char m_unreconstructed_20[4];
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_30[0x1c];
	unsigned char m_adjustDestinations;
};

class AIMoveAndEvacuateState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	Coord3D m_origin;
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

typedef void (__cdecl *DebugLogFunction)(void *, const char *);

// ?onEnter@AIMoveAndEvacuateState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveAndEvacuateState::onEnter()
{
	{
		Object *owner = getMachine()->m_owner;
		getMachine()->lock("AIMoveAndEvacuateState::onEnter");
		m_origin = *owner->getPosition();
	}

	if (g_012F0239 && g_012ED4FC)
	{
		((DebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 49");
	}

	setAdjustsDestination(true);
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();
	return AIInternalMoveToState::onEnter();
}

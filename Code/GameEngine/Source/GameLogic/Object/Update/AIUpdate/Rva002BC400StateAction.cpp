// cl: /DNDEBUG /MD
//
// Address-derived recovery for the BFME state-action body at 0x002BC400.

typedef int Int;

class BfmeSubCSA
{
public:
	bool bfmeAskCSA();

	unsigned char m_unreconstructed000[0x344];
	unsigned char m_flags344;
};

class Waypoint;

class AIStateMachine
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual void unused010() = 0;
	virtual void beginAction() = 0;
	virtual void unused018() = 0;
	virtual void unused01c() = 0;
	virtual void signalAction(Int code) = 0;
	void setGoalWaypoint(const Waypoint *waypoint);
};

class Rva002BC470StateAction
{
public:
	void finish(void *argument);
};

class Rva002BC400StateAction
{
public:
	void run(void *first, unsigned char second, void *third);

private:
	unsigned char m_unreconstructed000[8];
	BfmeSubCSA *m_object;
	unsigned char m_unreconstructed00c[0x24];
	AIStateMachine *m_sink;
	unsigned char m_unreconstructed034[0x42c];
	Int m_actionStarted;
};

void Rva002BC400StateAction::run(void *first, unsigned char second, void *third)
{
	if ((m_object->m_flags344 & 1) == 0 && m_object->bfmeAskCSA())
	{
		m_sink->beginAction();
		m_sink->setGoalWaypoint((const Waypoint *)first);
		((Rva002BC470StateAction *)this)->finish(third);
		m_sink->signalAction(0x3f9 + (second != 0));
	}
}

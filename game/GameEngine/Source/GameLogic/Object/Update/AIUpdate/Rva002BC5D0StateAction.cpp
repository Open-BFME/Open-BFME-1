// cl: /DNDEBUG /MD
//
// Address-derived recovery for the BFME state-action body at 0x002BC5D0.
// NEAR-TWIN of 0x002BC540 (Rva002BC540StateAction.cpp): identical shape except
// the "dispatch" virtual call (vtable slot 0x38) is replaced by a
// direct call to StateMachine::setGoalObject.

typedef int Int;

class BfmeSubCSA_2BC5D0
{
public:
	bool bfmeAskCSA();
};

class Rva002BC470StateAction_2BC5D0
{
public:
	void finish(void *argument);
};

class StateMachine_2BC5D0
{
public:
	void setGoalObject(const void *argument);
};

class Rva002BC5D0Sink
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
	virtual void unused024() = 0;
	virtual void unused028() = 0;
	virtual void unused02c() = 0;
	virtual void unused030() = 0;
	virtual void unused034() = 0;
	virtual void dispatch(void *argument) = 0;
};

class Rva002BC5D0StateAction
{
public:
	void run(void *first, void *second, unsigned char third);

private:
	unsigned char m_unreconstructed000[8];
	BfmeSubCSA_2BC5D0 *m_object;
	unsigned char m_unreconstructed00c[0x24];
	StateMachine_2BC5D0 *m_sink;
	unsigned char m_unreconstructed034[0x42c];
	Int m_actionStarted;
};

void Rva002BC5D0StateAction::run(void *first, void *second, unsigned char third)
{
	if (first && m_object->bfmeAskCSA())
	{
		((Rva002BC470StateAction_2BC5D0 *)this)->finish(second);
		((Rva002BC5D0Sink *)m_sink)->beginAction();
		((StateMachine_2BC5D0 *)m_sink)->setGoalObject(first);
		if (third)
			((Rva002BC5D0Sink *)m_sink)->signalAction(0x3f3);
		else
			((Rva002BC5D0Sink *)m_sink)->signalAction(0x3f2);
		m_actionStarted = 1;
	}
}

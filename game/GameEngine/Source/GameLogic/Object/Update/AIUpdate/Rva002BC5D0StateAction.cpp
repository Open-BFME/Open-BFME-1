// cl: /DNDEBUG /MD
//
// Address-derived recovery for the BFME state-action body at 0x002BC5D0.
// NEAR-TWIN of 0x002BC540 (Rva002BC540StateAction.cpp): identical shape except
// the "dispatch" virtual call (vtable slot 0x38) is replaced by a
// direct call to StateMachine::setGoalObject.

typedef int Int;

class ObjectIsMobileBody
{
public:
	bool isMobile() const;
};

class Rva002BC470StateAction_2BC5D0
{
public:
	void finish(void *argument);
};

// Both call targets are 5-byte ILT thunks owned by game/gen_small (rows
// ?j_0003f42c@@YAXXZ at 0x0003F42C and ?j_00035a1c@@YAXXZ at 0x00035A1C in
// targets/game/reverse/functions.csv); the address-scoped helper pins
// ?finish@Rva002BC470StateAction_2BC5D0@@QAEXPAX@Z and
// ?setGoalObject@StateMachine_2BC5D0@@QAEXPBX@Z name the same thunks but
// nothing defines them, so call through the thunks' own names.
extern void j_0003f42c();
extern void j_00035a1c();

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
	ObjectIsMobileBody *m_object;
	unsigned char m_unreconstructed00c[0x24];
	StateMachine_2BC5D0 *m_sink;
	unsigned char m_unreconstructed034[0x42c];
	Int m_actionStarted;
};

typedef void (Rva002BC470StateAction_2BC5D0::*FinishCall)(void *);

union FinishPointer
{
	void (*entry)();
	FinishCall member;
};

typedef void (StateMachine_2BC5D0::*GoalCall)(const void *);

union GoalPointer
{
	void (*entry)();
	GoalCall member;
};

void Rva002BC5D0StateAction::run(void *first, void *second, unsigned char third)
{
	if (first && m_object->isMobile())
	{
		FinishPointer finishCall;
		finishCall.entry = j_0003f42c;
		(((Rva002BC470StateAction_2BC5D0 *)this)->*finishCall.member)(second);
		((Rva002BC5D0Sink *)m_sink)->beginAction();
		GoalPointer goalCall;
		goalCall.entry = j_00035a1c;
		(((StateMachine_2BC5D0 *)m_sink)->*goalCall.member)(first);
		if (third)
			((Rva002BC5D0Sink *)m_sink)->signalAction(0x3f3);
		else
			((Rva002BC5D0Sink *)m_sink)->signalAction(0x3f2);
		m_actionStarted = 1;
	}
}

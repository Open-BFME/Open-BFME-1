// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for the two pool-backed utility
// states in AIStateMachine.h.  The exact constructors and dedicated vtables
// identify the wrappers at retail 0x0017FF50 and 0x0017FF90.  Both classes use
// MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE, whose destructor declaration is
// protected; the MAE access decoration is therefore intentional.
//
// AIDeadState's complete destructor is the 5-byte tail jump at 0x0017FF80 to
// State::~State().  AIDockState's wrapper calls the already matched 106-byte
// owned-machine teardown at 0x0017D7A0 through its complete-dtor ILT.

class State
{
public:
	virtual ~State();
};

class AIDeadState : public State
{
	friend void forceAIDeadStateDeletingDestructor();

protected:
	virtual ~AIDeadState();
};

class AIDockState : public State
{
	friend void forceAIDockStateDeletingDestructor();

protected:
	virtual ~AIDockState();
};

void forceAIDeadStateDeletingDestructor()
{
	AIDeadState value;
}

void forceAIDockStateDeletingDestructor()
{
	AIDockState value;
}

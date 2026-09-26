// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: the two utility states in StateMachine.h have dedicated vtables
// and named constructors.  Their scalar-deleting wrappers are the 30-byte
// bodies at retail 0x0017F250 and 0x0017F290.  Each wrapper dispatches through
// the corresponding complete destructor ILT (0x000047F0 / 0x000161D0), which
// reduces to State::~State().

// The base declaration preserves the State subclass relationship and lets the
// compiler emit each empty derived destructor as the retail tail call to the
// already matched State destructor.
class State
{
public:
	virtual ~State();
};

class FailureState : public State
{
	friend void forceFailureStateDeletingDestructor();

protected:
	virtual ~FailureState() {}
};

class ContinueState : public State
{
	friend void forceContinueStateDeletingDestructor();

protected:
	virtual ~ContinueState() {}
};

void forceFailureStateDeletingDestructor()
{
	FailureState value;
}

void forceContinueStateDeletingDestructor()
{
	ContinueState value;
}

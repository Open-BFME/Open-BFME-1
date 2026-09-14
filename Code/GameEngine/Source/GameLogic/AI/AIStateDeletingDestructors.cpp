// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for two pool-backed AI states. Their
// exact named constructors install dedicated vtables whose slot-zero ILTs
// route to these wrappers; each complete destructor reduces to State cleanup.

class AIBusyState
{
protected:
	virtual ~AIBusyState();
private:
	friend void forceAIBusyStateDeletingDestructor();
};

class AIWaitState
{
protected:
	virtual ~AIWaitState();
private:
	friend void forceAIWaitStateDeletingDestructor();
};

void forceAIBusyStateDeletingDestructor()
{
	AIBusyState value;
}

void forceAIWaitStateDeletingDestructor()
{
	AIWaitState value;
}

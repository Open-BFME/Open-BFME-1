// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for three pool-backed AI movement
// states. Exact named constructors install their dedicated vtables and each
// slot-zero ILT routes to the corresponding 30-byte wrapper below.

class AIWanderState
{
protected:
	virtual ~AIWanderState();
private:
	friend void forceAIWanderStateDeletingDestructor();
};

class AIPanicState
{
protected:
	virtual ~AIPanicState();
private:
	friend void forceAIPanicStateDeletingDestructor();
};

class AIEnterState
{
protected:
	virtual ~AIEnterState();
private:
	friend void forceAIEnterStateDeletingDestructor();
};

void forceAIWanderStateDeletingDestructor() { AIWanderState value; }
void forceAIPanicStateDeletingDestructor() { AIPanicState value; }
void forceAIEnterStateDeletingDestructor() { AIEnterState value; }

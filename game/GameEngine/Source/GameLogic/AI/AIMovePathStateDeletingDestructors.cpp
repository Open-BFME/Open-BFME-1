// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for two pool-backed path movement
// states. Exact named constructors install their dedicated vtables and the
// slot-zero ILTs route to these 30-byte wrappers.

class AIMoveToState
{
protected:
	virtual ~AIMoveToState();
private:
	friend void forceAIMoveToStateDeletingDestructor();
};

class AIAttackFollowWaypointPathState
{
protected:
	virtual ~AIAttackFollowWaypointPathState();
private:
	friend void forceAIAttackFollowWaypointPathStateDeletingDestructor();
};

void forceAIMoveToStateDeletingDestructor() { AIMoveToState value; }
void forceAIAttackFollowWaypointPathStateDeletingDestructor() { AIAttackFollowWaypointPathState value; }

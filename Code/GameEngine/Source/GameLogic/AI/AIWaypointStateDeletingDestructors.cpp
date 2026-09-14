// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for two pool-backed waypoint states.
// Exact named constructors install their dedicated vtables and the slot-zero
// ILTs route to these 30-byte wrappers.

class AIFollowWaypointPathExactState
{
protected:
	virtual ~AIFollowWaypointPathExactState();
private:
	friend void forceAIFollowWaypointPathExactStateDeletingDestructor();
};

class AIWanderInPlaceState
{
protected:
	virtual ~AIWanderInPlaceState();
private:
	friend void forceAIWanderInPlaceStateDeletingDestructor();
};

void forceAIFollowWaypointPathExactStateDeletingDestructor() { AIFollowWaypointPathExactState value; }
void forceAIWanderInPlaceStateDeletingDestructor() { AIWanderInPlaceState value; }

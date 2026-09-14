// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for three pool-backed AI target-
// movement states. Exact named constructors and their dedicated vtable slot
// zero routes establish each 30-byte wrapper independently.

class AIMoveOutOfTheWayState
{
protected:
	virtual ~AIMoveOutOfTheWayState();
private:
	friend void forceAIMoveOutOfTheWayStateDeletingDestructor();
};

class AIMoveAwayFromRepulsorsState
{
protected:
	virtual ~AIMoveAwayFromRepulsorsState();
private:
	friend void forceAIMoveAwayFromRepulsorsStateDeletingDestructor();
};

class AIAttackPursueTargetState
{
protected:
	virtual ~AIAttackPursueTargetState();
private:
	friend void forceAIAttackPursueTargetStateDeletingDestructor();
};

void forceAIMoveOutOfTheWayStateDeletingDestructor() { AIMoveOutOfTheWayState value; }
void forceAIMoveAwayFromRepulsorsStateDeletingDestructor() { AIMoveAwayFromRepulsorsState value; }
void forceAIAttackPursueTargetStateDeletingDestructor() { AIAttackPursueTargetState value; }

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for seven pool-backed AI target-
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

class AIAttackMeleeHordeApproachTargetState
{
protected:
	virtual ~AIAttackMeleeHordeApproachTargetState();
private:
	friend void forceAIAttackMeleeHordeApproachTargetStateDeletingDestructor();
};

class AIAttackFireDuringApproachState
{
protected:
	virtual ~AIAttackFireDuringApproachState();
private:
	friend void forceAIAttackFireDuringApproachStateDeletingDestructor();
};

class AIAttackMeleeSquishState
{
protected:
	virtual ~AIAttackMeleeSquishState();
private:
	friend void forceAIAttackMeleeSquishStateDeletingDestructor();
};

class AIAttackMeleeEngageState
{
protected:
	virtual ~AIAttackMeleeEngageState();
private:
	friend void forceAIAttackMeleeEngageStateDeletingDestructor();
};

void forceAIMoveOutOfTheWayStateDeletingDestructor() { AIMoveOutOfTheWayState value; }
void forceAIMoveAwayFromRepulsorsStateDeletingDestructor() { AIMoveAwayFromRepulsorsState value; }
void forceAIAttackPursueTargetStateDeletingDestructor() { AIAttackPursueTargetState value; }
void forceAIAttackMeleeHordeApproachTargetStateDeletingDestructor() { AIAttackMeleeHordeApproachTargetState value; }
void forceAIAttackFireDuringApproachStateDeletingDestructor() { AIAttackFireDuringApproachState value; }
void forceAIAttackMeleeSquishStateDeletingDestructor() { AIAttackMeleeSquishState value; }
void forceAIAttackMeleeEngageStateDeletingDestructor() { AIAttackMeleeEngageState value; }

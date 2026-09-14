// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for two pool-backed AI states. Exact
// named constructors install their dedicated vtables and the slot-zero ILTs
// route to these 30-byte wrappers.

class AIAttackSquadState
{
protected:
	virtual ~AIAttackSquadState();
private:
	friend void forceAIAttackSquadStateDeletingDestructor();
};

class AIIdleState
{
protected:
	virtual ~AIIdleState();
private:
	friend void forceAIIdleStateDeletingDestructor();
};

void forceAIAttackSquadStateDeletingDestructor() { AIAttackSquadState value; }
void forceAIIdleStateDeletingDestructor() { AIIdleState value; }

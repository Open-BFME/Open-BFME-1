// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for two AIGuard states whose empty
// complete destructors tail-call State. Exact named constructors install the
// dedicated vtables and their slot-zero ILTs route to these wrappers.

class AIGuardOuterState
{
protected:
	virtual ~AIGuardOuterState();
private:
	friend void forceAIGuardOuterStateDeletingDestructor();
};

class AIGuardAttackAggressorState
{
protected:
	virtual ~AIGuardAttackAggressorState();
private:
	friend void forceAIGuardAttackAggressorStateDeletingDestructor();
};

void forceAIGuardOuterStateDeletingDestructor()
{
	AIGuardOuterState value;
}

void forceAIGuardAttackAggressorStateDeletingDestructor()
{
	AIGuardAttackAggressorState value;
}

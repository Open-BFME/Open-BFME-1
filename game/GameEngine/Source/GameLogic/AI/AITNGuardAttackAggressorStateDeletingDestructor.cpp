// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AITNGuardAttackAggressorState.
// Vtable 0x00C9B7A0 slots name this class (?update@AITNGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x0001C9F9 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00046D30 reaches cleanup body 0x000A1B30.

class AITNGuardAttackAggressorState
{
protected:
	virtual ~AITNGuardAttackAggressorState();
private:
	friend void forceAITNGuardAttackAggressorStateDeletingDestructor();
};

void forceAITNGuardAttackAggressorStateDeletingDestructor()
{
	AITNGuardAttackAggressorState value;
}

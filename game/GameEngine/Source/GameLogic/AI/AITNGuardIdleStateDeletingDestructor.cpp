// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AITNGuardIdleState.
// Vtable 0x00C9B5E0 slots name this class (?onEnter@AITNGuardIdleState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00041D62 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00022FB1 reaches cleanup body 0x000A1B30.

class AITNGuardIdleState
{
protected:
	virtual ~AITNGuardIdleState();
private:
	friend void forceAITNGuardIdleStateDeletingDestructor();
};

void forceAITNGuardIdleStateDeletingDestructor()
{
	AITNGuardIdleState value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AITNGuardInnerState.
// Vtable 0x00C9B560 slots name this class (?update@AITNGuardInnerState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00045D3B to this 30-byte wrapper, whose complete destructor
// route ILT 0x00041ED4 reaches cleanup body 0x000A1B30.

class AITNGuardInnerState
{
protected:
	virtual ~AITNGuardInnerState();
private:
	friend void forceAITNGuardInnerStateDeletingDestructor();
};

void forceAITNGuardInnerStateDeletingDestructor()
{
	AITNGuardInnerState value;
}

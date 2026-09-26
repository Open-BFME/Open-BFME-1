// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AITNGuardOuterState.
// Vtable 0x00C9B650 slots name this class (?update@AITNGuardOuterState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00048540 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000321A0 reaches cleanup body 0x000A1B30.

class AITNGuardOuterState
{
protected:
	virtual ~AITNGuardOuterState();
private:
	friend void forceAITNGuardOuterStateDeletingDestructor();
};

void forceAITNGuardOuterStateDeletingDestructor()
{
	AITNGuardOuterState value;
}

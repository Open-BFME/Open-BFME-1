// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIDockWaitForClearanceState.
// Vtable 0x00C95BF0 slots name this class (?onEnter@AIDockWaitForClearanceState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x0002B8B9 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001AD66 reaches cleanup body 0x000A1B30.

class AIDockWaitForClearanceState
{
protected:
	virtual ~AIDockWaitForClearanceState();
private:
	friend void forceAIDockWaitForClearanceStateDeletingDestructor();
};

void forceAIDockWaitForClearanceStateDeletingDestructor()
{
	AIDockWaitForClearanceState value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIDockAdvancePositionState.
// Vtable 0x00C95C68 slots name this class (?onEnter@AIDockAdvancePositionState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x0004B3D0 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00016F31 reaches cleanup body 0x00172430.

class AIDockAdvancePositionState
{
protected:
	virtual ~AIDockAdvancePositionState();
private:
	friend void forceAIDockAdvancePositionStateDeletingDestructor();
};

void forceAIDockAdvancePositionStateDeletingDestructor()
{
	AIDockAdvancePositionState value;
}

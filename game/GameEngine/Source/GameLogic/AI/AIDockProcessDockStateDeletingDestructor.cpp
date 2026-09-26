// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIDockProcessDockState.
// Vtable 0x00C95EA0 slots name this class (?onEnter@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x0003B8E5 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003E6CB reaches cleanup body 0x000A1B30.

class AIDockProcessDockState
{
protected:
	virtual ~AIDockProcessDockState();
private:
	friend void forceAIDockProcessDockStateDeletingDestructor();
};

void forceAIDockProcessDockStateDeletingDestructor()
{
	AIDockProcessDockState value;
}

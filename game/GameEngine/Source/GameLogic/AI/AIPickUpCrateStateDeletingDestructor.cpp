// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIPickUpCrateState.
// Vtable 0x00C960D0 slots name this class (?onEnter@AIPickUpCrateState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00044599 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0004B213 reaches cleanup body 0x00172430.

class AIPickUpCrateState
{
protected:
	virtual ~AIPickUpCrateState();
private:
	friend void forceAIPickUpCrateStateDeletingDestructor();
};

void forceAIPickUpCrateStateDeletingDestructor()
{
	AIPickUpCrateState value;
}

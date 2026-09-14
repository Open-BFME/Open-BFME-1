// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIExitState.
// Vtable 0x00C98120 slots name this class (?onExit@AIExitState@@UAEXW4StateExitType@@@Z); its slot zero routes
// through ILT 0x0001CDFF to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001B22F reaches cleanup body 0x000A1B30.

class AIExitState
{
protected:
	virtual ~AIExitState();
private:
	friend void forceAIExitStateDeletingDestructor();
};

void forceAIExitStateDeletingDestructor()
{
	AIExitState value;
}

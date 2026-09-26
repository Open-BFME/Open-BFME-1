// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIGuardRetaliateReturnState.
// Vtable 0x00C96520 slots name this class (?onEnter@AIGuardRetaliateReturnState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00029820 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002FD83 reaches cleanup body 0x00172430.

class AIGuardRetaliateReturnState
{
protected:
	virtual ~AIGuardRetaliateReturnState();
private:
	friend void forceAIGuardRetaliateReturnStateDeletingDestructor();
};

void forceAIGuardRetaliateReturnStateDeletingDestructor()
{
	AIGuardRetaliateReturnState value;
}

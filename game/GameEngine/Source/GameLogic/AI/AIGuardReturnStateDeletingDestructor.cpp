// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIGuardReturnState.
// Vtable 0x00C962C8 slots name this class (?onEnter@AIGuardReturnState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00015578 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002EF82 reaches cleanup body 0x00172430.

class AIGuardReturnState
{
protected:
	virtual ~AIGuardReturnState();
private:
	friend void forceAIGuardReturnStateDeletingDestructor();
};

void forceAIGuardReturnStateDeletingDestructor()
{
	AIGuardReturnState value;
}

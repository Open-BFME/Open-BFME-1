// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIHuntState.
// Vtable 0x00C98330 slots name this class (?onEnter@AIHuntState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x000453EF to this 30-byte wrapper, whose complete destructor
// route ILT 0x000409BC reaches cleanup body 0x0017E3F0.

class AIHuntState
{
protected:
	virtual ~AIHuntState();
private:
	friend void forceAIHuntStateDeletingDestructor();
};

void forceAIHuntStateDeletingDestructor()
{
	AIHuntState value;
}

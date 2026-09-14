// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIBackAwayAndCowerState.
// Vtable 0x00C97AF8 slots name this class (?onEnter@AIBackAwayAndCowerState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00014CF9 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000061CC reaches cleanup body 0x00173F30.

class AIBackAwayAndCowerState
{
protected:
	virtual ~AIBackAwayAndCowerState();
private:
	friend void forceAIBackAwayAndCowerStateDeletingDestructor();
};

void forceAIBackAwayAndCowerStateDeletingDestructor()
{
	AIBackAwayAndCowerState value;
}

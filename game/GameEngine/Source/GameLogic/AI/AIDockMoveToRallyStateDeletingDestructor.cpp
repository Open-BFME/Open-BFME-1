// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIDockMoveToRallyState.
// Vtable 0x00C95DB0 slots name this class (?onEnter@AIDockMoveToRallyState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x0004410C to this 30-byte wrapper, whose complete destructor
// route ILT 0x00031C9B reaches cleanup body 0x00172430.

class AIDockMoveToRallyState
{
protected:
	virtual ~AIDockMoveToRallyState();
private:
	friend void forceAIDockMoveToRallyStateDeletingDestructor();
};

void forceAIDockMoveToRallyStateDeletingDestructor()
{
	AIDockMoveToRallyState value;
}

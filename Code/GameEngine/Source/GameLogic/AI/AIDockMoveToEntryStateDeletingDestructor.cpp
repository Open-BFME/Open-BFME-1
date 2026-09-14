// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIDockMoveToEntryState.
// Vtable 0x00C95CC0 slots name this class (?onEnter@AIDockMoveToEntryState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00036476 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000315ED reaches cleanup body 0x00172430.

class AIDockMoveToEntryState
{
protected:
	virtual ~AIDockMoveToEntryState();
private:
	friend void forceAIDockMoveToEntryStateDeletingDestructor();
};

void forceAIDockMoveToEntryStateDeletingDestructor()
{
	AIDockMoveToEntryState value;
}

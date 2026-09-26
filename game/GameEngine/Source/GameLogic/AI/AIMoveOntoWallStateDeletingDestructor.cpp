// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIMoveOntoWallState.
// Vtable 0x00C98540 slots name this class (?xfer@AIMoveOntoWallState@@MAEXPAVXfer@@@Z); its slot zero routes
// through ILT 0x0003125A to this 30-byte wrapper, whose complete destructor
// route ILT 0x00010C4E reaches cleanup body 0x00171DB0.

class AIMoveOntoWallState
{
protected:
	virtual ~AIMoveOntoWallState();
private:
	friend void forceAIMoveOntoWallStateDeletingDestructor();
};

void forceAIMoveOntoWallStateDeletingDestructor()
{
	AIMoveOntoWallState value;
}

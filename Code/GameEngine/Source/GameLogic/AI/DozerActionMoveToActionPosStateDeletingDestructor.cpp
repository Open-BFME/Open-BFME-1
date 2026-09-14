// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DozerActionMoveToActionPosState.
// Vtable 0x00CC6DA0 slots name this class (?update@DozerActionMoveToActionPosState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00030BB6 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000188DB reaches cleanup body 0x000A1B30.

class DozerActionMoveToActionPosState
{
protected:
	virtual ~DozerActionMoveToActionPosState();
private:
	friend void forceDozerActionMoveToActionPosStateDeletingDestructor();
};

void forceDozerActionMoveToActionPosStateDeletingDestructor()
{
	DozerActionMoveToActionPosState value;
}

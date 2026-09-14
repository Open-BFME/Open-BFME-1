// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DozerActionState.
// Vtable 0x00CC6F70 slots name this class (?onEnter@DozerActionState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00035AA3 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00030B52 reaches cleanup body 0x002B85C0.

class DozerActionState
{
protected:
	virtual ~DozerActionState();
private:
	friend void forceDozerActionStateDeletingDestructor();
};

void forceDozerActionStateDeletingDestructor()
{
	DozerActionState value;
}

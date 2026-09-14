// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DozerPrimaryIdleState.
// Vtable 0x00CC6F00 slots name this class (?onExit@DozerPrimaryIdleState@@UAEXW4StateExitType@@@Z); its slot zero routes
// through ILT 0x0001C562 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003E5EF reaches cleanup body 0x000A1B30.

class DozerPrimaryIdleState
{
protected:
	virtual ~DozerPrimaryIdleState();
private:
	friend void forceDozerPrimaryIdleStateDeletingDestructor();
};

void forceDozerPrimaryIdleStateDeletingDestructor()
{
	DozerPrimaryIdleState value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: MoveAwayPanicState scalar-deleting destructor at retail RVA
// 0x001852D0 (30 bytes). The exact named constructor at 0x0017F4A0 passes
// "AIMoveAwayPanicState" and installs vtable 0x0109A3E0. Its slot zero routes
// through ILT 0x0003EC89 to this wrapper, whose complete destructor chains to
// the exact AIInternalMoveToState destructor.

class MoveAwayPanicState
{
protected:
	virtual ~MoveAwayPanicState();

private:
	friend void forceMoveAwayPanicStateDeletingDestructor();
};

void forceMoveAwayPanicStateDeletingDestructor()
{
	MoveAwayPanicState value;
}

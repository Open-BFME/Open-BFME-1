// cl: /DNDEBUG /MD /EHsc
//
// The exact constructor at 0x00180450 installs vtable 0x0109AD88 for
// MoveAwayAndCowerState. Its slot-zero ILT 0x0001B162 identifies the retail
// scalar-deleting wrapper at 0x00185850; the wrapper calls complete-dtor ILT
// 0x0000EA84.

class MoveAwayAndCowerState
{
protected:
	virtual ~MoveAwayAndCowerState();

private:
	friend void forceMoveAwayAndCowerStateDeletingDestructor();
};

void forceMoveAwayAndCowerStateDeletingDestructor()
{
	MoveAwayAndCowerState value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIMoveToPositionAndDieState scalar-deleting destructor at retail
// RVA 0x001856C0 (30 bytes). Constructor 0x0017FDC0 installs vtable
// 0x0109AB50, whose slot zero routes through ILT 0x00019E7F to this wrapper.
// The exact named update body and matching literal prove class identity; the
// complete destructor chains to AIInternalMoveToState.

class AIMoveToPositionAndDieState
{
protected:
	virtual ~AIMoveToPositionAndDieState();

private:
	friend void forceAIMoveToPositionAndDieStateDeletingDestructor();
};

void forceAIMoveToPositionAndDieStateDeletingDestructor()
{
	AIMoveToPositionAndDieState value;
}

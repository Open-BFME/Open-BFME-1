// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIMoveToStateSA scalar-deleting destructor at retail RVA
// 0x00182150 (30 bytes). Constructor 0x00173620 passes the literal class name
// and installs vtable 0x01098FA8. Its slot zero routes through ILT 0x0001B0CC
// to this wrapper; the same table owns the exact computePath, onEnter, and
// update bodies. The complete destructor chains to AIInternalMoveToState.

class AIMoveToStateSA
{
protected:
	virtual ~AIMoveToStateSA();

private:
	friend void forceAIMoveToStateSADeletingDestructor();
};

void forceAIMoveToStateSADeletingDestructor()
{
	AIMoveToStateSA value;
}

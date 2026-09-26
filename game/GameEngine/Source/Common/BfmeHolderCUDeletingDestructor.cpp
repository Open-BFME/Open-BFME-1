// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BfmeHolderCU.
// Constructor 0x005DD290 installs dedicated vtable 0x00D1126C; its slot
// zero routes through ILT 0x00003E3B to this 30-byte wrapper, whose complete
// destructor route ILT 0x0000CC16 reaches cleanup body 0x005DD320.

class BfmeHolderCU
{
protected:
	virtual ~BfmeHolderCU();
private:
	friend void forceBfmeHolderCUDeletingDestructor();
};

void forceBfmeHolderCUDeletingDestructor()
{
	BfmeHolderCU value;
}

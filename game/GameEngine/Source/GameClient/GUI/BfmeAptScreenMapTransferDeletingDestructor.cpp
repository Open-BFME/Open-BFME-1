// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BfmeAptScreenMapTransfer.
// Constructor 0x005104C0 installs dedicated vtable 0x00D05048; its slot
// zero routes through ILT 0x0002B51C to this 30-byte wrapper, whose complete
// destructor route ILT 0x0000118B reaches cleanup body 0x00510310.

class BfmeAptScreenMapTransfer
{
protected:
	virtual ~BfmeAptScreenMapTransfer();
private:
	friend void forceBfmeAptScreenMapTransferDeletingDestructor();
};

void forceBfmeAptScreenMapTransferDeletingDestructor()
{
	BfmeAptScreenMapTransfer value;
}

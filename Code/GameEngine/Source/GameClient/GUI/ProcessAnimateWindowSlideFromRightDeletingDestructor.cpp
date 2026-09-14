// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProcessAnimateWindowSlideFromRight.
// Constructor 0x00495650 installs dedicated vtable 0x00CFA254; its slot
// zero routes through ILT 0x00015203 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00043FB8 reaches cleanup body 0x00495690.

class ProcessAnimateWindowSlideFromRight
{
protected:
	virtual ~ProcessAnimateWindowSlideFromRight();
private:
	friend void forceProcessAnimateWindowSlideFromRightDeletingDestructor();
};

void forceProcessAnimateWindowSlideFromRightDeletingDestructor()
{
	ProcessAnimateWindowSlideFromRight value;
}

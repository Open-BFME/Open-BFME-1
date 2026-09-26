// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProcessAnimateWindowSlideFromLeft.
// Constructor 0x00495AC0 installs dedicated vtable 0x00CFA270; its slot
// zero routes through ILT 0x0000FE07 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00015FAA reaches cleanup body 0x00495B00.

class ProcessAnimateWindowSlideFromLeft
{
protected:
	virtual ~ProcessAnimateWindowSlideFromLeft();
private:
	friend void forceProcessAnimateWindowSlideFromLeftDeletingDestructor();
};

void forceProcessAnimateWindowSlideFromLeftDeletingDestructor()
{
	ProcessAnimateWindowSlideFromLeft value;
}

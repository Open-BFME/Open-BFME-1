// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProcessAnimateWindowSlideFromTop.
// Constructor 0x00495F30 installs dedicated vtable 0x00CFA28C; its slot
// zero routes through ILT 0x00004AD9 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0000A812 reaches cleanup body 0x00495F70.

class ProcessAnimateWindowSlideFromTop
{
protected:
	virtual ~ProcessAnimateWindowSlideFromTop();
private:
	friend void forceProcessAnimateWindowSlideFromTopDeletingDestructor();
};

void forceProcessAnimateWindowSlideFromTopDeletingDestructor()
{
	ProcessAnimateWindowSlideFromTop value;
}

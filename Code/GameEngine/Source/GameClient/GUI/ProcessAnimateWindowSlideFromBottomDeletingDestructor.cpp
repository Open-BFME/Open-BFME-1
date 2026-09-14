// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProcessAnimateWindowSlideFromBottom.
// Constructor 0x004963B0 installs dedicated vtable 0x00CFA2A8; its slot
// zero routes through ILT 0x0002A004 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0003EF7C reaches cleanup body 0x004963F0.

class ProcessAnimateWindowSlideFromBottom
{
protected:
	virtual ~ProcessAnimateWindowSlideFromBottom();
private:
	friend void forceProcessAnimateWindowSlideFromBottomDeletingDestructor();
};

void forceProcessAnimateWindowSlideFromBottomDeletingDestructor()
{
	ProcessAnimateWindowSlideFromBottom value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProcessAnimateWindowSlideFromRightFast.
// Constructor 0x004973C0 installs dedicated vtable 0x00CFA2E0; its slot
// zero routes through ILT 0x00001EA6 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00025C70 reaches cleanup body 0x00497400.

class ProcessAnimateWindowSlideFromRightFast
{
protected:
	virtual ~ProcessAnimateWindowSlideFromRightFast();
private:
	friend void forceProcessAnimateWindowSlideFromRightFastDeletingDestructor();
};

void forceProcessAnimateWindowSlideFromRightFastDeletingDestructor()
{
	ProcessAnimateWindowSlideFromRightFast value;
}

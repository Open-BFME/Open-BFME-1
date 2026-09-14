// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProcessAnimateWindowSlideFromBottomTimed.
// Constructor 0x004953F0 installs dedicated vtable 0x00CFA21C; its slot
// zero routes through ILT 0x00034798 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00015582 reaches cleanup body 0x00495420.

class ProcessAnimateWindowSlideFromBottomTimed
{
protected:
	virtual ~ProcessAnimateWindowSlideFromBottomTimed();
private:
	friend void forceProcessAnimateWindowSlideFromBottomTimedDeletingDestructor();
};

void forceProcessAnimateWindowSlideFromBottomTimedDeletingDestructor()
{
	ProcessAnimateWindowSlideFromBottomTimed value;
}

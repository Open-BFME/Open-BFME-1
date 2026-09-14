// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProcessAnimateWindowSlideFromTopFast.
// Constructor 0x00496F30 installs dedicated vtable 0x00CFA2C4; its slot
// zero routes through ILT 0x0002A6C6 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00044E45 reaches cleanup body 0x00496F70.

class ProcessAnimateWindowSlideFromTopFast
{
protected:
	virtual ~ProcessAnimateWindowSlideFromTopFast();
private:
	friend void forceProcessAnimateWindowSlideFromTopFastDeletingDestructor();
};

void forceProcessAnimateWindowSlideFromTopFastDeletingDestructor()
{
	ProcessAnimateWindowSlideFromTopFast value;
}

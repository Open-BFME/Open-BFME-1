// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProcessAnimateWindowSpiral.
// Vtable 0x00CFA238 slots name this class (?initAnimateWindow@ProcessAnimateWindowSpiral@@UAEXPAVAnimateWindow@@@Z); its slot zero routes
// through ILT 0x0003A43B to this 30-byte wrapper, whose complete destructor
// route ILT 0x00048BC6 reaches cleanup body 0x00495600.

class ProcessAnimateWindowSpiral
{
protected:
	virtual ~ProcessAnimateWindowSpiral();
private:
	friend void forceProcessAnimateWindowSpiralDeletingDestructor(const ProcessAnimateWindowSpiral &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceProcessAnimateWindowSpiralDeletingDestructor(const ProcessAnimateWindowSpiral &that)
{
	ProcessAnimateWindowSpiral value(that);
}

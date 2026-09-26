// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LocomotorTemplate.
// Constructor 0x001B52C0 installs dedicated vtable 0x00C9DE9C; its slot
// zero routes through ILT 0x0000F9AC to this 30-byte wrapper, whose complete
// destructor route ILT 0x0003296B reaches cleanup body 0x001B5550.

class LocomotorTemplate
{
protected:
	virtual ~LocomotorTemplate();
private:
	friend void forceLocomotorTemplateDeletingDestructor();
};

void forceLocomotorTemplateDeletingDestructor()
{
	LocomotorTemplate value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for EnragedBehavior.
// Vtable 0x00CA3D9C slots name this class (?getModuleNameKey@EnragedBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0003EB49 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000E822 reaches cleanup body 0x001FAD80.

class EnragedBehavior
{
protected:
	virtual ~EnragedBehavior();
private:
	friend void forceEnragedBehaviorDeletingDestructor();
};

void forceEnragedBehaviorDeletingDestructor()
{
	EnragedBehavior value;
}

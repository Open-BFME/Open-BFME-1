// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for VisPolyClass.
// Constructor 0x007A1750 installs dedicated vtable 0x00D27AC8; its slot
// zero routes through ILT 0x00025A59 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0002880D reaches cleanup body 0x007A00F0.

class VisPolyClass
{
protected:
	virtual ~VisPolyClass();
private:
	friend void forceVisPolyClassDeletingDestructor();
};

void forceVisPolyClassDeletingDestructor()
{
	VisPolyClass value;
}

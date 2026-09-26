// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for UpgradeDie.
// Vtable 0x00CB350C slots name this class (?getClassMemoryPool@UpgradeDie@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0002160C to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001B7B6 reaches cleanup body 0x002560A0.

class UpgradeDie
{
protected:
	virtual ~UpgradeDie();
private:
	friend void forceUpgradeDieDeletingDestructor();
};

void forceUpgradeDieDeletingDestructor()
{
	UpgradeDie value;
}

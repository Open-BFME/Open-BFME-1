// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ApplyRandomForceNugget.
// Constructor 0x003B7610 installs dedicated vtable 0x00CEC764; its slot
// zero routes through ILT 0x00011AD6 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00038DAC reaches cleanup body 0x003B7640.

class ApplyRandomForceNugget
{
protected:
	virtual ~ApplyRandomForceNugget();
private:
	friend void forceApplyRandomForceNuggetDeletingDestructor();
};

void forceApplyRandomForceNuggetDeletingDestructor()
{
	ApplyRandomForceNugget value;
}

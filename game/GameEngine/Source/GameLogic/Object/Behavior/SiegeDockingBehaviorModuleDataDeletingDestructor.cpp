// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SiegeDockingBehaviorModuleData.
// Constructor 0x00205F60 installs dedicated vtable 0x00CA61F0; its slot
// zero routes through ILT 0x00012125 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00006451 reaches cleanup body 0x002060A0.

class SiegeDockingBehaviorModuleData
{
protected:
	virtual ~SiegeDockingBehaviorModuleData();
private:
	friend void forceSiegeDockingBehaviorModuleDataDeletingDestructor();
};

void forceSiegeDockingBehaviorModuleDataDeletingDestructor()
{
	SiegeDockingBehaviorModuleData value;
}

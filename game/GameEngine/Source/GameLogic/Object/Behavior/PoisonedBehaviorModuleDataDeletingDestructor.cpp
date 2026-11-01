// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PoisonedBehaviorModuleData.
// Constructor 0x002029B0 installs dedicated vtable 0x00CA53B8; its slot
// zero routes through ILT 0x0002351A to this 30-byte wrapper, whose complete
// destructor route ILT 0x000443FF reaches cleanup body 0x00202DE0.

class PoisonedBehaviorModuleData
{
public:
	virtual ~PoisonedBehaviorModuleData();
private:
	friend void forcePoisonedBehaviorModuleDataDeletingDestructor();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forcePoisonedBehaviorModuleDataDeletingDestructor(const PoisonedBehaviorModuleData &that)
{
	PoisonedBehaviorModuleData value(that);
}

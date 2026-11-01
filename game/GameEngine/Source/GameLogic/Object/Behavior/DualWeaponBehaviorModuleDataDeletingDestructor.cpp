// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DualWeaponBehaviorModuleData.
// Constructor 0x001F7E20 installs dedicated vtable 0x00CA3468; its slot
// zero routes through ILT 0x000320BA to this 30-byte wrapper, whose complete
// destructor route ILT 0x000364EE reaches cleanup body 0x001F8070.

class DualWeaponBehaviorModuleData
{
public:
	virtual ~DualWeaponBehaviorModuleData();
private:
	friend void forceDualWeaponBehaviorModuleDataDeletingDestructor(const DualWeaponBehaviorModuleData &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceDualWeaponBehaviorModuleDataDeletingDestructor(const DualWeaponBehaviorModuleData &that)
{
	DualWeaponBehaviorModuleData value(that);
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AimWeaponBehaviorModuleData.
// Constructor 0x001ECEF0 installs dedicated vtable 0x00CA1848; its slot
// zero routes through ILT 0x00037F0B to this 30-byte wrapper, whose complete
// destructor route ILT 0x00039397 reaches cleanup body 0x001ED150.

class AimWeaponBehaviorModuleData
{
public:
	virtual ~AimWeaponBehaviorModuleData();
private:
	friend void forceAimWeaponBehaviorModuleDataDeletingDestructor(const AimWeaponBehaviorModuleData &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceAimWeaponBehaviorModuleDataDeletingDestructor(const AimWeaponBehaviorModuleData &that)
{
	AimWeaponBehaviorModuleData value(that);
}

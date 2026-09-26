// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AimWeaponBehaviorModuleData.
// Constructor 0x001ECEF0 installs dedicated vtable 0x00CA1848; its slot
// zero routes through ILT 0x00037F0B to this 30-byte wrapper, whose complete
// destructor route ILT 0x00039397 reaches cleanup body 0x001ED150.

class AimWeaponBehaviorModuleData
{
protected:
	virtual ~AimWeaponBehaviorModuleData();
private:
	friend void forceAimWeaponBehaviorModuleDataDeletingDestructor();
};

void forceAimWeaponBehaviorModuleDataDeletingDestructor()
{
	AimWeaponBehaviorModuleData value;
}

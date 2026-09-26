// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AimWeaponBehavior.
// Vtable 0x00CA1A24 slots name this class (?getModuleNameKey@AimWeaponBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00042825 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00045C5A reaches cleanup body 0x001ECEB0.

class AimWeaponBehavior
{
protected:
	virtual ~AimWeaponBehavior();
private:
	friend void forceAimWeaponBehaviorDeletingDestructor();
};

void forceAimWeaponBehaviorDeletingDestructor()
{
	AimWeaponBehavior value;
}

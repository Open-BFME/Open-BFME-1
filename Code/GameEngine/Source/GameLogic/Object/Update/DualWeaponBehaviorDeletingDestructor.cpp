// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DualWeaponBehavior.
// Vtable 0x00CA3694 slots name this class (?getModuleNameKey@DualWeaponBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0000AFFB to this 30-byte wrapper, whose complete destructor
// route ILT 0x00032D49 reaches cleanup body 0x001F7DD0.

class DualWeaponBehavior
{
protected:
	virtual ~DualWeaponBehavior();
private:
	friend void forceDualWeaponBehaviorDeletingDestructor();
};

void forceDualWeaponBehaviorDeletingDestructor()
{
	DualWeaponBehavior value;
}

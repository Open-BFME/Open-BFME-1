// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for WeaponSetUpgrade.
// Vtable 0x00CCE824 slots name this class (?getClassMemoryPool@WeaponSetUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00010F5A to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003E45A reaches cleanup body 0x002DA4A0.

class WeaponSetUpgrade
{
protected:
	virtual ~WeaponSetUpgrade();
private:
	friend void forceWeaponSetUpgradeDeletingDestructor();
};

void forceWeaponSetUpgradeDeletingDestructor()
{
	WeaponSetUpgrade value;
}

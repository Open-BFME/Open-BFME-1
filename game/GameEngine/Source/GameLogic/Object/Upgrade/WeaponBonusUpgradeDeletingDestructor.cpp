// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for WeaponBonusUpgrade.
// Vtable 0x00CCE6CC slots name this class (?getClassMemoryPool@WeaponBonusUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00043A27 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00022020 reaches cleanup body 0x002DA2D0.

class WeaponBonusUpgrade
{
protected:
	virtual ~WeaponBonusUpgrade();
private:
	friend void forceWeaponBonusUpgradeDeletingDestructor();
};

void forceWeaponBonusUpgradeDeletingDestructor()
{
	WeaponBonusUpgrade value;
}

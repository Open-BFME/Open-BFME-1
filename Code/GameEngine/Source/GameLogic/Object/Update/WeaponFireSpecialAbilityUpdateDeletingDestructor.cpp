// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: WeaponFireSpecialAbilityUpdate scalar-deleting destructor at
// retail RVA 0x0026D490 (30 bytes).  The matched instance constructor at
// 0x0026D670, complete destructor at 0x0026D320, friend_newModuleInstance
// factory, module-name getter, and xfer body independently establish the
// class identity.

class WeaponFireSpecialAbilityUpdate
{
public:
	virtual ~WeaponFireSpecialAbilityUpdate();
};

void forceWeaponFireSpecialAbilityUpdateDeletingDestructor()
{
	WeaponFireSpecialAbilityUpdate value;
}

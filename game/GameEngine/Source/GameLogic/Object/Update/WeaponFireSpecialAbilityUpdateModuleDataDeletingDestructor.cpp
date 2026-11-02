// cl: /DNDEBUG /MD /EHsc
//
// Retail's WeaponFireSpecialAbilityUpdateModuleData vtable at 0x010B8D98 names
// this scalar deleting destructor in slot zero (ILT 0x00039FF4 -> 0x0026D780).
// Its call target is the independently matched destructor body at 0x0026D7B0.

class __declspec(novtable) WeaponFireSpecialAbilityUpdateModuleDataBase
{
public:
	virtual ~WeaponFireSpecialAbilityUpdateModuleDataBase();
};

class WeaponFireSpecialAbilityUpdateModuleData
	: public WeaponFireSpecialAbilityUpdateModuleDataBase
{
	friend void forceWeaponFireSpecialAbilityUpdateModuleDataDeletingDestructorCopy(const WeaponFireSpecialAbilityUpdateModuleData &that);
public:
	__declspec(noinline) virtual ~WeaponFireSpecialAbilityUpdateModuleData();
};

// ~WeaponFireSpecialAbilityUpdateModuleData is matched out of line (WeaponFireSpecialAbilityUpdateModuleDataDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceWeaponFireSpecialAbilityUpdateModuleDataDeletingDestructorCopy(const WeaponFireSpecialAbilityUpdateModuleData &that)
{
	WeaponFireSpecialAbilityUpdateModuleData value(that);
}

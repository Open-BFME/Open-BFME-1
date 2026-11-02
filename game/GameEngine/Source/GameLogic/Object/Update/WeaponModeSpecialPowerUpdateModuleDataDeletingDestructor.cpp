// cl: /DNDEBUG /MD /EHsc
//
// Retail's WeaponModeSpecialPowerUpdateModuleData vtable at 0x010C5510 names
// this scalar deleting destructor in slot zero (ILT 0x00017CEC -> 0x002B2D40).
// Its call target is the independently matched destructor body at 0x002B2D70.

class __declspec(novtable) WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	virtual ~WeaponModeSpecialPowerUpdateModuleDataBase();
};

class WeaponModeSpecialPowerUpdateModuleData
	: public WeaponModeSpecialPowerUpdateModuleDataBase
{
	friend void forceWeaponModeSpecialPowerUpdateModuleDataDeletingDestructorCopy(const WeaponModeSpecialPowerUpdateModuleData &that);
public:
	__declspec(noinline) virtual ~WeaponModeSpecialPowerUpdateModuleData();
};

// ~WeaponModeSpecialPowerUpdateModuleData is matched out of line (WeaponModeSpecialPowerUpdateModuleDataDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceWeaponModeSpecialPowerUpdateModuleDataDeletingDestructorCopy(const WeaponModeSpecialPowerUpdateModuleData &that)
{
	WeaponModeSpecialPowerUpdateModuleData value(that);
}

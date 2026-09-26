// cl: /DNDEBUG /MD /EHsc
//
// Retail's WeaponModeSpecialPowerUpdateModuleData vtable at 0x010C5510 names
// this scalar deleting destructor in slot zero (ILT 0x00017CEC -> 0x002B2D40).
// Its call target is the independently matched destructor body at 0x002B2D70.

class WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	virtual ~WeaponModeSpecialPowerUpdateModuleDataBase();
};

class WeaponModeSpecialPowerUpdateModuleData
	: public WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	__declspec(noinline) virtual ~WeaponModeSpecialPowerUpdateModuleData();
};

WeaponModeSpecialPowerUpdateModuleData::~WeaponModeSpecialPowerUpdateModuleData()
{
}

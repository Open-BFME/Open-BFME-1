// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: WeaponModeSpecialPowerUpdateModuleDataBase scalar-deleting
// destructor at retail RVA 0x0026A9F0 (30 bytes).
//
// The named base constructor at 0x0026A820 constructs the four 0x70-byte
// named-slot members and installs vtable 0x010B7D40.  That vtable's slot zero
// is ILT 0x00036BA6, which jumps directly to this wrapper.  The wrapper calls
// the named base-dtor pin at ILT 0x0001BBE4; its 112-byte target is the
// ICF-shared four-slot destructor body at 0x0025A4A0.

class WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	virtual ~WeaponModeSpecialPowerUpdateModuleDataBase();
};

void Force_WeaponModeSpecialPowerUpdateModuleDataBase_Deleting_Destructor()
{
	WeaponModeSpecialPowerUpdateModuleDataBase value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: WeaponChangeSpecialPowerModuleModuleData scalar-deleting
// destructor at retail RVA 0x0026CEE0 (30 bytes).  The matched constructor at
// 0x0026CE40 and complete virtual destructor at 0x0026CF10 establish the
// module-data class identity; its friend_newModuleData factory supplies the
// independent allocation/vtable ownership witness.

class WeaponChangeSpecialPowerModuleModuleData
{
public:
	virtual ~WeaponChangeSpecialPowerModuleModuleData();
};

void forceWeaponChangeSpecialPowerModuleModuleDataDeletingDestructor()
{
	WeaponChangeSpecialPowerModuleModuleData value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BloodthirstyUpdateModuleData scalar-deleting destructor at retail
// RVA 0x00287350 (30 bytes). The exact constructor at 0x00286EC0 installs
// vtable 0x010BC6B8, whose slot zero reaches this wrapper through ILT
// 0x00048982. The wrapper calls the complete destructor through ILT
// 0x0003F59E; the named module-data factory allocates the exact 0xF0 bytes.

class BloodthirstyUpdateModuleData
{
public:
	virtual ~BloodthirstyUpdateModuleData();
};

void forceBloodthirstyUpdateModuleDataDeletingDestructor()
{
	BloodthirstyUpdateModuleData value;
}

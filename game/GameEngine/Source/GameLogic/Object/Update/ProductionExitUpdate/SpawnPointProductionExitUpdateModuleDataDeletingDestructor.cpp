// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// SpawnPointProductionExitUpdateModuleData. The exact constructor at
// 0x0035F0F0 installs dedicated vtable 0x010E8D28; slot zero routes through
// ILT 0x0002AEF0 to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x0003C457.

class SpawnPointProductionExitUpdateModuleData
{
public:
	virtual ~SpawnPointProductionExitUpdateModuleData();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceSpawnPointProductionExitUpdateModuleDataDeletingDestructor(const SpawnPointProductionExitUpdateModuleData &that)
{
	SpawnPointProductionExitUpdateModuleData value(that);
}

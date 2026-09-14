// cl: /O2

// The constructor at 0x0024D190 identifies this 30-byte scalar-deleting
// destructor as the HordeGarrisonContainModuleData vtable slot.
class HordeGarrisonContainModuleData
{
public:
	virtual ~HordeGarrisonContainModuleData();
};

void forceHordeGarrisonContainModuleDataDeletingDestructor()
{
	HordeGarrisonContainModuleData value;
}

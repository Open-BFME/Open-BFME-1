// cl: /O2

// The constructor at 0x0024D190 identifies this 30-byte scalar-deleting
// destructor as the HordeGarrisonContainModuleData vtable slot.
class HordeGarrisonContainModuleData
{
public:
	virtual ~HordeGarrisonContainModuleData();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceHordeGarrisonContainModuleDataDeletingDestructor(const HordeGarrisonContainModuleData &that)
{
	HordeGarrisonContainModuleData value(that);
}

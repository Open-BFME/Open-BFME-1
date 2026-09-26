// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// ScavengerSpecialPowerModuleData. The exact constructor at 0x00265A80
// installs dedicated vtable 0x010B6FF8; slot zero routes through ILT
// 0x000314B7 to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x00025577.

class ScavengerSpecialPowerModuleData
{
public:
	virtual ~ScavengerSpecialPowerModuleData();
};

void forceScavengerSpecialPowerModuleDataDeletingDestructor()
{
	ScavengerSpecialPowerModuleData value;
}

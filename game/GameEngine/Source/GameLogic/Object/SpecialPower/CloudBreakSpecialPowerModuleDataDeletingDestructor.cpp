// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for CloudBreakSpecialPowerModuleData.
// The exact constructor at 0x002592A0 installs dedicated vtable 0x010B3CD8;
// slot zero routes through ILT 0x0003D861 to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x0001F76C.

class CloudBreakSpecialPowerModuleData
{
public:
	virtual ~CloudBreakSpecialPowerModuleData();
};

void forceCloudBreakSpecialPowerModuleDataDeletingDestructor()
{
	CloudBreakSpecialPowerModuleData value;
}

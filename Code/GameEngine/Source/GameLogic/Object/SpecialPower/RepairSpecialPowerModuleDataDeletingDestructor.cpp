// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// RepairSpecialPowerModuleData. The exact constructor at 0x00264990 installs
// dedicated vtable 0x010B6B10; slot zero routes through ILT 0x0000BAAF to
// this 30-byte wrapper. The wrapper calls the complete destructor through
// ILT 0x00004AAC.

class RepairSpecialPowerModuleData
{
public:
	virtual ~RepairSpecialPowerModuleData();
};

void forceRepairSpecialPowerModuleDataDeletingDestructor()
{
	RepairSpecialPowerModuleData value;
}

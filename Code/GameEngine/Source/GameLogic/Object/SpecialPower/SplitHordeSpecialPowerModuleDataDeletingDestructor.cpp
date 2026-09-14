// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// SplitHordeSpecialPowerModuleData. The exact constructor at 0x0026B1D0
// installs dedicated vtable 0x010B80E8; slot zero routes through ILT
// 0x0000C8AB to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x00018AC0.

class SplitHordeSpecialPowerModuleData
{
public:
	virtual ~SplitHordeSpecialPowerModuleData();
};

void forceSplitHordeSpecialPowerModuleDataDeletingDestructor()
{
	SplitHordeSpecialPowerModuleData value;
}

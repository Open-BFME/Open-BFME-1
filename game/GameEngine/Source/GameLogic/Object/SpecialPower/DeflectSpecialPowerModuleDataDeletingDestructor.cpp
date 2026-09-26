// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// DeflectSpecialPowerModuleData. The exact constructor at 0x0025A600
// installs dedicated vtable 0x010B4520; slot zero routes through ILT
// 0x0003A70B to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x00033AF0.

class DeflectSpecialPowerModuleData
{
public:
	virtual ~DeflectSpecialPowerModuleData();
};

void forceDeflectSpecialPowerModuleDataDeletingDestructor()
{
	DeflectSpecialPowerModuleData value;
}

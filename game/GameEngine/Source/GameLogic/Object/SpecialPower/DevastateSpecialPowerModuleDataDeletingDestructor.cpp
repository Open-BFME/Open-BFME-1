// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// DevastateSpecialPowerModuleData. The exact constructor at 0x0025AC10
// installs dedicated vtable 0x010B47C8; slot zero routes through ILT
// 0x00034897 to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x00032E25.

class DevastateSpecialPowerModuleData
{
public:
	virtual ~DevastateSpecialPowerModuleData();
};

void forceDevastateSpecialPowerModuleDataDeletingDestructor()
{
	DevastateSpecialPowerModuleData value;
}

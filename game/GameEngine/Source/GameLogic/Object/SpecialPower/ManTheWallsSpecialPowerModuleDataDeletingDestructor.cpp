// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// ManTheWallsSpecialPowerModuleData. The exact constructor at 0x00261260
// installs dedicated vtable 0x010B5EA0; slot zero routes through ILT
// 0x00032AFB to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x00016220.

class ManTheWallsSpecialPowerModuleData
{
public:
	virtual ~ManTheWallsSpecialPowerModuleData();
};

void forceManTheWallsSpecialPowerModuleDataDeletingDestructor()
{
	ManTheWallsSpecialPowerModuleData value;
}

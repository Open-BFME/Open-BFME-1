// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// SiegeDeployHordeSpecialPowerModuleData. The exact constructor at 0x00265D90
// installs dedicated vtable 0x010B7240; slot zero routes through ILT
// 0x00025AE5 to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x000175B7.

class SiegeDeployHordeSpecialPowerModuleData
{
public:
	virtual ~SiegeDeployHordeSpecialPowerModuleData();
};

void forceSiegeDeployHordeSpecialPowerModuleDataDeletingDestructor()
{
	SiegeDeployHordeSpecialPowerModuleData value;
}

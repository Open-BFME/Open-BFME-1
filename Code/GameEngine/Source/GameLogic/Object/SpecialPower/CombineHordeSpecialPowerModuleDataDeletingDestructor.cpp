// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// CombineHordeSpecialPowerModuleData. The exact constructor at 0x002598A0
// installs dedicated vtable 0x010B3EC8; slot zero routes through ILT
// 0x0002A072 to this 30-byte wrapper. The wrapper calls the derived complete
// destructor through ILT 0x0000B37F.

class CombineHordeSpecialPowerModuleData
{
public:
	virtual ~CombineHordeSpecialPowerModuleData();
};

void forceCombineHordeSpecialPowerModuleDataDeletingDestructor()
{
	CombineHordeSpecialPowerModuleData value;
}

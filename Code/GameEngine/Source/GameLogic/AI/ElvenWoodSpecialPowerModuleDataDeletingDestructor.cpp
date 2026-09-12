// cl: /DNDEBUG /MD /EHsc
//
// Retail's ElvenWoodSpecialPowerModuleData vtable at 0x010B4C38 names this
// scalar deleting destructor in slot zero (ILT 0x00025F4F -> 0x0025CC50). Its
// call target is the independently matched destructor body at 0x0025CC80.

class ElvenWoodSpecialPowerModuleDataBase
{
public:
	virtual ~ElvenWoodSpecialPowerModuleDataBase();
};

class ElvenWoodSpecialPowerModuleData : public ElvenWoodSpecialPowerModuleDataBase
{
public:
	__declspec(noinline) virtual ~ElvenWoodSpecialPowerModuleData();
};

ElvenWoodSpecialPowerModuleData::~ElvenWoodSpecialPowerModuleData()
{
}

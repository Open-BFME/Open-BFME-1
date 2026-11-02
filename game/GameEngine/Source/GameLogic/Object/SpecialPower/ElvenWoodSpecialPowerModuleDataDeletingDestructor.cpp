// cl: /DNDEBUG /MD /EHsc
//
// Retail's ElvenWoodSpecialPowerModuleData vtable at 0x010B4C38 names this
// scalar deleting destructor in slot zero (ILT 0x00025F4F -> 0x0025CC50). Its
// call target is the independently matched destructor body at 0x0025CC80.

class __declspec(novtable) ElvenWoodSpecialPowerModuleDataBase
{
public:
	virtual ~ElvenWoodSpecialPowerModuleDataBase();
};

class ElvenWoodSpecialPowerModuleData : public ElvenWoodSpecialPowerModuleDataBase
{
	friend void forceElvenWoodSpecialPowerModuleDataDeletingDestructorCopy(const ElvenWoodSpecialPowerModuleData &that);
public:
	__declspec(noinline) virtual ~ElvenWoodSpecialPowerModuleData();
};

// ~ElvenWoodSpecialPowerModuleData is matched out of line (ElvenWoodSpecialPowerModuleDataDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceElvenWoodSpecialPowerModuleDataDeletingDestructorCopy(const ElvenWoodSpecialPowerModuleData &that)
{
	ElvenWoodSpecialPowerModuleData value(that);
}

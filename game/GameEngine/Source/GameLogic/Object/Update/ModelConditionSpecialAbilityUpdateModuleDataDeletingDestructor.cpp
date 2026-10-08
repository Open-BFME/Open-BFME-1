// cl: /O2 /Ob0

class ModelConditionSpecialAbilityUpdateModuleData
{
public:
	virtual ~ModelConditionSpecialAbilityUpdateModuleData();

protected:
	// Protected stand-in constructor so the forcer can install the vftable;
	// its unreferenced IAE COMDAT never clashes with the real public
	// constructor (0x002982D0). The destructor (0x002984B0) is matched in
	// ModelConditionSpecialAbilityUpdateModuleDataDestructor.cpp.
	ModelConditionSpecialAbilityUpdateModuleData() {}
	friend void forceModelConditionSpecialAbilityUpdateModuleDataDeletingDestructor();
};

void forceModelConditionSpecialAbilityUpdateModuleDataDeletingDestructor()
{
	ModelConditionSpecialAbilityUpdateModuleData value;
}

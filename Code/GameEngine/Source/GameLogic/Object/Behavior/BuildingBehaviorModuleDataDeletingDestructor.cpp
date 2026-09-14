// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for BuildingBehaviorModuleData.
// The exact constructor at 0x001F6C70 installs dedicated vtable 0x010A2C88;
// slot zero routes through ILT 0x00019F0B to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x00016A13.

class BuildingBehaviorModuleData
{
public:
	virtual ~BuildingBehaviorModuleData();
};

void forceBuildingBehaviorModuleDataDeletingDestructor()
{
	BuildingBehaviorModuleData value;
}

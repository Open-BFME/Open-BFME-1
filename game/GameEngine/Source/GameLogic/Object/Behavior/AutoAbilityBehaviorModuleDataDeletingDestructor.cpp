// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for AutoAbilityBehaviorModuleData.
// The exact constructor at 0x001ED6A0 installs dedicated vtable 0x010A1A70;
// slot zero routes through ILT 0x0002775F to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x00003C51.

class AutoAbilityBehaviorModuleData
{
public:
	virtual ~AutoAbilityBehaviorModuleData();
};

void forceAutoAbilityBehaviorModuleDataDeletingDestructor()
{
	AutoAbilityBehaviorModuleData value;
}

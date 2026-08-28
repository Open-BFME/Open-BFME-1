// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FireWeaponWhenDeadBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponWhenDeadBehavior.h
class FireWeaponWhenDeadBehavior
{
public:
	FireWeaponWhenDeadBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x8c];
};

// ?friend_newModuleInstance@FireWeaponWhenDeadBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FireWeaponWhenDeadBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new FireWeaponWhenDeadBehavior(thing, data);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AimWeaponBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AimWeaponBehavior
{
public:
	AimWeaponBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x24];
};

// ?friend_newModuleInstance@AimWeaponBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AimWeaponBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new AimWeaponBehavior(thing, data);
}

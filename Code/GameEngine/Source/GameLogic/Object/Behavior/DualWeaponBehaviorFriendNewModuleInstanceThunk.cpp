// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DualWeaponBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DualWeaponBehavior
{
public:
	DualWeaponBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleInstance@DualWeaponBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DualWeaponBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new DualWeaponBehavior(thing, data);
}

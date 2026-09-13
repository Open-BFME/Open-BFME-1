// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSetSpecialAbilityUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WeaponSetSpecialAbilityUpdate
{
public:
	WeaponSetSpecialAbilityUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xe8];
};

// ?friend_newModuleInstance@WeaponSetSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WeaponSetSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new WeaponSetSpecialAbilityUpdate(thing, data);
}

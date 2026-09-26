// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponChangeSpecialPowerModule::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WeaponChangeSpecialPowerModule
{
public:
	WeaponChangeSpecialPowerModule(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x2c];
};

// ?friend_newModuleInstance@WeaponChangeSpecialPowerModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WeaponChangeSpecialPowerModule::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new WeaponChangeSpecialPowerModule(thing, data);
}

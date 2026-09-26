// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponModeSpecialPowerUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WeaponModeSpecialPowerUpdate
{
public:
	WeaponModeSpecialPowerUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x3c];
};

// ?friend_newModuleInstance@WeaponModeSpecialPowerUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WeaponModeSpecialPowerUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new WeaponModeSpecialPowerUpdate(thing, data);
}

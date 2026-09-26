// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HeroModeSpecialAbilityUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HeroModeSpecialAbilityUpdate
{
public:
	HeroModeSpecialAbilityUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xe8];
};

// ?friend_newModuleInstance@HeroModeSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HeroModeSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new HeroModeSpecialAbilityUpdate(thing, data);
}

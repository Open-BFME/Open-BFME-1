// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ToggleMountedSpecialAbilityUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ToggleMountedSpecialAbilityUpdate
{
public:
	ToggleMountedSpecialAbilityUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xec];
};

// ?friend_newModuleInstance@ToggleMountedSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ToggleMountedSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new ToggleMountedSpecialAbilityUpdate(thing, data);
}

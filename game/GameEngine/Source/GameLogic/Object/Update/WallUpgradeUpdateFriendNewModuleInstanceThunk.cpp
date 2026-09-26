// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WallUpgradeUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WallUpgradeUpdate
{
public:
	WallUpgradeUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x34];
};

// ?friend_newModuleInstance@WallUpgradeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WallUpgradeUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new WallUpgradeUpdate(thing, data);
}

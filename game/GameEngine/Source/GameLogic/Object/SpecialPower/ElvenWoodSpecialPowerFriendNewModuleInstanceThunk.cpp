// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ElvenWoodSpecialPower::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ElvenWoodSpecialPower
{
public:
	ElvenWoodSpecialPower(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x2c];
};

// ?friend_newModuleInstance@ElvenWoodSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ElvenWoodSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new ElvenWoodSpecialPower(thing, data);
}

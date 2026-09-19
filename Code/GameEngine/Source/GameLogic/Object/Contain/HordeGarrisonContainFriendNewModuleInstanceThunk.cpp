// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeGarrisonContain::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HordeGarrisonContain
{
public:
	HordeGarrisonContain(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x9bc];
};

// ?friend_newModuleInstance@HordeGarrisonContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeGarrisonContain::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new HordeGarrisonContain(thing, data);
}

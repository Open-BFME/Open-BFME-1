// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HorseHordeContain::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HorseHordeContain
{
public:
	HorseHordeContain(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x224];
};

// ?friend_newModuleInstance@HorseHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HorseHordeContain::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new HorseHordeContain(thing, data);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeEngineContain::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeEngineContain
{
public:
	SiegeEngineContain(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x100];
};

// ?friend_newModuleInstance@SiegeEngineContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeEngineContain::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SiegeEngineContain(thing, data);
}

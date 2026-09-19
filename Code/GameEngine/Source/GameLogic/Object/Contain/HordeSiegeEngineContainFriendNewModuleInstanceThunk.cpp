// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeSiegeEngineContain::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HordeSiegeEngineContain
{
public:
	HordeSiegeEngineContain(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x108];
};

// ?friend_newModuleInstance@HordeSiegeEngineContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeSiegeEngineContain::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new HordeSiegeEngineContain(thing, data);
}

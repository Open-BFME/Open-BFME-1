// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeTransportContain::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HordeTransportContain
{
public:
	HordeTransportContain(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xec];
};

// ?friend_newModuleInstance@HordeTransportContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeTransportContain::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new HordeTransportContain(thing, data);
}

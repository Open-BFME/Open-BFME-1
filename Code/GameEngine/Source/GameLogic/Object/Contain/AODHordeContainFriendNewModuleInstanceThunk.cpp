// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AODHordeContain::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AODHordeContain
{
public:
	AODHordeContain(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x7f8];
};

// ?friend_newModuleInstance@AODHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AODHordeContain::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new AODHordeContain(thing, data);
}

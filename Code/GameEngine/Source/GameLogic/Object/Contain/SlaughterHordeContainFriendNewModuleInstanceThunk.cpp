// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SlaughterHordeContain::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SlaughterHordeContain
{
public:
	SlaughterHordeContain(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x9c4];
};

// ?friend_newModuleInstance@SlaughterHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SlaughterHordeContain::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SlaughterHordeContain(thing, data);
}

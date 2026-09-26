// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeAIUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeAIUpdate
{
public:
	SiegeAIUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x340];
};

// ?friend_newModuleInstance@SiegeAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SiegeAIUpdate(thing, data);
}

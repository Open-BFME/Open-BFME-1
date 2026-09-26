// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GiantBirdAIUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GiantBirdAIUpdate
{
public:
	GiantBirdAIUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x4b4];
};

// ?friend_newModuleInstance@GiantBirdAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GiantBirdAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new GiantBirdAIUpdate(thing, data);
}

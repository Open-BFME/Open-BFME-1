// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialEnemySenseUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpecialEnemySenseUpdate
{
public:
	SpecialEnemySenseUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x20];
};

// ?friend_newModuleInstance@SpecialEnemySenseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpecialEnemySenseUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SpecialEnemySenseUpdate(thing, data);
}

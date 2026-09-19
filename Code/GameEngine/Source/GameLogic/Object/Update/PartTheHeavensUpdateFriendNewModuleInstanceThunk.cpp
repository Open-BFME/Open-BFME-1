// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PartTheHeavensUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PartTheHeavensUpdate
{
public:
	PartTheHeavensUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleInstance@PartTheHeavensUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PartTheHeavensUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new PartTheHeavensUpdate(thing, data);
}

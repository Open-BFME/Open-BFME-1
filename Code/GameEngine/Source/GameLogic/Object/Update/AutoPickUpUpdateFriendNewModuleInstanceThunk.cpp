// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoPickUpUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AutoPickUpUpdate
{
public:
	AutoPickUpUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x2c];
};

// ?friend_newModuleInstance@AutoPickUpUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AutoPickUpUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new AutoPickUpUpdate(thing, data);
}

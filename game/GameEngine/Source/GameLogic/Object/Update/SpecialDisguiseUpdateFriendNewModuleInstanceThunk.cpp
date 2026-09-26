// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialDisguiseUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpecialDisguiseUpdate
{
public:
	SpecialDisguiseUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xf4];
};

// ?friend_newModuleInstance@SpecialDisguiseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpecialDisguiseUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SpecialDisguiseUpdate(thing, data);
}

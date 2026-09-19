// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WargBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WargBehavior
{
public:
	WargBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x10];
};

// ?friend_newModuleInstance@WargBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WargBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new WargBehavior(thing, data);
}

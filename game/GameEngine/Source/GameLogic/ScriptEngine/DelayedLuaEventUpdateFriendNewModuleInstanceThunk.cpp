// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DelayedLuaEventUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DelayedLuaEventUpdate
{
public:
	DelayedLuaEventUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x78];
};

// ?friend_newModuleInstance@DelayedLuaEventUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DelayedLuaEventUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new DelayedLuaEventUpdate(thing, data);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DestroyEnvironmentUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DestroyEnvironmentUpdate
{
public:
	DestroyEnvironmentUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleInstance@DestroyEnvironmentUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DestroyEnvironmentUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new DestroyEnvironmentUpdate(thing, data);
}

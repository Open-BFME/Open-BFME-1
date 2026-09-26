// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RespawnBody::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RespawnBody
{
public:
	RespawnBody(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xe0];
};

// ?friend_newModuleInstance@RespawnBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RespawnBody::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new RespawnBody(thing, data);
}

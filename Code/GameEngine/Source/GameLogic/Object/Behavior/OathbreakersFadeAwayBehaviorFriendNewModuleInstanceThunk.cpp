// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: OathbreakersFadeAwayBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class OathbreakersFadeAwayBehavior
{
public:
	OathbreakersFadeAwayBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleInstance@OathbreakersFadeAwayBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *OathbreakersFadeAwayBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new OathbreakersFadeAwayBehavior(thing, data);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ShareExperienceBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ShareExperienceBehavior
{
public:
	ShareExperienceBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x24];
};

// ?friend_newModuleInstance@ShareExperienceBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ShareExperienceBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new ShareExperienceBehavior(thing, data);
}

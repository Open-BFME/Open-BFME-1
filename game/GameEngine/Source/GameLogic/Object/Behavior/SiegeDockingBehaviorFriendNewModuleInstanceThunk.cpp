// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDockingBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeDockingBehavior
{
public:
	SiegeDockingBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x34];
};

// ?friend_newModuleInstance@SiegeDockingBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeDockingBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SiegeDockingBehavior(thing, data);
}

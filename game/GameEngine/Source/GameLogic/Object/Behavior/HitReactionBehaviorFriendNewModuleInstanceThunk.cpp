// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HitReactionBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HitReactionBehavior
{
public:
	HitReactionBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleInstance@HitReactionBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HitReactionBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new HitReactionBehavior(thing, data);
}

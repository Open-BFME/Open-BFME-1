// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GiantBirdSlowDeathBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GiantBirdSlowDeathBehavior
{
public:
	GiantBirdSlowDeathBehavior(Thing *, const ModuleData *);
	virtual ~GiantBirdSlowDeathBehavior();
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xD4];
};

// ?friend_newModuleInstance@GiantBirdSlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GiantBirdSlowDeathBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new GiantBirdSlowDeathBehavior(thing, data);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ReplenishUnitsBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ReplenishUnitsBehavior
{
public:
	ReplenishUnitsBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleInstance@ReplenishUnitsBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ReplenishUnitsBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new ReplenishUnitsBehavior(thing, data);
}

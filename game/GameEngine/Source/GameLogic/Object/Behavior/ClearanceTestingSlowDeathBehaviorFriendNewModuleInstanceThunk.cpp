// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ClearanceTestingSlowDeathBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ClearanceTestingSlowDeathBehavior
{
public:
	ClearanceTestingSlowDeathBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x54];
};

// ?friend_newModuleInstance@ClearanceTestingSlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ClearanceTestingSlowDeathBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new ClearanceTestingSlowDeathBehavior(thing, data);
}

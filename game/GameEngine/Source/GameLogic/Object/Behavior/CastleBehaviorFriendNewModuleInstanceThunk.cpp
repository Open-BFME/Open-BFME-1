// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CastleBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CastleBehavior
{
public:
	CastleBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x114];
};

// ?friend_newModuleInstance@CastleBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CastleBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new CastleBehavior(thing, data);
}

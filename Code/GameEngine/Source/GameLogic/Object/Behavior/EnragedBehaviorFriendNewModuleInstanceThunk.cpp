// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EnragedBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class EnragedBehavior
{
public:
	EnragedBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x24];
};

// ?friend_newModuleInstance@EnragedBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *EnragedBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new EnragedBehavior(thing, data);
}

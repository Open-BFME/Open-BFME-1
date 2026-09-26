// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ExperienceLevelCreate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ExperienceLevelCreate
{
public:
	ExperienceLevelCreate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x18];
};

// ?friend_newModuleInstance@ExperienceLevelCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ExperienceLevelCreate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new ExperienceLevelCreate(thing, data);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BaseUpgrade::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BaseUpgrade
{
public:
	BaseUpgrade(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x1c];
};

// ?friend_newModuleInstance@BaseUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BaseUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new BaseUpgrade(thing, data);
}

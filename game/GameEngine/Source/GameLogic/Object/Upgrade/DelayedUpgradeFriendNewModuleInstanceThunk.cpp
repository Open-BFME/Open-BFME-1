// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DelayedUpgrade::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DelayedUpgrade
{
public:
	DelayedUpgrade(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x1c];
};

// ?friend_newModuleInstance@DelayedUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DelayedUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new DelayedUpgrade(thing, data);
}

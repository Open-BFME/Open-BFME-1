// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RubbleRiseUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RubbleRiseUpdate
{
public:
	RubbleRiseUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x48];
};

// ?friend_newModuleInstance@RubbleRiseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RubbleRiseUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new RubbleRiseUpdate(thing, data);
}

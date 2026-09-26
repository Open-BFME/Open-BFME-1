// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FadeAndDieOrnamentUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FadeAndDieOrnamentUpdate
{
public:
	FadeAndDieOrnamentUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x50];
};

// ?friend_newModuleInstance@FadeAndDieOrnamentUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FadeAndDieOrnamentUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new FadeAndDieOrnamentUpdate(thing, data);
}

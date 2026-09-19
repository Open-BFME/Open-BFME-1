// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GloriousChargeUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GloriousChargeUpdate
{
public:
	GloriousChargeUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xf4];
};

// ?friend_newModuleInstance@GloriousChargeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GloriousChargeUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new GloriousChargeUpdate(thing, data);
}

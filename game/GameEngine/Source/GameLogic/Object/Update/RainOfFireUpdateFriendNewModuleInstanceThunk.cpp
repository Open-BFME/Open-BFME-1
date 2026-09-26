// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RainOfFireUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RainOfFireUpdate
{
public:
	RainOfFireUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x38];
};

// ?friend_newModuleInstance@RainOfFireUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RainOfFireUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new RainOfFireUpdate(thing, data);
}

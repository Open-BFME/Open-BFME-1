// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DevastateSpecialPower::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DevastateSpecialPower
{
public:
	DevastateSpecialPower(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x2c];
};

// ?friend_newModuleInstance@DevastateSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DevastateSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new DevastateSpecialPower(thing, data);
}

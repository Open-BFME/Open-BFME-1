// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GrabPassengerSpecialPower::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GrabPassengerSpecialPower
{
public:
	GrabPassengerSpecialPower(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x2c];
};

// ?friend_newModuleInstance@GrabPassengerSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GrabPassengerSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new GrabPassengerSpecialPower(thing, data);
}

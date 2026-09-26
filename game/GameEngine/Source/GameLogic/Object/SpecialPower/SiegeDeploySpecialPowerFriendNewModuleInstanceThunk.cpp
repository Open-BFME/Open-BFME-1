// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDeploySpecialPower::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeDeploySpecialPower
{
public:
	SiegeDeploySpecialPower(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x74];
};

// ?friend_newModuleInstance@SiegeDeploySpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeDeploySpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SiegeDeploySpecialPower(thing, data);
}

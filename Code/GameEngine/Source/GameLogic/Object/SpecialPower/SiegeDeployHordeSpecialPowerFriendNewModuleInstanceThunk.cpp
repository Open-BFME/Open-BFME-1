// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDeployHordeSpecialPower::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeDeployHordeSpecialPower
{
public:
	SiegeDeployHordeSpecialPower(Thing *, const ModuleData *);
	virtual ~SiegeDeployHordeSpecialPower();
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x48];
};

// ?friend_newModuleInstance@SiegeDeployHordeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeDeployHordeSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SiegeDeployHordeSpecialPower(thing, data);
}

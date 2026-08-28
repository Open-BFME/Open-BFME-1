// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoHealBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoHealBehavior.h
class AutoHealBehavior
{
public:
	AutoHealBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x34];
};

// ?friend_newModuleInstance@AutoHealBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AutoHealBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new AutoHealBehavior(thing, data);
}

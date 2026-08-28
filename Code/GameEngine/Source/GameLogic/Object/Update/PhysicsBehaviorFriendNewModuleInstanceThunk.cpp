// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PhysicsBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PhysicsUpdate.h
class PhysicsBehavior
{
public:
	PhysicsBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x60];
};

// ?friend_newModuleInstance@PhysicsBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PhysicsBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new PhysicsBehavior(thing, data);
}

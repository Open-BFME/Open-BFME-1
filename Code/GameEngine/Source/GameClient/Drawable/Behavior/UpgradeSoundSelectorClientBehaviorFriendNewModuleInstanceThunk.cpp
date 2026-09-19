// cl: /DNDEBUG /MD /EHsc

// Allocate sixteen bytes, construct, return the pointer.
//
// The constructor is inlined into the factory rather than called: what is called
// is the base's, and the three vptr stores after it are the inlined body -- the
// second base's own vptr at +0xC, then this class's two, overwriting both. The
// object is returned unadjusted, so Module is the base at offset zero.
//
// The static's mangling is SA, which is cdecl, so the caller cleans and the
// function ends in a bare ret despite taking two arguments.
class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
	virtual void unknownVirtual(void);

private:
	int m_04;
	int m_08;
};

// The constructor actually called is ClientUpdateModule's, which is pinned at
// the same incremental-link thunk as seven other module constructors. Module
// itself is what the factory returns, and it sits at offset zero, so the
// returned pointer needs no adjustment.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ClientUpdateModule.h
class ClientUpdateModule : public Module
{
public:
	ClientUpdateModule(Thing *thing, const ModuleData *moduleData);
};

class SoundSelectorInterface
{
public:
	virtual void unknownInterfaceVirtual(void);
};

class UpgradeSoundSelectorClientBehavior : public ClientUpdateModule, public SoundSelectorInterface
{
public:
	UpgradeSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData)
		: ClientUpdateModule(thing, moduleData) {}

	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
};

// ?friend_newModuleInstance@UpgradeSoundSelectorClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *UpgradeSoundSelectorClientBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return new UpgradeSoundSelectorClientBehavior(thing, moduleData);
}

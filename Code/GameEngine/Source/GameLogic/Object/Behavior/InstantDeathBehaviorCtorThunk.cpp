// cl: /DNDEBUG /MD /EHsc
// readable body of ??0InstantDeathBehavior@@: Code/GameEngine/Source/GameLogic/Object/Behavior/InstantDeathBehavior.cpp

// Open-BFME5: InstantDeathBehavior module ctor.
// Base call then interim dual iface vtbls at +0xC/+0x10, then three
// most-derived vtbls at +0/+0xC/+0x10.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class InstantDeathBehaviorIface1
{
public:
	virtual void instantDeathIface1Anchor();
};

class InstantDeathBehaviorIface2
{
public:
	virtual void instantDeathIface2Anchor();
};

class InstantDeathBehaviorBase : public BehaviorModule
{
public:
	InstantDeathBehaviorBase(Thing *thing, const ModuleData *moduleData);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InstantDeathBehavior.h
class InstantDeathBehavior : public InstantDeathBehaviorBase,
	public InstantDeathBehaviorIface1,
	public InstantDeathBehaviorIface2
{
public:
	InstantDeathBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0InstantDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
InstantDeathBehavior::InstantDeathBehavior(Thing *thing, const ModuleData *moduleData)
	: InstantDeathBehaviorBase(thing, moduleData)
{
}

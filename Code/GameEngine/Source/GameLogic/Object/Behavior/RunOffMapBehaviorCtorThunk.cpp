// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RunOffMapBehavior module ctor.
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

class RunOffMapBehaviorIface1
{
public:
	virtual void runOffMapIface1Anchor();
};

class RunOffMapBehaviorIface2
{
public:
	virtual void runOffMapIface2Anchor();
};

class RunOffMapBehaviorBase : public BehaviorModule
{
public:
	RunOffMapBehaviorBase(Thing *thing, const ModuleData *moduleData);
};

class RunOffMapBehavior : public RunOffMapBehaviorBase,
	public RunOffMapBehaviorIface1,
	public RunOffMapBehaviorIface2
{
public:
	RunOffMapBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0RunOffMapBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
RunOffMapBehavior::RunOffMapBehavior(Thing *thing, const ModuleData *moduleData)
	: RunOffMapBehaviorBase(thing, moduleData)
{
}

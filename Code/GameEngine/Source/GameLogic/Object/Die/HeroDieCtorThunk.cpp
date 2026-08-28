// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HeroDie module ctor.
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

class HeroDieIface1
{
public:
	virtual void heroDieIface1Anchor();
};

class HeroDieIface2
{
public:
	virtual void heroDieIface2Anchor();
};

class HeroDieBase : public BehaviorModule
{
public:
	HeroDieBase(Thing *thing, const ModuleData *moduleData);
};

class HeroDie : public HeroDieBase,
	public HeroDieIface1,
	public HeroDieIface2
{
public:
	HeroDie(Thing *thing, const ModuleData *moduleData);
};

// ??0HeroDie@@QAE@PAVThing@@PBVModuleData@@@Z
HeroDie::HeroDie(Thing *thing, const ModuleData *moduleData)
	: HeroDieBase(thing, moduleData)
{
}

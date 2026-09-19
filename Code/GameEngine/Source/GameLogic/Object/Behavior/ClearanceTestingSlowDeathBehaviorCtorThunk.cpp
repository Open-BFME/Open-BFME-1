// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ClearanceTestingSlowDeathBehavior module ctor (ICF 74B family).
// Base call, interim vtbl at +0x50, then most-derived vtbls at
// +0/+0xC/+0x10/+0x20/+0x24/+0x50.

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

class ClearanceTestingSlowDeathBehaviorIface1
{
public:
	virtual void clearanceTestingSlowDeathBehaviorIface1Anchor();
};

class ClearanceTestingSlowDeathBehaviorIface2
{
public:
	virtual void clearanceTestingSlowDeathBehaviorIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class ClearanceTestingSlowDeathBehaviorIface3
{
public:
	virtual void clearanceTestingSlowDeathBehaviorIface3Anchor();
};

class ClearanceTestingSlowDeathBehaviorIface4
{
public:
	virtual void clearanceTestingSlowDeathBehaviorIface4Anchor();

private:
	unsigned char m_pad[0x28];
};

class ClearanceTestingSlowDeathBehaviorIface5
{
public:
	virtual void clearanceTestingSlowDeathBehaviorIface5Anchor();
};

class ClearanceTestingSlowDeathBehaviorBase : public BehaviorModule,
	public ClearanceTestingSlowDeathBehaviorIface1,
	public ClearanceTestingSlowDeathBehaviorIface2,
	public ClearanceTestingSlowDeathBehaviorIface3,
	public ClearanceTestingSlowDeathBehaviorIface4
{
public:
	ClearanceTestingSlowDeathBehaviorBase(Thing *thing, const ModuleData *moduleData);
};

class ClearanceTestingSlowDeathBehavior : public ClearanceTestingSlowDeathBehaviorBase,
	public ClearanceTestingSlowDeathBehaviorIface5
{
public:
	ClearanceTestingSlowDeathBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0ClearanceTestingSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
ClearanceTestingSlowDeathBehavior::ClearanceTestingSlowDeathBehavior(Thing *thing, const ModuleData *moduleData)
	: ClearanceTestingSlowDeathBehaviorBase(thing, moduleData)
{
}

// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: NeutronMissileSlowDeathBehavior module ctor (ICF 74B family).
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

class NeutronMissileSlowDeathBehaviorIface1
{
public:
	virtual void neutronMissileSlowDeathBehaviorIface1Anchor();
};

class NeutronMissileSlowDeathBehaviorIface2
{
public:
	virtual void neutronMissileSlowDeathBehaviorIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class NeutronMissileSlowDeathBehaviorIface3
{
public:
	virtual void neutronMissileSlowDeathBehaviorIface3Anchor();
};

class NeutronMissileSlowDeathBehaviorIface4
{
public:
	virtual void neutronMissileSlowDeathBehaviorIface4Anchor();

private:
	unsigned char m_pad[0x28];
};

class NeutronMissileSlowDeathBehaviorIface5
{
public:
	virtual void neutronMissileSlowDeathBehaviorIface5Anchor();
};

class NeutronMissileSlowDeathBehaviorBase : public BehaviorModule,
	public NeutronMissileSlowDeathBehaviorIface1,
	public NeutronMissileSlowDeathBehaviorIface2,
	public NeutronMissileSlowDeathBehaviorIface3,
	public NeutronMissileSlowDeathBehaviorIface4
{
public:
	NeutronMissileSlowDeathBehaviorBase(Thing *thing, const ModuleData *moduleData);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutronMissileSlowDeathUpdate.h
class NeutronMissileSlowDeathBehavior : public NeutronMissileSlowDeathBehaviorBase,
	public NeutronMissileSlowDeathBehaviorIface5
{
public:
	NeutronMissileSlowDeathBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0NeutronMissileSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
NeutronMissileSlowDeathBehavior::NeutronMissileSlowDeathBehavior(Thing *thing, const ModuleData *moduleData)
	: NeutronMissileSlowDeathBehaviorBase(thing, moduleData)
{
}

// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: CountermeasuresBehavior module ctor (ICF 74B family).
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

class CountermeasuresBehaviorIface1
{
public:
	virtual void countermeasuresBehaviorIface1Anchor();
};

class CountermeasuresBehaviorIface2
{
public:
	virtual void countermeasuresBehaviorIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class CountermeasuresBehaviorIface3
{
public:
	virtual void countermeasuresBehaviorIface3Anchor();
};

class CountermeasuresBehaviorIface4
{
public:
	virtual void countermeasuresBehaviorIface4Anchor();

private:
	unsigned char m_pad[0x28];
};

class CountermeasuresBehaviorIface5
{
public:
	virtual void countermeasuresBehaviorIface5Anchor();
};

class CountermeasuresBehaviorBase : public BehaviorModule,
	public CountermeasuresBehaviorIface1,
	public CountermeasuresBehaviorIface2,
	public CountermeasuresBehaviorIface3,
	public CountermeasuresBehaviorIface4
{
public:
	CountermeasuresBehaviorBase(Thing *thing, const ModuleData *moduleData);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CountermeasuresBehavior.h
class CountermeasuresBehavior : public CountermeasuresBehaviorBase,
	public CountermeasuresBehaviorIface5
{
public:
	CountermeasuresBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0CountermeasuresBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
CountermeasuresBehavior::CountermeasuresBehavior(Thing *thing, const ModuleData *moduleData)
	: CountermeasuresBehaviorBase(thing, moduleData)
{
}

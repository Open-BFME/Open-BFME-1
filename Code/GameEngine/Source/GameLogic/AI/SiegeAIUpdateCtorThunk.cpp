// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeAIUpdate module ctor.
// Out-of-line base MI, then five most-derived vtbls at
// +0/+0xC/+0x10/+0x20/+0x24.

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

class SiegeAIUpdateIface1
{
public:
	virtual void siegeAIUpdateIface1Anchor();
};

class SiegeAIUpdateIface2
{
public:
	virtual void siegeAIUpdateIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class SiegeAIUpdateIface3
{
public:
	virtual void siegeAIUpdateIface3Anchor();
};

class SiegeAIUpdateIface4
{
public:
	virtual void siegeAIUpdateIface4Anchor();
};

class SiegeAIUpdateBase : public BehaviorModule,
	public SiegeAIUpdateIface1,
	public SiegeAIUpdateIface2,
	public SiegeAIUpdateIface3,
	public SiegeAIUpdateIface4
{
public:
	SiegeAIUpdateBase(Thing *thing, const ModuleData *moduleData);
};

class SiegeAIUpdate : public SiegeAIUpdateBase
{
public:
	SiegeAIUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0SiegeAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SiegeAIUpdate::SiegeAIUpdate(Thing *thing, const ModuleData *moduleData)
	: SiegeAIUpdateBase(thing, moduleData)
{
}

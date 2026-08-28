// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RespawnBody module ctor.
// Out-of-line base MI, then three most-derived vtbls at +0/+0xC/+0x10.

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

class RespawnBodyIface1
{
public:
	virtual void respawnBodyIface1Anchor();
};

class RespawnBodyIface2
{
public:
	virtual void respawnBodyIface2Anchor();
};

class RespawnBodyBase : public BehaviorModule,
	public RespawnBodyIface1,
	public RespawnBodyIface2
{
public:
	RespawnBodyBase(Thing *thing, const ModuleData *moduleData);
};

class RespawnBody : public RespawnBodyBase
{
public:
	RespawnBody(Thing *thing, const ModuleData *moduleData);
};

// ??0RespawnBody@@QAE@PAVThing@@PBVModuleData@@@Z
RespawnBody::RespawnBody(Thing *thing, const ModuleData *moduleData)
	: RespawnBodyBase(thing, moduleData)
{
}

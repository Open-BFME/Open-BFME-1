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

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

class ActiveBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	ActiveBody(Thing *thing, const ModuleData *moduleData);
	virtual ~ActiveBody();
};

class RespawnBody : public ActiveBody
{
public:
	RespawnBody(Thing *thing, const ModuleData *moduleData);
	virtual ~RespawnBody();
};

// ??0RespawnBody@@QAE@PAVThing@@PBVModuleData@@@Z
RespawnBody::RespawnBody(Thing *thing, const ModuleData *moduleData)
	: ActiveBody(thing, moduleData)
{
}

RespawnBody::~RespawnBody()
{
}

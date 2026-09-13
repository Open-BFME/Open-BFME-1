// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TransportAIUpdate module ctor.
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

class TransportAIUpdateIface1
{
public:
	virtual void transportAIUpdateIface1Anchor();
};

class TransportAIUpdateIface2
{
public:
	virtual void transportAIUpdateIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class TransportAIUpdateIface3
{
public:
	virtual void transportAIUpdateIface3Anchor();
};

class TransportAIUpdateIface4
{
public:
	virtual void transportAIUpdateIface4Anchor();
};

class TransportAIUpdateBase : public BehaviorModule,
	public TransportAIUpdateIface1,
	public TransportAIUpdateIface2,
	public TransportAIUpdateIface3,
	public TransportAIUpdateIface4
{
public:
	TransportAIUpdateBase(Thing *thing, const ModuleData *moduleData);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportAIUpdate.h
class TransportAIUpdate : public TransportAIUpdateBase
{
public:
	TransportAIUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0TransportAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
TransportAIUpdate::TransportAIUpdate(Thing *thing, const ModuleData *moduleData)
	: TransportAIUpdateBase(thing, moduleData)
{
}

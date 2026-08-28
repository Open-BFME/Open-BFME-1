// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: CivilianSpawnCollide module ctor.
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

class CivilianSpawnCollideIface1
{
public:
	virtual void civilianSpawnCollideIface1Anchor();
};

class CivilianSpawnCollideIface2
{
public:
	virtual void civilianSpawnCollideIface2Anchor();
};

class CivilianSpawnCollideBase : public BehaviorModule
{
public:
	CivilianSpawnCollideBase(Thing *thing, const ModuleData *moduleData);
};

class CivilianSpawnCollide : public CivilianSpawnCollideBase,
	public CivilianSpawnCollideIface1,
	public CivilianSpawnCollideIface2
{
public:
	CivilianSpawnCollide(Thing *thing, const ModuleData *moduleData);
};

// ??0CivilianSpawnCollide@@QAE@PAVThing@@PBVModuleData@@@Z
CivilianSpawnCollide::CivilianSpawnCollide(Thing *thing, const ModuleData *moduleData)
	: CivilianSpawnCollideBase(thing, moduleData)
{
}

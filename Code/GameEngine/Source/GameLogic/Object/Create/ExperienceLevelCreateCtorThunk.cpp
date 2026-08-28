// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ExperienceLevelCreate module ctor.
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

class ExperienceLevelCreateIface1
{
public:
	virtual void experienceLevelCreateIface1Anchor();
};

class ExperienceLevelCreateIface2
{
public:
	virtual void experienceLevelCreateIface2Anchor();
};

class ExperienceLevelCreateBase : public BehaviorModule,
	public ExperienceLevelCreateIface1,
	public ExperienceLevelCreateIface2
{
public:
	ExperienceLevelCreateBase(Thing *thing, const ModuleData *moduleData);
};

class ExperienceLevelCreate : public ExperienceLevelCreateBase
{
public:
	ExperienceLevelCreate(Thing *thing, const ModuleData *moduleData);
};

// ??0ExperienceLevelCreate@@QAE@PAVThing@@PBVModuleData@@@Z
ExperienceLevelCreate::ExperienceLevelCreate(Thing *thing, const ModuleData *moduleData)
	: ExperienceLevelCreateBase(thing, moduleData)
{
}

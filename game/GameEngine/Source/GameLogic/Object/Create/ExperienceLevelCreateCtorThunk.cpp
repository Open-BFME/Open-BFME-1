// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ExperienceLevelCreate module ctor.
// Out-of-line base MI, then three most-derived vtbls at +0/+0xC/+0x10.

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
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

// The base this constructor initialises is reached through ILT 0x00026CAB,
// whose jump lands on rva 0x0024F450: the 64-byte matched
// CreateModule(Thing *, ModuleData const *) -- the same base ctor
// LockWeaponCreate reaches through the same stub
// (game/GameEngine/Source/GameLogic/Object/Create/LockWeaponCreate.cpp).
// Only its ctor signature is known here; the members this body never touches
// are left to the class's own TU, so no retail header is redeclared.
class CreateModule : public BehaviorModule,
	public ExperienceLevelCreateIface1,
	public ExperienceLevelCreateIface2
{
public:
	CreateModule(Thing *thing, const ModuleData *moduleData);
};

class ExperienceLevelCreate : public CreateModule
{
public:
	ExperienceLevelCreate(Thing *thing, const ModuleData *moduleData);
};

// ??0ExperienceLevelCreate@@QAE@PAVThing@@PBVModuleData@@@Z
ExperienceLevelCreate::ExperienceLevelCreate(Thing *thing, const ModuleData *moduleData)
	: CreateModule(thing, moduleData)
{
}
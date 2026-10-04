// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LevelGrantSpecialPower module ctor.
// Base MI: vptrs at +0/+0xC/+0x10/+0x20.

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor() = 0;

private:
	unsigned char m_data[8];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor() = 0;
};

class SpecialPowerModuleExtra
{
public:
	virtual void specialPowerExtraAnchor() = 0;

private:
	unsigned char m_pad[12];
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor() = 0;
};

// The retail base call leaves through ILT 0x00013462, whose jmp target is
// 0x006A6360 = the body the ledger owns as
// ??0SpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z (0x002A6360,
// matched in SpecialAbilityUpdate_ctor_Thunk.cpp).  Spell the base with that
// name so the reference resolves, exactly as
// HeroModeSpecialAbilityUpdateCtorThunk.cpp does for the same ILT entry.
class SpecialAbilityUpdate : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public SpecialPowerModuleExtra,
	public ModuleInterface
{
public:
	SpecialAbilityUpdate( Thing *thing, const ModuleData *moduleData );
};

class LevelGrantSpecialPower : public SpecialAbilityUpdate
{
public:
	LevelGrantSpecialPower( Thing *thing, const ModuleData *moduleData );
};

// ??0LevelGrantSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z
LevelGrantSpecialPower::LevelGrantSpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialAbilityUpdate( thing, moduleData )
{
}
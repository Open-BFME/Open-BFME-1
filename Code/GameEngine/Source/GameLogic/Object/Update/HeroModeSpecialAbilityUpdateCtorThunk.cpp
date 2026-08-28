// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HeroModeSpecialAbilityUpdate module ctor.
// Base MI: vptrs at +0/+0xC/+0x10/+0x20.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class SpecialPowerModuleExtra
{
public:
	virtual void specialPowerExtraAnchor();

private:
	unsigned char m_pad[12];
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class HeroModeSpecialAbilityUpdateBase : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public SpecialPowerModuleExtra,
	public ModuleInterface
{
public:
	HeroModeSpecialAbilityUpdateBase( Thing *thing, const ModuleData *moduleData );
};

class HeroModeSpecialAbilityUpdate : public HeroModeSpecialAbilityUpdateBase
{
public:
	HeroModeSpecialAbilityUpdate( Thing *thing, const ModuleData *moduleData );
};

// ??0HeroModeSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
HeroModeSpecialAbilityUpdate::HeroModeSpecialAbilityUpdate( Thing *thing, const ModuleData *moduleData )
	: HeroModeSpecialAbilityUpdateBase( thing, moduleData )
{
}
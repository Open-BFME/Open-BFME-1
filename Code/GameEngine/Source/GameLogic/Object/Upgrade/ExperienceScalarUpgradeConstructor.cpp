// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ExperienceScalarUpgrade module ctor via UpgradeModule multi-inheritance.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();

private:
	bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
public:
	UpgradeModule( Thing *thing, const ModuleData *moduleData );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ExperienceScalarUpgrade.h
class ExperienceScalarUpgrade : public UpgradeModule
{
public:
	ExperienceScalarUpgrade( Thing *thing, const ModuleData *moduleData );
};

// ??0ExperienceScalarUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
ExperienceScalarUpgrade::ExperienceScalarUpgrade(
	Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}
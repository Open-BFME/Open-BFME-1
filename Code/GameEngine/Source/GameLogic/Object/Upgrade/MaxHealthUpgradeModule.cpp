// cl: /DNDEBUG /MD /EHsc
// readable body of ??0MaxHealthUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp
// readable body of ??0MaxHealthUpgradeModuleData@@QAE@XZ: Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp

// The MaxHealthUpgrade module and the module data it is built from. Upstream
// both constructors live in MaxHealthUpgrade.cpp; they sat in two files here,
// so neither could see the other's half of the same module.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MaxHealthUpgrade.h
class MaxHealthUpgrade : public UpgradeModule
{
public:
	MaxHealthUpgrade( Thing *thing, const ModuleData *moduleData );
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char opaque[0x68];
};

// Retail builds the module data as a sub-object at +8, zeroes +0x70/+0x74, then
// runs the outer vtable's own constructor over `this` -- which is why the same
// layout is spelled twice, once as the novtable class the body defines and once
// as the vtable-carrying class it re-runs.
class __declspec(novtable) MaxHealthUpgradeModuleData
{
public:
	MaxHealthUpgradeModuleData();
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_70;
	unsigned int m_74;
};

class MaxHealthUpgradeModuleDataVtbl
{
public:
	MaxHealthUpgradeModuleDataVtbl() {}
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_70;
	unsigned int m_74;
};

// ??0MaxHealthUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
MaxHealthUpgrade::MaxHealthUpgrade(
	Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}

// ??0MaxHealthUpgradeModuleData@@QAE@XZ
MaxHealthUpgradeModuleData::MaxHealthUpgradeModuleData()
{
	UpgradeModuleDataSub *sub =
		(UpgradeModuleDataSub *)((char *)this + 8);
	sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
	m_70 = 0;
	m_74 = 0;
	MaxHealthUpgradeModuleDataVtbl *v =
		(MaxHealthUpgradeModuleDataVtbl *)this;
	v->MaxHealthUpgradeModuleDataVtbl::MaxHealthUpgradeModuleDataVtbl();
}

// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: SubObjectsUpgrade module ctor
// UpgradeModule base multi-inheritance vtbls, then global+0x3c to +0x1c, byte +0x20=0.

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
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
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
};

class GlobalThing
{
public:
	unsigned char m_pad[0x3C];
	unsigned int m_field3c;
};

// Retail 0x012F0898 is EA's game-logic singleton, which carries the ONE
// canonical spelling ?TheGameLogic@@3PAVGameLogic@@A.  GlobalThing above is this
// TU's own view of the same address, so the field read below casts at the use.
class GameLogic;

// DIR32 global filled from retail.
extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SubObjectsUpgrade.h
class SubObjectsUpgrade : public UpgradeModule
{
public:
	SubObjectsUpgrade(Thing *thing, const ModuleData *moduleData);

private:
	unsigned int m_field1c;
	unsigned char m_byte20;
};

// ??0SubObjectsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
SubObjectsUpgrade::SubObjectsUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
	m_field1c = ((GlobalThing *)TheGameLogic)->m_field3c;
	m_byte20 = 0;
}

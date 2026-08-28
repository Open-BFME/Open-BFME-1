// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();

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
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();

private:
	unsigned int m_state;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpgradeModuleInterface,
	public ModuleInterface
{
public:
	UpgradeModule( Thing *, const ModuleData * );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CostModifierUpgrade.h
class CostModifierUpgrade : public UpgradeModule, public UpgradeMux
{
public:
	CostModifierUpgrade( Thing *, const ModuleData * );

private:
	bool m_enabled;
};

CostModifierUpgrade::CostModifierUpgrade( Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData ),
	  m_enabled( true )
{
}

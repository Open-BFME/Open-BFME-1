// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: SubObjectsUpgrade module ctor
// UpgradeModule base multi-inheritance vtbls, then global+0x3c to +0x1c, byte +0x20=0.

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

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

// DIR32 global filled from retail.
extern GlobalThing *g_theWritableGlobalData;

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
	m_field1c = g_theWritableGlobalData->m_field3c;
	m_byte20 = 0;
}

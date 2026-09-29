// cl: /DNDEBUG /MD /EHsc
// UpgradeModule::UpgradeModule(Thing *, const ModuleData *) at 0x001F8970.
// The ledger row was a naked lift named ??1CostModifierUpgrade, but the body
// ends in `ret 8`, installs vftables and is the shared base constructor that
// twenty-four upgrade module constructors call through ILT 0x0000C315
// (symbols.csv already pins ??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z
// there). The matched ??0CostModifierUpgrade at 0x002D4570 calls it first.
//
// Shape: the ObjectModule constructor (ILT 0x000170E4), the inline
// BehaviorModule vptr round (0x0109C9D0 then 0x0109CB5C/0x0109CA98), the shared
// UpgradeMux constructor at +0x10 (ILT 0x0003D24E), a ModuleInterface base at
// +0x18 (0x010A1BFC), then the UpgradeModule vptr round.

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData) {}
};

// The pinned UpgradeMux constructor ILT 0x0003D24E; body 0x002D9B80 stores a
// dword and then a byte.
class ALU_UpgradeMux
{
public:
	ALU_UpgradeMux();
	virtual void upgradeMuxAnchor();

private:
	unsigned char m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public BehaviorModule, public ALU_UpgradeMux, public ModuleInterface
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
};

// ??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z
UpgradeModule::UpgradeModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData), ALU_UpgradeMux(), ModuleInterface()
{
}
